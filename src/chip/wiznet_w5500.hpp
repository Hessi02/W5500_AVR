/**
 *  \file   wiznet_w5500.hpp 
 *  \brief  The file contains declaration for the W5500 class.
 */

#ifndef __WIZNET_W5500_HPP__
#define __WIZNET_W5500_HPP__

#include <stdint.h>

/**
 *  \class  W5500
 *  \brief  The class represents the Wiznet W5500 chip. 
 */
class W5500
{
private:
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
			const uint8_t& controlByte,
			const uint8_t* dataByteArray,
			const uint8_t& dataByteCount) const;

		/**
		 * 	\fn			readRegister()
		 * 	\brief 		Reads the data of the specified register address.
		 *  \param[in]  addressWord passes the address to read from.
		 *  \param[in]  controlByte passes options for selecting various parameters.
		 *  \param[in]  byteCount passes the length of the byte array to read.
		 *	\return		Pointer to a C array containing the registers data.
		 */
		uint8_t* readRegister(
			const uint16_t& addressWord,
			const uint8_t& controlByte,
			const uint8_t& byteCount) const;
};

#endif //__WIZNET_W5500_HPP__