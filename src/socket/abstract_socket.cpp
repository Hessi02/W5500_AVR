/**
 *  \file   abstract_socket.hpp
 *  \brief  The file contains implementation for the AbstractSocket class.
 */

#include "abstract_socket.hpp"

#include "../chip/wiznet_w5500.hpp"
#include <avr/io.h>
#include <util/delay.h>

AbstractSocket::AbstractSocket(void) {}

AbstractSocket::~AbstractSocket(void)
{
    if (_chipInterface)
    {
        _chipInterface->unsubscribeSocket(_index);
    }
}

uint8_t AbstractSocket::getIndex(void) const
{
    return _index;
}

void AbstractSocket::setLocalPort(const uint16_t& port)
{
    constexpr uint16_t SnPORTRegisterAddress = 0x0004;
    constexpr uint8_t byteCount = 2;

    const unsigned char portInBytes[byteCount] = {static_cast<unsigned char>(0xff & (port >> 8)),
                                                  static_cast<unsigned char>(0xff & port)};

    writeControlRegister(SnPORTRegisterAddress, portInBytes, byteCount);
}

void AbstractSocket::open(void)
{
    constexpr unsigned char openBitmask = 0x01;
    constexpr uint16_t SnCRRegisterAddress = 0x0001;
    writeControlRegister(SnCRRegisterAddress, &openBitmask, 1);
}

void AbstractSocket::writeControlRegister(const uint16_t& addressWord,
                                          const unsigned char* dataByteArray,
                                          const uint8_t& dataByteCount)
{
    if (_chipInterface)
    {
        const unsigned char controlByte = 0x0C | (_index << 5);
        _chipInterface->writeRegister(addressWord, controlByte, dataByteArray, dataByteCount);
    }
}

void AbstractSocket::readControlRegister(const uint16_t& addressWord,
                                         unsigned char* dataByteArray,
                                         const uint8_t& dataByteCount)
{
    if (_chipInterface)
    {
        const unsigned char controlByte = 0x08 | (_index << 5);
        _chipInterface->readRegister(addressWord, controlByte, dataByteArray, dataByteCount);
    }
}

void AbstractSocket::writeBufferRegister(const uint16_t& addressRegister,
                                         const unsigned char* data,
                                         const uint8_t& length)
{
    if (_chipInterface)
    {
        const unsigned char controlByte = 0x14 | (_index << 5);
        _chipInterface->writeRegister(addressRegister, controlByte, data, length);
    }
}

void AbstractSocket::sendBuffer(void)
{
    constexpr unsigned char sendBitmask = 0x20;
    constexpr uint16_t SnCRRegisterAddress = 0x0001;
    writeControlRegister(SnCRRegisterAddress, &sendBitmask, 1);
}

void AbstractSocket::send(const char* data)
{
    uint16_t iterator = 0;

    while (data[iterator] != '\0')
    {
        iterator++;
    }

    uint16_t writePointerTX = getTXWritePointer();
    setTXReadPointer(writePointerTX);

    writeBufferRegister(writePointerTX, (unsigned char*) data, iterator);

    setTXWritePointer(writePointerTX + iterator);
    sendBuffer();
}

void AbstractSocket::enableInterrupts(const unsigned char& interruptMask)
{
    constexpr uint16_t SnIMRRegisterAddress = 0x002c;
    writeControlRegister(SnIMRRegisterAddress, &interruptMask, 1);
}

void AbstractSocket::eventOccured(void)
{
    unsigned char interruptRegister;
    constexpr uint16_t SnIRRegisterAddress = 0x0002;
    readControlRegister(SnIRRegisterAddress, &interruptRegister, 1);
    //writeControlRegister(SnIRRegisterAddress, &interruptRegister, 1); // Clearing fails in ISR but why??

    if (interruptRegister & (1 << 0x00))
        connected();

    if (interruptRegister & (1 << 0x01))
        disconnected();

    if (interruptRegister & (1 << 0x02))
        receivedMessage();

    if (interruptRegister & (1 << 0x03))
        timedOut();

    if (interruptRegister & (1 << 0x04))
        messageSent();
}

unsigned char AbstractSocket::getINTStatus(void)
{
    unsigned char interruptRegister;
    constexpr uint16_t SnIRRegisterAddress = 0x0002;
    readControlRegister(SnIRRegisterAddress, &interruptRegister, 1);
    return interruptRegister;
}

void AbstractSocket::connected(void) {}

void AbstractSocket::disconnected(void) {}

void AbstractSocket::receivedMessage(void) {}

void AbstractSocket::timedOut(void) {}

void AbstractSocket::messageSent(void) {}

uint16_t AbstractSocket::getTXWritePointer(void)
{
    unsigned char lengthArray[2] = {};
    constexpr uint16_t SnRXWRRegisterAddress = 0x0024;
    readControlRegister(SnRXWRRegisterAddress, lengthArray, 2);

    return (static_cast<uint16_t>(lengthArray[0]) << 8) + lengthArray[1];
}

void AbstractSocket::setTXWritePointer(const uint16_t& length)
{
    const unsigned char lengthArray[2] = {static_cast<unsigned char>((length >> 8) & 0xff),
                                          static_cast<unsigned char>(length & 0xff)};
    constexpr uint16_t SnRXWRRegisterAddress = 0x0024;
    writeControlRegister(SnRXWRRegisterAddress, lengthArray, 2);
}

void AbstractSocket::setTXReadPointer(const uint16_t& length)
{
    const unsigned char lengthArray[2] = {static_cast<unsigned char>((length >> 8) & 0xff),
                                          static_cast<unsigned char>(length & 0xff)};
    constexpr uint16_t SnRXWRRegisterAddress = 0x0022;
    writeControlRegister(SnRXWRRegisterAddress, lengthArray, 2);
}