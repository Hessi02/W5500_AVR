add_library(AVR_SPI "spi.hpp" "spi.cpp")

set_target_properties(AVR_SPI PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(AVR_SPI PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")