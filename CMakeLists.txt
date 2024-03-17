cmake_minimum_required(VERSION 3.29.0)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_C_COMPILER avr-gcc)
set(CMAKE_CXX_COMPILER avr-g++)

project(RPMS)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(MCU at90can128)
set(F_CPU 16000000UL)

add_compile_options(
    -mmcu=${MCU}
    -D F_CPU=${F_CPU}
    -fno-threadsafe-statics
    -Os
    -g3
    -Wall
    -Wdouble-promotion
    -Wno-main
    -Wstack-usage=255
)