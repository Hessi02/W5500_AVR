/**
 *  \file   udp_socket.hpp
 *  \brief  The file contains implementation for the UDPSocket class.
 */

#include "udp_socket.hpp"

UdpSocket::UdpSocket(void)
    : AbstractSocket()
{
    constexpr uint16_t SnModeRegisterAddress = 0x0000;
    constexpr unsigned char socketMode = 0x02;
    writeControlRegister(SnModeRegisterAddress, &socketMode, 1);
}

bool UdpSocket::isOpen(void)
{
    return false;
}