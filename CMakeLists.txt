file(GLOB INCLUDE_FILES CONFIGURE_DEPENDS 
        "src/address/ipv4_address.hpp"
        "src/address/ipv4_address.cpp"
        "src/address/mac_address.hpp"
        "src/address/mac_address.cpp"
        "src/chip/wiznet_w5500.hpp" 
        "src/chip/wiznet_w5500.cpp"
        "src/chip/interface.hpp"
        "src/chip/interface.cpp"
        "src/socket/abstract_socket.hpp"
        "src/socket/abstract_socket.cpp"
        "src/socket/tcp_socket.hpp"
        "src/socket/tcp_socket.cpp"
        "src/socket/udp_socket.hpp"
        "src/socket/udp_socket.cpp")

add_library(W5500_AVR ${INCLUDE_FILES})

set_target_properties(W5500_AVR PROPERTIES LINKER_LANGUAGE CXX)

add_subdirectory("lib/SPI")
add_subdirectory("lib/AVR_Container")

target_link_libraries(W5500_AVR PUBLIC AVR_Container AVR_SPI)

target_include_directories(W5500_AVR PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/inc")