/**
 *  \file   wiznet_w5500.cpp
 *  \brief  The file contains implementation for the W5500 class.
 */

#include "wiznet_w5500.hpp"

#include "../socket/tcp_socket.hpp"
#include "../socket/udp_socket.hpp"
#include <avr/io.h>

W5500::W5500(const MacAddress& macAddress,
             const HostAddress& gatewayIPv4Address,
             const SubnetMask& subnetMask,
             const HostAddress& sourceIPv4Address,
             volatile unsigned char& chipSelectDataDirectionRegister,
             volatile unsigned char& chipSelectPort,
             const uint8_t& chipSelectPin)
    : SpiDevice(chipSelectDataDirectionRegister, chipSelectPort, chipSelectPin)
{
    SpiBus::initialize();

    if (verify())
    {
        initRegister(macAddress, gatewayIPv4Address, subnetMask, sourceIPv4Address);
    }
}

W5500::W5500(const char* macAddress,
             const char* gatewayIPv4Address,
             const char* subnetMask,
             const char* sourceIPv4Address,
             volatile unsigned char& chipSelectDataDirectionRegister,
             volatile unsigned char& chipSelectPort,
             const uint8_t& chipSelectPin)
    : SpiDevice(chipSelectDataDirectionRegister, chipSelectPort, chipSelectPin)
{
    SpiBus::initialize(0x00);

    if (verify())
    {
        initRegister(MacAddress(macAddress),
                     HostAddress(gatewayIPv4Address),
                     SubnetMask(subnetMask),
                     HostAddress(sourceIPv4Address));
    }
}

bool W5500::verify(void)
{
    unsigned char versionNumber;
    readRegister(_chipVersionRegisterAddress, 0x00, &versionNumber, 1);
    return 0x04 == versionNumber;
}

bool W5500::setMACAddress(const MacAddress& macAddress)
{
    writeRegister(_macAddrRegisterAddress, 0x04, macAddress.toArray(), 6);

    unsigned char addressToValidate[6];
    readRegister(_macAddrRegisterAddress, 0x00, addressToValidate, 6);

    bool isSame = true;
    for (uint8_t i = 0; i < 6; i++)
    {
        isSame = isSame && macAddress.toArray()[i] == addressToValidate[i];
    }
    return isSame;
}

bool W5500::setGatewayAddress(const HostAddress& gatewayAddress)
{
    writeRegister(_gatewayAddrRegisterAddress, 0x04, gatewayAddress.toArray(), 4);

    unsigned char addressToValidate[4];
    readRegister(_gatewayAddrRegisterAddress, 0x00, addressToValidate, 4);

    bool isSame = true;
    for (uint8_t i = 0; i < 4; i++)
    {
        isSame = isSame && gatewayAddress.toArray()[i] == addressToValidate[i];
    }
    return isSame;
}

bool W5500::setSourceAddress(const HostAddress& sourceAddress)
{
    writeRegister(_sourceAddrRegisterAddress, 0x04, sourceAddress.toArray(), 4);

    unsigned char addressToValidate[4];
    readRegister(_sourceAddrRegisterAddress, 0x00, addressToValidate, 4);

    bool isSame = true;
    for (uint8_t i = 0; i < 4; i++)
    {
        isSame = isSame && sourceAddress.toArray()[i] == addressToValidate[i];
    }
    return isSame;
}

bool W5500::setSubnetMask(const SubnetMask& subnetMask)
{
    writeRegister(_subnetMaskRegisterAddress, 0x04, subnetMask.toArray(), 4);

    unsigned char addressToValidate[4];
    readRegister(_subnetMaskRegisterAddress, 0x00, addressToValidate, 4);

    bool isSame = true;
    for (uint8_t i = 0; i < 4; i++)
    {
        isSame = isSame && subnetMask.toArray()[i] == addressToValidate[i];
    }
    return isSame;
}

