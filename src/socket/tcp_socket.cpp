/**
 *  \file   tcp_socket.hpp 
 *  \brief  The file contains implementation for the TCPSocket class.
 */

#include "tcp_socket.hpp"

TCPSocket::TCPSocket(
    W5500* chipInterface,
    const uint16_t& port) :
AbstractSocket(chipInterface, port)
{
    setSocketType(AbstractSocket::SocketType::TCP);
}

void TCPSocket::listen(void)
{
    constexpr unsigned char listenBitmask = 0x02;
    constexpr uint16_t SnCRRegisterAddress = 0x0001;
    writeControlRegister(SnCRRegisterAddress, &listenBitmask, 1);
}

bool TCPSocket::isOpen(void)
{
    constexpr uint16_t SnSRRegisterAddress = 0x0003;
    unsigned char socketStatus;
    readControlRegister(SnSRRegisterAddress, &socketStatus, 1);

    const bool socketIsInitialized = socketStatus == 0x13;

    return socketIsInitialized || isListening() || isConnected();
}

bool TCPSocket::isListening(void)
{
    constexpr uint16_t SnSRRegisterAddress = 0x0003;
    unsigned char socketStatus;
    readControlRegister(SnSRRegisterAddress, &socketStatus, 1);
    return socketStatus == 0x14;
}

bool TCPSocket::isConnected(void)
{
    constexpr uint16_t SnSRREgisterAddress = 0x0003;
    unsigned char socketStatus;
    readControlRegister(SnSRREgisterAddress, &socketStatus, 1);
    return socketStatus == 0x17;
}