/**
 *  \file   wiznet_w5500.cpp
 *  \brief  The file contains implementation for the W5500 class.
 */

#include "wiznet_w5500.hpp"

#include "../socket/tcp_socket.hpp"
#include "../socket/udp_socket.hpp"
#include "spi.hpp"

W5500::W5500(const MACAddress& macAddress,
             const IPv4Address& gatewayIPv4Address,
             const SubnetMask& subnetMask,
             const IPv4Address& sourceIPv4Address)
{
    SPI::init();

    if (verify()) {
        initRegister(macAddress, gatewayIPv4Address, subnetMask, sourceIPv4Address);
    }
}

W5500::W5500(const char* macAddress,
             const char* gatewayIPv4Address,
             const char* subnetMask,
             const char* sourceIPv4Address)
{
    SPI::init();

    if (verify()) {
        initRegister(MACAddress(macAddress),
                     IPv4Address(gatewayIPv4Address),
                     SubnetMask(subnetMask),
                     IPv4Address(sourceIPv4Address));
    }
}

bool W5500::verify(void) const
{
    unsigned char versionNumber;
    readRegister(_chipVersionRegisterAddress, 0x00, &versionNumber, 1);
    return 0x04 == versionNumber;
}

bool W5500::setMACAddress(const MACAddress& macAddress) const
{
    writeRegister(_macAddrRegisterAddress, 0x04, macAddress.toArray(), 6);

    unsigned char addressToValidate[6];
    readRegister(_macAddrRegisterAddress, 0x00, addressToValidate, 6);

    bool isSame = true;
    for (uint8_t i = 0; i < 6; i++) {
        isSame = isSame && macAddress.toArray()[i] == addressToValidate[i];
    }
    return isSame;
}

bool W5500::setGatewayAddress(const IPv4Address& gatewayAddress) const
{
    writeRegister(_gatewayAddrRegisterAddress, 0x04, gatewayAddress.toArray(), 4);

    unsigned char addressToValidate[4];
    readRegister(_gatewayAddrRegisterAddress, 0x00, addressToValidate, 4);

    bool isSame = true;
    for (uint8_t i = 0; i < 4; i++) {
        isSame = isSame && gatewayAddress.toArray()[i] == addressToValidate[i];
    }
    return isSame;
}

bool W5500::setSourceAddress(const IPv4Address& sourceAddress) const
{
    writeRegister(_sourceAddrRegisterAddress, 0x04, sourceAddress.toArray(), 4);

    unsigned char addressToValidate[4];
    readRegister(_sourceAddrRegisterAddress, 0x00, addressToValidate, 4);

    bool isSame = true;
    for (uint8_t i = 0; i < 4; i++) {
        isSame = isSame && sourceAddress.toArray()[i] == addressToValidate[i];
    }
    return isSame;
}

bool W5500::setSubnetMask(const SubnetMask& subnetMask) const
{
    writeRegister(_subnetMaskRegisterAddress, 0x04, subnetMask.toArray(), 4);

    unsigned char addressToValidate[4];
    readRegister(_subnetMaskRegisterAddress, 0x00, addressToValidate, 4);

    bool isSame = true;
    for (uint8_t i = 0; i < 4; i++) {
        isSame = isSame && subnetMask.toArray()[i] == addressToValidate[i];
    }
    return isSame;
}

uint8_t W5500::registerSocket(AbstractSocket* socket)
{
    uint8_t targetIndex = 0x09;

    for (uint8_t i = 0; i < 8; i++) {
        if (!(_occupiedSocketMask & (1 << i))) {
            targetIndex = i;
            break;
        }
    }

    if (socket) {
        _socketList.append(socket);
    }

    _occupiedSocketMask |= (1 << targetIndex);
    return targetIndex;
}

void W5500::initRegister(const MACAddress& macAddress,
                         const IPv4Address& gatewayAddress,
                         const SubnetMask& subnetMask,
                         const IPv4Address& sourceAddress) const
{
    resetRegister(_modeRegisterAddress);
    resetRegister(_phyConfigRegisterAddress);
    setMACAddress(macAddress);
    setGatewayAddress(gatewayAddress);
    setSubnetMask(subnetMask);
    setSourceAddress(sourceAddress);
}

void W5500::unsubscribeSocket(const uint8_t& index)
{
    _occupiedSocketMask &= ~(1 << index);
}

void W5500::resetRegister(const uint16_t& registerAddress) const
{
    unsigned char tempRegister;

    readRegister(registerAddress, 0x00, &tempRegister, 1);
    tempRegister &= ~(1 << 7);
    writeRegister(registerAddress, 0x04, &tempRegister, 1);

    readRegister(registerAddress, 0x00, &tempRegister, 1);
    tempRegister |= (1 << 7);
    writeRegister(registerAddress, 0x04, &tempRegister, 1);
}

void W5500::writeRegister(const uint16_t& addressWord,
                          const unsigned char& controlByte,
                          const unsigned char* dataByteArray,
                          const uint8_t& dataByteCount) const
{
    SPI::selectSlave();

    SPI::sendByte(static_cast<uint8_t>(addressWord >> 8));
    SPI::sendByte(static_cast<uint8_t>(addressWord & 0xff));
    SPI::sendByte(controlByte);

    for (uint8_t i = 0; i < dataByteCount; i++) {
        SPI::sendByte(dataByteArray[i]);
    }

    SPI::deselectSlave();
}

void W5500::readRegister(const uint16_t& addressWord,
                         const unsigned char& controlByte,
                         unsigned char* dataByteArray,
                         const uint8_t& dataByteCount) const
{
    SPI::selectSlave();

    SPI::sendByte(addressWord >> 8);
    SPI::sendByte(addressWord & 0xff);
    SPI::sendByte(controlByte);

    for (uint8_t i = 0; i < dataByteCount; i++) {
        dataByteArray[i] = SPI::recvByte();
    }

    SPI::deselectSlave();
}