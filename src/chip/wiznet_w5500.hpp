/**
 *  \file   wiznet_w5500.hpp
 *  \brief  The file contains declaration for the W5500 class.
 */

#ifndef __WIZNET_W5500_HPP__
#define __WIZNET_W5500_HPP__

#include <avr/io.h>
#include <avr_spi.hpp>
#include <stdint.h>

#include "../address/host_address.hpp"
#include "../address/mac_address.hpp"
#include "../callback/callback.hpp"
#include "../socket/tcp_socket.hpp"
#include "../socket/udp_socket.hpp"

/**
 *  \class  W5500
 *  \brief  The class represents the Wiznet W5500 chip.
 */
class W5500 : public SpiDevice, public CallbackInstance
{
public:
    /**
     * 	\fn			  W5500()
     * 	\brief		  The constructor initializes an instance of type 'W5500'.
     * 	\param[in]	  macAddress passes the devices mac address.
     * 	\param[in]	  gatewayIPv4Address passes the gateways IPv4 address.
     * 	\param[in]	  subnetMask passes the networks subnet mask.
     * 	\param[in]	  sourceIPv4Address passes the IPv4 address to use.
     *  \param[inout] chipSelectDataDirectionRegister passes the DDR for the SPI CS pin.
     *  \param[inout] chipSelectPort passes the PORT for the SPI CS pin.
     *  \param[inout] chipSelectPin passes the SPI CS pin's index.
     */
    W5500(const MacAddress& macAddress,
          const HostAddress& gatewayIPv4Address,
          const SubnetMask& subnetMask,
          const HostAddress& sourceIPv4Address,
          volatile unsigned char& chipSelectDataDirectionRegister = DDRB,
          volatile unsigned char& chipSelectPort = PORTB,
          const uint8_t& chipSelectPin = 0x04);

    /**
     * 	\fn		      W5500()
     * 	\brief	      The constructor initializes an instance of type 'W5500'.
     * 	\param[in]	  macAddress passes the devices mac address as a string.
     * 	\param[in]	  gatewayIPv4Address passes the gateways IPv4 address as a string.
     * 	\param[in]	  subnetMask passes the networks subnet mask as a string.
     * 	\param[in]	  sourceIPv4Address passes the IPv4 address to use as a string.
     *  \param[inout] chipSelectDataDirectionRegister passes the DDR for the SPI CS pin.
     *  \param[inout] chipSelectPort passes the PORT for the SPI CS pin.
     *  \param[inout] chipSelectPin passes the SPI CS pin's index.
     */
    W5500(const char* macAddress,
          const char* gatewayIPv4Address,
          const char* subnetMask,
          const char* sourceIPv4Address,
          volatile unsigned char& chipSelectDataDirectionRegister = DDRB,
          volatile unsigned char& chipSelectPort = PORTB,
          const uint8_t& chipSelectPin = 0x04);

    /**
     *	\fn		verify(void)
     * 	\brief 	Verifies the W5500 chip by its version number.
     * 	\return Boolean indicating the result of verification.
     */
    bool verify(void);

    /**
     *  \fn         setMACAddress(const MacAddress& macAddress) const         
     *  \brief      Sets and validates the MAC address of the chip.
     *  \param[in]  macAddress passes the MAC address to set.
     *  \return     Indicating success of the writing operation.
     */
    bool setMACAddress(const MacAddress& macAddress);

    /**
     *  \fn         setGatewayAddress(const HostAddress& gatewayAddress) const
     *  \brief      Sets and validates the gateway address of the chip.
     *  \param[in]  gatewayAddress passes the IP address to set.
     *  \return     Indicating success of the writing operation.
     */
    bool setGatewayAddress(const HostAddress& gatewayAddress);

    /**
     *  \fn         setSourceAddress(const HostAddress& sourceAddress) const
     *  \brief      Sets and validates the source address of the chip.
     *  \param[in]  soureceAddress passes the IP address to set.
     *  \return     Indicating success of the writing operation.
     */
    bool setSourceAddress(const HostAddress& sourceAddress);

    /**
     *  \fn         setSubnetMask(const SubnetMask& subnetMask) const
     *  \brief      Sets and validates the subnet mask of the chip.
     *  \param[in]  subnetMask passes the subnet mask to set.
     *  \return     Indicating success of the writing operation.
     */
    bool setSubnetMask(const SubnetMask& subnetMask);

    /**
     *  \fn     handleInterupt(void) 
     *  \brief  Handles an new issued hardware interupt.
     */
    void handleInterrupt(void);

    /**
     *  \fn     resetSocketInterrupts(void)
     *  \brief  Resets all acitve socket interrupt flags.
     */
    bool resetSocketInterrupts(void);

    /**
     * 	\fn		 	registerSocket(const AbstractSocket* socket)
     * 	\brief 		Registers a new socket instance.
     * 	\param[in]	socket passes a pointer to the socket instance to register.
     * 	\return 	The index for the socket to specify.
     */
    uint8_t registerSocket(AbstractSocket* socket);

