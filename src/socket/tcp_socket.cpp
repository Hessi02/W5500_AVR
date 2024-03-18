/**
 *  \file   tcp_socket.hpp 
 *  \brief  The file contains implementation for the TCPSocket class.
 */

#include "tcp_socket.hpp"

TCPSocket::TCPSocket(
    W5500* chipInterface,
    const uint8_t& index,
    const uint16_t& port) :
AbstractSocket(chipInterface, index, port)
{
    
}