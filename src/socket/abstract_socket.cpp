/**
 *  \file   abstract_socket.hpp 
 *  \brief  The file contains implementation for the AbstractSocket class.
 */

#include "abstract_socket.hpp"

#include "../chip/wiznet_w5500.hpp"

AbstractSocket::AbstractSocket(
    W5500* chipInterface, 
    const uint16_t& port) :
_chipInterface(chipInterface),
_index(0)
{
    setLocalPort(port);
    _chipInterface->registerSocket(this);
}

void AbstractSocket::setSocketType(const SocketType& socketType)
{
    constexpr uint16_t SnModeRegisterAddress = 0x0000;
    unsigned char socketMode = static_cast<unsigned char>(socketType);
    writeControlRegister(SnModeRegisterAddress, &socketMode, 1);
}

void AbstractSocket::setLocalPort(const uint16_t& port)
{
    constexpr uint16_t SnPORTRegisterAddress = 0x0004;
    constexpr uint8_t byteCount = 2;

    const unsigned char portInBytes[byteCount] = {
        static_cast<unsigned char>(0xff & (port >> 8)), 
        static_cast<unsigned char>(0xff & port)
    };

    writeControlRegister(SnPORTRegisterAddress, portInBytes, byteCount);
}

void AbstractSocket::setDestinationPort(const uint16_t& port)
{
    constexpr uint16_t SnDPORTRegisterAddress = 0x0010;
    constexpr uint8_t byteCount = 2;

    const unsigned char portInBytes[byteCount] = {
        static_cast<unsigned char>(0xff & (port >> 8)), 
        static_cast<unsigned char>(0xff & port)
    };

    writeControlRegister(SnDPORTRegisterAddress, portInBytes, byteCount);
}

void AbstractSocket::setDestinationAddress(const unsigned char* addressIPv4)
{
    constexpr uint16_t SnDIPRRegisterAddress = 0x000C;
    constexpr uint8_t byteCount = 4;
    writeControlRegister(SnDIPRRegisterAddress, addressIPv4, byteCount);
}

void AbstractSocket::open(void)
{
    constexpr unsigned char openBitmask = 0x01;
    constexpr uint16_t SnCRRegisterAddress = 0x0001;
    writeControlRegister(SnCRRegisterAddress, &openBitmask, 1);
}

void AbstractSocket::writeControlRegister(
    const uint16_t& addressWord,
	const unsigned char* dataByteArray,
	const uint8_t& dataByteCount)
{
    const unsigned char controlByte = 0x0C | (_index << 5);
    _chipInterface->writeRegister(addressWord, controlByte, dataByteArray, dataByteCount);
}

void AbstractSocket::readControlRegister(
	const uint16_t& addressWord,
	unsigned char* dataByteArray,
	const uint8_t& dataByteCount)
{
    const unsigned char controlByte = 0x08 | (_index << 5);
    _chipInterface->readRegister(addressWord, controlByte, dataByteArray, dataByteCount);
}