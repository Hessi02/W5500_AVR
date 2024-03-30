add_library(AVR_SPI "AVR_SPI/src/spi_device/spi_device.hpp" "AVR_SPI/src/spi_device/spi_device.cpp" "AVR_SPI/src/spi_bus/spi_bus.hpp" "AVR_SPI/src/spi_bus/spi_bus.cpp")
set_target_properties(AVR_SPI PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(AVR_SPI PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/AVR_SPI/inc")

file(GLOB avr-libstdcpp_SRC
     "avr-libstdcpp/src/*.h"
     "avr-libstdcpp/src/*.cpp"
)
add_library(avr-libstdcpp ${avr-libstdcpp_SRC})
set_target_properties(avr-libstdcpp PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(avr-libstdcpp PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/avr-libstdcpp/include")

add_library(AVR_Container "AVR_Container/src/heap.hpp" "AVR_Container/src/element.hpp" "AVR_Container/src/iterator.hpp" "AVR_Container/src/vector.hpp")
set_target_properties(AVR_Container PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(AVR_Container PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/AVR_Container/inc")