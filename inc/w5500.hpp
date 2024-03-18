/**
 *  \file   w5500.hpp
 *  \brief  This is the include file for the W5500_ARV library.
 * 
 *  Include this file to use the library in your project. Make sure
 *  to link the library in CMake. The library is supposed to be 
 *  compiled with the avr-gcc compiler.
 */

#ifndef __W5500_HP__
#define __W5500_HP__

#include "../src/chip/wiznet_w5500.hpp"
#include "../src/socket/abstract_socket.hpp"
#include "../src/socket/tcp_socket.hpp"
#include "../src/socket/udp_socket.hpp"

#endif //__W5500_HP__