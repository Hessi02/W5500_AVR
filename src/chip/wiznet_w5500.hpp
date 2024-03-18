/**
 *  \file   wiznet_w5500.hpp 
 *  \brief  The file contains declaration for the W5500 class.
 */

#ifndef __WIZNET_W5500_HPP__
#define __WIZNET_W5500_HPP__

class AbstractSocket;

#include <stdint.h>
#include "vector.hpp"

/**
 *  \class  W5500
 *  \brief  The class represents the Wiznet W5500 chip. 
 */
class W5500
{
public:
	/**
	 * 	\fn		W5500(void)
	 * 	\brief	The constructor initializes an instance of type 'W5500'.
	 */
	W5500(void);

	/**
	 * 	\fn			setGatewayAddress(const unsigned char* gatewayAddress) const
	 *	\brief 		Sets the gateway address of the W5500 chip.
	 *	\param[in]	gatewayAddress passes the Gateway Address as a 4 Byte C-Array
	 */
	void setGatewayAddress(const unsigned char* gatewayAddress) const;

	/**
	 * 	\fn			setSubnetMaskAddress(const unsigned char* subnetMaskAddress) const
	 * 	\brief		Sets the subnet mask address of the w5500 chip.
	 *	\param[in]	subnetMaskAddress passes the Subnet Mask Address as a 4 Byte C-Array
	 */
	void setSubnetMaskAddress(const unsigned char* subnetMaskAddress) const;

	/**
	 * 	\fn			setSourceHardwareAddress(const unsigned char* sourceHardwareAddress) const
	 * 	\brief 		Sets the MAC Address of the W5500 chip.
	 *	\param[in] 	sourceHardwareAddress passes the MAC address as a 6 Byte C-Array
	 */
	void setSourceHardwareAddress(const unsigned char* sourceHardwareAddress) const;

	/**
	 * 	\fn			setSourceIPAddress(const unsigned char* sourceIPAddress) const
	 * 	\brief		Sets the IP Address oof the W5500 chip.
	 * 	\param[in]	sourceIPAddress passes the IP Address as a 4 Byte C-Array
	 */
	void setSourceIPAddress(const unsigned char* sourceIPAddress) const;

private:
	/**
	 *	\fn			resetRegister(const uint16_t& registerAddress) 
	 * 	\brief		Reset a register of the W5500 chip at the passed address.
	 * 	\param[in]	registerAddress passes the address of the register.
	 * 	\note 		Only working if MSB of register is a RST bit!
	 */	
	void resetRegister(const uint16_t& registerAddress) const;

	/**
	 *	\fn		reset(void) 
	 * 	\brief	Resets the registers of the W5500 chip.
	 */
	void reset(void) const;

	/**
	 * 	\fn		initPHY(void)
	 * 	\brief	Initializes the W5500's PHY configuration.
	 */
	void initPHY(void) const;

	/**
	 *  \fn         writeRegister()
	 *  \brief      Writes the passed data to the specified register address.
	 *  \param[in]  addressWord passes the register address to write to.
	 *  \param[in]  controlByte passes options for selecting various parameters.
	 *  \param[in]  dataByteArray passes the data to send as an byte array.
	 *  \param[in]  dataByteCount passes the length of the byte array.
	 */
	void writeRegister(
		const uint16_t& addressWord,
		const unsigned char& controlByte,
		const unsigned char* dataByteArray,
		const uint8_t& dataByteCount) const;

	/**
	 * 	\fn			readRegister()
	 * 	\brief 		Reads the data of the specified register address.
	 *  \param[in]  addressWord passes the address to read from.
	 *  \param[in]  controlByte passes options for selecting various parameters.
	 * 	\param[out]	dataByteArray passes the array to write the received data to. 
	 *  \param[in]  dataByteCount passes the length of the byte array to read.
	 *	\return		Pointer to a C array containing the registers data.
	 */
	void readRegister(
		const uint16_t& addressWord,
		const unsigned char& controlByte,
		unsigned char* dataByteArray,
		const uint8_t& dataByteCount) const;

private:
	/**
	 *	\var 	_socketList 
	 * 	\brief 	A list containing all active sockets of various types.
	 */
	Vector<AbstractSocket*> _socketList;
};

#endif //__WIZNET_W5500_HPP__