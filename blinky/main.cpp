// Copyright 2021 Tomas Barton, tommz9@gmail.com
//
// Licensed under the Apache License, Version 2.0

#include <cstdint>
#include "cmsis_gcc.h"
#include "system_stm32f4xx.h"
#include "stm32f411xe.h"
#include "os.h"
#include "clock.hpp"
#include "flash.hpp"
#include "gpio.hpp"
#include "system.hpp"

//For debugging
#define CE(x) if ((err = x) != OS_ERR_NONE) \
 printf("Runtime error: %d line %d - see ucos_ii.h\n", err, __LINE__);

#define TASK_STK_SIZE 512

#if !defined(ARRAY_SIZE)

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

#endif

#if !defined(ARRAY_START)

#define ARRAY_START(arr) (arr != NULL ? &arr[0] : NULL)

#endif

#if !defined(ARRAY_END)

#define ARRAY_END(arr) (arr != NULL ? &arr[ARRAY_SIZE(arr) - 1] : NULL)

#endif

#if !defined(NULL)

#define NULL (0U)

#endif


OS_STK blinky_task_stack[TASK_STK_SIZE];
INT8U  blinky_task_priority = 32;

#define MILLISECONDS_TO_TICKS(ms) \
  ((ms * OS_TICKS_PER_SEC) / 1000)

void configureSystem() {
  system::enableExtraExceptions();
  //clock::enableCrystalClock();
  flash::enableAllCaches();
  //clock::configureSysTick();
}

void blinky_task(void * /* p_arg */) {

  gpio::Port portA(gpio::Gpio::C);

  auto ledPin = portA.allocatePin(13);
  ledPin.setMode(gpio::PinMode::Output);

  uint32_t cpu_clk_freq;
  uint32_t cnts;
  cpu_clk_freq = SystemCoreClock; 
  cnts  = cpu_clk_freq / (uint32_t)OS_TICKS_PER_SEC;

  OS_CPU_SysTickInit(cnts);

  //unsigned const led_off_interval = MILLISECONDS_TO_TICKS(500);
  //unsigned const led_on_interval = MILLISECONDS_TO_TICKS(2500);

  while (1) {
    ledPin.high();
    OSTimeDly(500);
    ledPin.low();
    OSTimeDly(500);
  }
}

int main(void) {
  //configureSystem();

  // Disable interrupts
  __disable_irq();

  OSInit();

  OSTaskCreate(&blinky_task, (void *)0, &blinky_task_stack[TASK_STK_SIZE - 1], 25);

  // Enable interrupts
  __enable_irq();

  // Start OS
  OSStart();

  while (1) {}
  return 0;
}
