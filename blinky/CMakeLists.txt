# Copyright 2021 Tomas Barton, tommz9@gmail.com
#
# Licensed under the Apache License, Version 2.0

add_library(blinky OBJECT)

target_sources(blinky PRIVATE
    clock.cpp
    gpio.cpp
    flash.cpp
    main.cpp
    power.cpp
    system.cpp

    ${PROJECT_SOURCE_DIR}/ucos2_blackpill/cfg/app_hooks.c
    ${PROJECT_SOURCE_DIR}/ucos2_blackpill/port/os_cpu_c.c
    ${PROJECT_SOURCE_DIR}/ucos2_blackpill/port/gnu/os_cpu_a.S
    ${PROJECT_SOURCE_DIR}/ucos2_blackpill/port/gnu/os_dbg.c

    ${PROJECT_SOURCE_DIR}/modules/ucos2/Source/ucos_ii.c
)

target_include_directories(blinky PRIVATE
    ${PROJECT_SOURCE_DIR}/vendor
    ${PROJECT_SOURCE_DIR}/ucos2_blackpill/port/gnu
    ${PROJECT_SOURCE_DIR}/ucos2_blackpill/cfg
    ${PROJECT_SOURCE_DIR}/modules/ucos2/Source
)
