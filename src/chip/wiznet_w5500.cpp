/**
 *  \file   wiznet_w5500.cpp 
 *  \brief  The file contains implementation for the W5500 class.
 */

#include "wiznet_w5500.hpp"

#include "spi.hpp"

W5500::W5500(void)
{
	SPI::init();
	reset();
	initPHY();
}

void W5500::setGatewayAddress(const uint8_t *gatewayAddress) const
{
	constexpr uint16_t GARRegisterAddress = 0x0001;
	constexpr uint8_t gatewayAddressByteCount = 4;
	writeRegister(GARRegisterAddress, 0x04, gatewayAddress, gatewayAddressByteCount);
}

void W5500::setSubnetMaskAddress(const uint8_t *subnetMaskAddress) const
{
	constexpr uint16_t SUBRRegisterAddress = 0x0005; 
	constexpr uint8_t subnetMaskAddressByteCount = 4;
	writeRegister(SUBRRegisterAddress, 0x04, subnetMaskAddress, subnetMaskAddressByteCount);
}

void W5500::setSourceHardwareAddress(const uint8_t *sourceHardwareAddress) const
{
	constexpr uint16_t SHARRegisterAddress = 0x0009;
	constexpr uint8_t sourceHardwareAddressByteCount = 6;
	writeRegister(SHARRegisterAddress, 0x04, sourceHardwareAddress, sourceHardwareAddressByteCount);
}

void W5500::setSourceIPAddress(const uint8_t *sourceIPAddress) const
{
	constexpr uint16_t SIPRRegisterAddress = 0x000f;
	constexpr uint8_t sourceIPAddressByteCount = 4;
	writeRegister(SIPRRegisterAddress, 0x04, sourceIPAddress, sourceIPAddressByteCount);
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