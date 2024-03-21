/**
 *  \file   wiznet_w5500.hpp
 *  \brief  The file contains declaration for the W5500 class.
 */

#ifndef __WIZNET_W5500_HPP__
#define __WIZNET_W5500_HPP__

#include <stdint.h>

#include "../address/ipv4_address.hpp"
#include "../address/mac_address.hpp"
#include "../socket/tcp_socket.hpp"
#include "../socket/udp_socket.hpp"
#include "vector.hpp"

/**
 *  \class  W5500
 *  \brief  The class represents the Wiznet W5500 chip.
 */
class W5500
{
  public:
    /**
     * 	\fn			W5500()
     * 	\brief		The constructor initializes an instance of type 'W5500'.
     * 	\param[in]	macAddress passes the devices mac address.
     * 	\param[in]	gatewayIPv4Address passes the gateways IPv4 address.
     * 	\param[in]	subnetMask passes the networks subnet mask.
     * 	\param[in]	sourceIPv4Address passes the IPv4 address to use.
     */
    W5500 (
        const MACAddress &macAddress,
        const IPv4Address &gatewayIPv4Address,
        const SubnetMask &subnetMask,
        const IPv4Address &sourceIPv4Address);

    /**
     *	\fn		verify(void)
     * 	\brief 	Verifies the W5500 chip by its version number.
     * 	\return Boolean indicating the result of verification.
     */
    bool verify (void) const;

  private:
    /**
     * 	\fn		 	registerSocket(const AbstractSocket* socket)
     * 	\brief 		Registers a new socket instance.
     * 	\param[in]	socket passes a pointer to the socket instance to register.
     * 	\return 	The index for the socket to specify.
     */
    uint8_t registerSocket (AbstractSocket *socket);

    /**
     *	\fn			unsubscribeSocket(const uint8_t& index)
     * 	\brief		Unsubscribe the socket with the given index from the socket list.
     * 	\param[in]	index passes the socket's index to remove from the chip.
     */
    void unsubscribeSocket (const uint8_t &index);

    /**
     *	\fn			resetRegister(const uint16_t& registerAddress)
     * 	\brief		Reset a register of the W5500 chip at the passed address.
     * 	\param[in]	registerAddress passes the address of the register.
     * 	\note 		Only working if MSB of register is a RST bit!
     */
    void resetRegister (const uint16_t &registerAddress) const;

    /**
     *	\fn		reset(void)
     * 	\brief	Resets the registers of the W5500 chip.
     */
    void reset (void) const;

    /**
     * 	\fn		initPHY(void)
     * 	\brief	Initializes the W5500's PHY configuration.
     */
    void initPHY (void) const;

    /**
     *  \fn         writeRegister()
     *  \brief      Writes the passed data to the specified register address.
     *  \param[in]  addressWord passes the register address to write to.
     *  \param[in]  controlByte passes options for selecting various parameters.
     *  \param[in]  dataByteArray passes the data to send as an byte array.
     *  \param[in]  dataByteCount passes the length of the byte array.
     */
    void writeRegister (
        const uint16_t &addressWord,
        const unsigned char &controlByte,
        const unsigned char *dataByteArray,
        const uint8_t &dataByteCount) const;

    /**
     * 	\fn			readRegister()
     * 	\brief 		Reads the data of the specified register address.
     *  \param[in]  addressWord passes the address to read from.
     *  \param[in]  controlByte passes options for selecting various parameters.
     * 	\param[out]	dataByteArray passes the array to write the received data to.
     *  \param[in]  dataByteCount passes the length of the byte array to read.
     *	\return		Pointer to a C array containing the registers data.
     */
    void readRegister (
        const uint16_t &addressWord,
        const unsigned char &controlByte,
        unsigned char *dataByteArray,
        const uint8_t &dataByteCount) const;

  private:
    /**
     *	\var 	_socketList
     * 	\brief 	A list containing all active sockets of various types.
     */
    Vector<AbstractSocket *> _socketList;

    uint8_t _occupiedSocketMask = 0x00;

    friend class AbstractSocket;
};

#endif //__WIZNET_W5500_HPP__