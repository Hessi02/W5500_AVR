/**
 *  \file   udp_socket.hpp 
 *  \brief  The file contains implementation for the UDPSocket class.
 */

#include "udp_socket.hpp"

UDPSocket::UDPSocket(
    W5500* chipInterface,
    const uint16_t& port) :
AbstractSocket(chipInterface, port)
{
    setSocketType(AbstractSocket::SocketType::UDP);
}

bool UDPSocket::isOpen(void)
{
    return false;
}