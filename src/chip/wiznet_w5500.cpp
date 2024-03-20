/**
 *  \file   wiznet_w5500.cpp 
 *  \brief  The file contains implementation for the W5500 class.
 */

#include "wiznet_w5500.hpp"

#include "spi.hpp"
#include "../socket/tcp_socket.hpp"
#include "../socket/udp_socket.hpp"

W5500::W5500(
	const MACAddress& macAddress,
	const IPv4Address& gatewayIPv4Address,
	const SubnetMask& subnetMask,
	const IPv4Address& sourceIPv4Address)
{
	SPI::init();
	reset();
	initPHY();
	
	constexpr uint16_t SHARRegisterAddress = 0x0009;
	writeRegister(SHARRegisterAddress, 0x04, macAddress.toArray(), 6);

	constexpr uint16_t GARRegisterAddress = 0x0001;
	writeRegister(GARRegisterAddress, 0x04, gatewayIPv4Address.toArray(), 4);

	constexpr uint16_t SUBRRegisterAddress = 0x0005; 
	writeRegister(SUBRRegisterAddress, 0x04, subnetMask.toArray(), 4);

	constexpr uint16_t SIPRRegisterAddress = 0x000f;
	writeRegister(SIPRRegisterAddress, 0x04, sourceIPv4Address.toArray(), 4);
}

bool W5500::verify(void) const
{
	constexpr uint16_t VERSIONNRRegisterAddress = 0x0039;
	constexpr uint8_t byteCount = 1;

	unsigned char versionNumber;
	readRegister(VERSIONNRRegisterAddress, 0x00, &versionNumber, byteCount);

	return 0x04 == versionNumber;
}	

uint8_t W5500::registerSocket(AbstractSocket* socket)
{
	uint8_t targetIndex = 0x09;

	for(uint8_t i = 0; i < 8; i++)
	{
		if(!(_occupiedSocketMask & (1 << i)))
		{
			targetIndex = i;
			break;
		}
	}

	if (socket)
	{
		_socketList.append(socket);
	}	

	_occupiedSocketMask |= (1 << targetIndex);
	return targetIndex;
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

void W5500::reset(void) const
{
	constexpr uint16_t MRRegisterAddress = 0x0000;
	resetRegister(MRRegisterAddress);
}

void W5500::initPHY(void) const
{
	constexpr uint16_t PHYCFGRRegisterAddress = 0x002e;
	resetRegister(PHYCFGRRegisterAddress);
}

void W5500::writeRegister(
	const uint16_t& addressWord,
	const unsigned char& controlByte,
	const unsigned char* dataByteArray,
	const uint8_t& dataByteCount) const
{
	SPI::selectSlave();

	SPI::sendByte(static_cast<uint8_t>(addressWord >> 8));
	SPI::sendByte(static_cast<uint8_t>(addressWord & 0xff));
	SPI::sendByte(controlByte);

	for (uint8_t i = 0; i < dataByteCount; i++)
	{
		SPI::sendByte(dataByteArray[i]);
	}

	SPI::deselectSlave();
}

void W5500::readRegister(
    const uint16_t& addressWord,
	const unsigned char& controlByte,
	unsigned char* dataByteArray,
	const uint8_t& dataByteCount) const
{
	SPI::selectSlave();

	SPI::sendByte(addressWord >> 8);
	SPI::sendByte(addressWord & 0xff);
	SPI::sendByte(controlByte);

	for (uint8_t i = 0; i < dataByteCount; i++)
	{
		dataByteArray[i] = SPI::recvByte();
	}

	SPI::deselectSlave();
}