    /**
     *	\fn			unsubscribeSocket(const uint8_t& index)
     * 	\brief		Unsubscribe the socket with the given index from the socket list.
     * 	\param[in]	index passes the socket's index to remove from the chip.
     */
    void unsubscribeSocket(const uint8_t& index);

private:
    /**
     * 	\fn			initRegister()
     * 	\brief		Initializes the basic registers of the 'W5500'.
     * 	\param[in]	macAddress passes the devices mac address.
     * 	\param[in]	gatewayIPv4Address passes the gateways IPv4 address.
     * 	\param[in]	subnetMask passes the networks subnet mask.
     * 	\param[in]	sourceIPv4Address passes the IPv4 address to use.
     */
    void initRegister(const MacAddress& macAddress,
                      const HostAddress& gatewayIPv4Address,
                      const SubnetMask& subnetMask,
                      const HostAddress& sourceIPv4Address);

    /**
     *  \fn         setInterruptLowLevelTimer(const uint16_t& value)
     *  \brief      Sets the low level timer value of the W5500 INT.
     *  \param[in]  value passes the value to assign.
     */
    void setInterruptLowLevelTimer(const uint16_t& value);

    /**
     *	\fn			resetRegister(const uint16_t& registerAddress)
     * 	\brief		Reset a register of the W5500 chip at the passed address.
     * 	\param[in]	registerAddress passes the address of the register.
     * 	\note 		Only working if MSB of register is a RST bit!
     */
    void resetRegister(const uint16_t& registerAddress);

    /**
     *  \fn         enableSocketInterrupts(const unsigned char& interruptMask = 0xff)     
     *  \brief      Enables the socket interrupts according to passed mask.
     *  \param[in]  interruptMask passes the interrupt value for each sockets represented as bit. 
     */
    void enableSocketInterrupts(const unsigned char& interruptMask = 0xff);

    /**
     *  \fn         writeRegister()
     *  \brief      Writes the passed data to the specified register address.
     *  \param[in]  addressWord passes the register address to write to.
     *  \param[in]  controlByte passes options for selecting various parameters.
     *  \param[in]  dataByteArray passes the data to send as an byte array.
     *  \param[in]  dataByteCount passes the length of the byte array.
     */
    void writeRegister(const uint16_t& addressWord,
                       const unsigned char& controlByte,
                       const unsigned char* dataByteArray,
                       const uint8_t& dataByteCount);

    /**
     * 	\fn			readRegister()
     * 	\brief 		Reads the data of the specified register address.
     *  \param[in]  addressWord passes the address to read from.
     *  \param[in]  controlByte passes options for selecting various parameters.
     * 	\param[out]	dataByteArray passes the array to write the received data to.
     *  \param[in]  dataByteCount passes the length of the byte array to read.
     *	\return		Pointer to a C array containing the registers data.
     */
    void readRegister(const uint16_t& addressWord,
                      const unsigned char& controlByte,
                      unsigned char* dataByteArray,
                      const uint8_t& dataByteCount);

    /**
     *	\var 	_socketList
     * 	\brief 	A list containing all active sockets of various types.
     */
    AbstractSocket* _socketList[8] = {};

    /**
     *  \var    _occupiedSocketMask
     *  \brief  Indicates the occupied hardware sockets of the W5500. 
     */
    uint8_t _occupiedSocketMask = 0x00;

    /**
     *  \var    _modeRegisterAddress
     *  \brief  Used for S/W reset, ping block mode and PPPoE mode.
     */
    const uint16_t _modeRegisterAddress = 0x0000;

    /**
     *  \var    _gatewayAddrRegisterAddress
     *  \brief  Configures the default gateway address.

     */
    const uint16_t _gatewayAddrRegisterAddress = 0x0001;

    /**
     *  \var    _subnetMaskRegisterAddress
     *  \brief  Configures the subnet mask address.
     */
    const uint16_t _subnetMaskRegisterAddress = 0x0005;

    /**
     *  \var    _macAddrRegisterAddress
     *  \brief  Configures the source hardware address
     */
    const uint16_t _macAddrRegisterAddress = 0x0009;

    /**
     *  \var    _sourceAddrRegisterAddr
     *  \brief  Configures the source IP address.
     */
    const uint16_t _sourceAddrRegisterAddress = 0x000f;

    /**
     *  \var    _socketInterruptRegister
     *  \brief  Indicates the socket that called an interrupt.
     */
    const uint16_t _socketInterruptRegister = 0x0017;

    /**
     *  \var    _socketInterruptMaskRegister
     *  \brief  Configures socket's that call interrupts.
     */
    const uint16_t _socketInterruptMaskRegister = 0x0018;

    /**
     *  \var    _pyhConfigRegisterAddress
     *  \brief  Configures PHY operation mode and resets PHY. 
     */
    const uint16_t _phyConfigRegisterAddress = 0x002e;

    /**
     *  \var    _chipVersionRegisterAddress
     *  \brief  Contains the chip version.
     *  \note   VERSIONR always indicates the W5500 version as 0x04.
     */
    const uint16_t _chipVersionRegisterAddress = 0x0039;

    friend class AbstractSocket;
};

#endif //__WIZNET_W5500_HPP__