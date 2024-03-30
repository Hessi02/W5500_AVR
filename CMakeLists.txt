file(GLOB INCLUDE_FILES CONFIGURE_DEPENDS 
        "src/callback/callback.hpp"
        "src/callback/callback_instance.hpp"
        "src/address/host_address.hpp"
        "src/address/host_address.cpp"
        "src/address/mac_address.hpp"
        "src/address/mac_address.cpp"
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

add_subdirectory("lib")

target_link_libraries(W5500_AVR PUBLIC avr-libstdcpp AVR_SPI AVR_Container)

target_include_directories(W5500_AVR PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/inc")