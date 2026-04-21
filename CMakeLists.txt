cmake_minimum_required(VERSION 3.13)

include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(PC_TEMP_MONITER)

pico_sdk_init()

set(CMAKE_ASM_FLAGS "${CMAKE_ASM_FLAGS} -mcpu=cortex-m0plus -mthumb")
set(CMAKE_EXECUTABLE_SUFFIX ".elf")

add_executable(PC_TEMP_MONITER
    ssd1306_i2c.c
    main.c
)

pico_enable_stdio_usb(PC_TEMP_MONITER 1)
pico_enable_stdio_uart(PC_TEMP_MONITER 0)

target_link_libraries(PC_TEMP_MONITER
    pico_stdlib
    hardware_i2c
)

pico_add_extra_outputs(PC_TEMP_MONITER)