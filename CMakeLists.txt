file(GLOB INCLUDE_FILES CONFIGURE_DEPENDS 
        "src/chip/wiznet_w5500.hpp" 
        "src/chip/wiznet_w5500.cpp"
        "src/socket/abstract_socket.hpp"
        "src/socket/abstract_socket.cpp"
        "src/socket/tcp_socket.hpp"
        "src/socket/tcp_socket.cpp"
        "src/socket/udp_socket.hpp"
        "src/socket/udp_socket.cpp")

add_library(W5500_AVR ${INCLUDE_FILES})

set_target_properties(W5500_AVR PROPERTIES LINKER_LANGUAGE CXX)

add_subdirectory("lib/SPI")
target_link_libraries(W5500_AVR PRIVATE AVR_SPI)

target_include_directories(W5500_AVR PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/inc")