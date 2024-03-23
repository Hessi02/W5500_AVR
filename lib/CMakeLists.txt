add_library(AVR_SPI "AVR_SPI/spi.hpp" "AVR_SPI/spi.cpp")
set_target_properties(AVR_SPI PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(AVR_SPI PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/AVR_SPI")

file(GLOB avr-libstdcpp_SRC
     "avr-libstdcpp/src/*.h"
     "avr-libstdcpp/src/*.cpp"
)

add_library(avr-libstdcpp ${avr-libstdcpp_SRC})
set_target_properties(avr-libstdcpp PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(avr-libstdcpp PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/avr-libstdcpp/include")