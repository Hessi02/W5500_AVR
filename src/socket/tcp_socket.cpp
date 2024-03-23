/**
 *  \file   tcp_socket.hpp
 *  \brief  The file contains implementation for the TCPSocket class.
 */

#include "tcp_socket.hpp"

TcpSocket::TcpSocket(void)
    : AbstractSocket()
{}

void TcpSocket::listen(void)
{
    constexpr unsigned char listenBitmask = 0x02;
    constexpr uint16_t SnCRRegisterAddress = 0x0001;
    writeControlRegister(SnCRRegisterAddress, &listenBitmask, 1);
}

bool TcpSocket::isOpen(void)
{
    constexpr uint16_t SnSRRegisterAddress = 0x0003;
    unsigned char socketStatus;
    readControlRegister(SnSRRegisterAddress, &socketStatus, 1);

    const bool socketIsInitialized = socketStatus == 0x13;

    return socketIsInitialized || isListening() || isConnected();
}

bool TcpSocket::isListening(void)
{
    constexpr uint16_t SnSRRegisterAddress = 0x0003;
    unsigned char socketStatus;
    readControlRegister(SnSRRegisterAddress, &socketStatus, 1);
    return socketStatus == 0x14;
}

bool TcpSocket::isConnected(void)
{
    constexpr uint16_t SnSRREgisterAddress = 0x0003;
    unsigned char socketStatus;
    readControlRegister(SnSRREgisterAddress, &socketStatus, 1);
    return socketStatus == 0x17;
}

void TcpSocket::specifyType(void)
{
    constexpr uint16_t SnModeRegisterAddress = 0x0000;
    constexpr unsigned char socketMode = 0x01;
    writeControlRegister(SnModeRegisterAddress, &socketMode, 1);
}