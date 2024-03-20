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
    setSocketType(AbstractSocket::SocketType::TCP);
}

void TCPSocket::open(void)
{
    constexpr unsigned char openBitmask = 0x01;
    constexpr uint16_t SnCRRegisterAddress = 0x0001;
    writeControlRegister(SnCRRegisterAddress, &openBitmask, 1);
}

void TCPSocket::listen(void)
{
    constexpr unsigned char listenBitmask = 0x02;
    constexpr uint16_t SnCRRegisterAddress = 0x0001;
    writeControlRegister(SnCRRegisterAddress, &listenBitmask, 1);
}