uint8_t W5500::registerSocket(AbstractSocket* socket)
{
    uint8_t targetIndex = 0x09;

    for (uint8_t i = 0; i < 8; i++)
    {
        if (!(_occupiedSocketMask & (1 << i)))
        {
            targetIndex = i;
            break;
        }
    }

    _socketList[targetIndex] = socket;

    _occupiedSocketMask |= (1 << targetIndex);
    return targetIndex;
}

void W5500::initRegister(const MacAddress& macAddress,
                         const HostAddress& gatewayAddress,
                         const SubnetMask& subnetMask,
                         const HostAddress& sourceAddress)
{
    resetRegister(_modeRegisterAddress);
    resetRegister(_phyConfigRegisterAddress);
    setMACAddress(macAddress);
    setGatewayAddress(gatewayAddress);
    setSubnetMask(subnetMask);
    setSourceAddress(sourceAddress);
    setInterruptLowLevelTimer(0xffff);
    enableSocketInterrupts();
}

void W5500::setInterruptLowLevelTimer(const uint16_t& value)
{
    const unsigned char valueInBytes[2] = {(value >> 8) & 0xff, value & 0xff};
    constexpr uint16_t INTLEVELREgisterAddresss = 0x0013;
    writeRegister(INTLEVELREgisterAddresss, 0x04, valueInBytes, 2);
}

void W5500::unsubscribeSocket(const uint8_t& index)
{
    _occupiedSocketMask &= ~(1 << index);
}

void W5500::resetRegister(const uint16_t& registerAddress)
{
    unsigned char tempRegister;

    readRegister(registerAddress, 0x00, &tempRegister, 1);
    tempRegister &= ~(1 << 7);
    writeRegister(registerAddress, 0x04, &tempRegister, 1);

    readRegister(registerAddress, 0x00, &tempRegister, 1);
    tempRegister |= (1 << 7);
    writeRegister(registerAddress, 0x04, &tempRegister, 1);
}

void W5500::enableSocketInterrupts(const unsigned char& interruptMask)
{
    writeRegister(_socketInterruptMaskRegister, 0x04, &interruptMask, 1);
}

void W5500::handleInterrupt(void)
{
    unsigned char interruptIndicator;
    readRegister(_socketInterruptRegister, 0x00, &interruptIndicator, 1);

    PORTA = ~interruptIndicator;

    for (uint8_t i = 0; i < 8; i++)
    {
        AbstractSocket* currentSocket = _socketList[i];

        if (currentSocket && interruptIndicator & (1 << i))
        {
            currentSocket->eventOccured();
        }
    }
}

bool W5500::resetSocketInterrupts(void)
{
    unsigned char interruptIndicator;
    readRegister(_socketInterruptRegister, 0x00, &interruptIndicator, 1);

    for (uint8_t i = 0; i < 8; i++)
    {
        AbstractSocket* currentSocket = _socketList[i];

        if (currentSocket)
        {
            currentSocket->resetInterrupts();
        }
    }

    readRegister(_socketInterruptRegister, 0x00, &interruptIndicator, 1);
    return 0x00 == interruptIndicator;
}

void W5500::writeRegister(const uint16_t& addressWord,
                          const unsigned char& controlByte,
                          const unsigned char* dataByteArray,
                          const uint8_t& dataByteCount)
{
    SpiDevice::select();

    SpiBus::sendByte(static_cast<uint8_t>(addressWord >> 8));
    SpiBus::sendByte(static_cast<uint8_t>(addressWord & 0xff));
    SpiBus::sendByte(controlByte);

    for (uint8_t i = 0; i < dataByteCount; i++)
    {
        SpiBus::sendByte(dataByteArray[i]);
    }

    SpiDevice::deselect();
}

void W5500::readRegister(const uint16_t& addressWord,
                         const unsigned char& controlByte,
                         unsigned char* dataByteArray,
                         const uint8_t& dataByteCount)
{
    SpiDevice::select();

    SpiBus::sendByte(addressWord >> 8);
    SpiBus::sendByte(addressWord & 0xff);
    SpiBus::sendByte(controlByte);

    for (uint8_t i = 0; i < dataByteCount; i++)
    {
        dataByteArray[i] = SpiBus::recvByte();
    }

    SpiDevice::deselect();
}