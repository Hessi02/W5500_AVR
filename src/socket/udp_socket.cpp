/**
 *  \file   udp_socket.hpp
 *  \brief  The file contains implementation for the UDPSocket class.
 */

#include "udp_socket.hpp"

UDPSocket::UDPSocket(W5500* chipInterface, const uint16_t& port)
    : AbstractSocket(chipInterface, port)
{
    constexpr uint16_t SnModeRegisterAddress = 0x0000;
    constexpr unsigned char socketMode = 0x02;
    writeControlRegister(SnModeRegisterAddress, &socketMode, 1);
}

bool UDPSocket::isOpen(void)
{
    return false;
}