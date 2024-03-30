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

void AbstractSocket::readRXBufferRegister(const uint16_t& addressRegister,
                                          unsigned char* data,
                                          const uint8_t& length)
{
    if (_chipInterface)
    {
        const unsigned char controlByte = 0x18 | (_index << 5);
        _chipInterface->readRegister(addressRegister, controlByte, data, length);
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

    writeBufferRegister(writePointerTX, (unsigned char*) data, iterator);

    setTXWritePointer(writePointerTX + iterator);
    sendBuffer();
}

char* AbstractSocket::recv(void)
{
    unsigned char receivedSizeValue[2];
    constexpr uint16_t SnRXRXRRegisterAddress = 0x0026;
    readControlRegister(SnRXRXRRegisterAddress, receivedSizeValue, 2);

    const uint16_t receivedByteCount = (static_cast<uint16_t>(receivedSizeValue[0]) << 8)
                                       + receivedSizeValue[1];

    const uint16_t readPointer = getRXReadPointer();

    unsigned char buffer[receivedByteCount] = {};
    readRXBufferRegister(readPointer, buffer, receivedByteCount);

    setRXReadPointer(readPointer + receivedByteCount);

    constexpr uint16_t SNCRRegisterAddress = 0x0001;
    constexpr unsigned char receiveCommand = 0x40;
    writeControlRegister(SNCRRegisterAddress, &receiveCommand, 1);

    return nullptr;
}

bool AbstractSocket::resetInterrupts(void)
{
    constexpr uint16_t SnIRRegisterAddress = 0x0002;
    unsigned char resetMask;
    readControlRegister(SnIRRegisterAddress, &resetMask, 1);
    writeControlRegister(SnIRRegisterAddress, &resetMask, 1);

    unsigned char resetResult;
    readControlRegister(SnIRRegisterAddress, &resetResult, 1);

    return 0x00 == resetResult;
}

void AbstractSocket::addCallbackFunction(void (AbstractSocket::*signal)(void),
                                         void (*callbackFunction)(void))
{
    if (signal == &AbstractSocket::eventOccured)
    {
        _eventOccuredCallbackFunctionList.append(callbackFunction);
    }
    else if (signal == &AbstractSocket::receivedMessage)
    {
        _receivedMessageCallbackFunctionList.append(callbackFunction);
    }
}

void AbstractSocket::addCallback(void (AbstractSocket::*signal)(void), Callback& callback)
{
    if (signal == &AbstractSocket::eventOccured)
    {
        _eventOccuredCallbackInstanceList.append(callback);
    }
    else if (signal == &AbstractSocket::receivedMessage)
    {
        _receivedMessageCallbackInstanceList.append(callback);
    }
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

    for (void (*onEventCallback)(void) : _eventOccuredCallbackFunctionList)
    {
        onEventCallback();
    }

    for (Callback callbackInstance : _eventOccuredCallbackInstanceList)
    {
        callbackInstance.fire();
    }

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

void AbstractSocket::connected(void)
{
    send("Connected to 192.168.178.101!\n\r");
}

void AbstractSocket::disconnected(void) {}

void AbstractSocket::receivedMessage(void)
{
    for (void (*onNewMessageCallbackFunction)(void) : _receivedMessageCallbackFunctionList)
    {
        onNewMessageCallbackFunction();
    }

    for (Callback callbackInstance : _receivedMessageCallbackInstanceList)
    {
        callbackInstance.fire();
    }
}

void AbstractSocket::timedOut(void) {}

void AbstractSocket::messageSent(void) {}

uint16_t AbstractSocket::getTXWritePointer(void)
{
    unsigned char lengthArray[2] = {};
    constexpr uint16_t SnTXWRRegisterAddress = 0x0024;
    readControlRegister(SnTXWRRegisterAddress, lengthArray, 2);
    return (static_cast<uint16_t>(lengthArray[0]) << 8) + lengthArray[1];
}

uint16_t AbstractSocket::getRXReadPointer(void)
{
    unsigned char lengthArray[2] = {};
    constexpr uint16_t SnRXRDRegisterAddress = 0x0028;
    readControlRegister(SnRXRDRegisterAddress, lengthArray, 2);
    return (static_cast<uint16_t>(lengthArray[0]) << 8) + lengthArray[1];
}

uint16_t AbstractSocket::getRXWritePointer(void)
{
    unsigned char lengthArray[2] = {};
    constexpr uint16_t SnRXWRRegisterAddress = 0x002a;
    readControlRegister(SnRXWRRegisterAddress, lengthArray, 2);
    return (static_cast<uint16_t>(lengthArray[0]) << 8) + lengthArray[1];
}

void AbstractSocket::setRXReadPointer(const uint16_t position)
{
    const unsigned char lengthArray[2] = {static_cast<unsigned char>((position >> 8) & 0xff),
                                          static_cast<unsigned char>(position & 0xff)};
    constexpr uint16_t SnRXRDRegisterAddress = 0x0028;
    writeControlRegister(SnRXRDRegisterAddress, lengthArray, 2);
}

void AbstractSocket::setTXWritePointer(const uint16_t& length)
{
    const unsigned char lengthArray[2] = {static_cast<unsigned char>((length >> 8) & 0xff),
                                          static_cast<unsigned char>(length & 0xff)};
    constexpr uint16_t SnRXWRRegisterAddress = 0x0024;
    writeControlRegister(SnRXWRRegisterAddress, lengthArray, 2);
}