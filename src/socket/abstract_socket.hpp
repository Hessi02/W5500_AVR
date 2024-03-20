/**
 *  \file   abstract_socket.hpp 
 *  \brief  The file contains declaration for the AbstractSocket class.
 */

#ifndef __ABSTRACT_SOCKET_HPP__
#define __ABSTRACT_SOCKET_HPP__

class W5500;

#include <stdint.h>

/**
 *  \class  AbstractSocket
 *  \brief  The class represents a base class for all socket types.
*/
class AbstractSocket
{
public:
    /**
     *  \enum   SocketType
     *  \brief  Enumeration of all known socket types of the W5500.
     */
    enum class SocketType
    {
        Closed = 0x00,
        TCP    = 0x01,
        UDP    = 0x02,
        MACRAW = 0x04
    };

    /**
     *  \fn             AbstractSocket()
     *  \brief          The constructor initializes an instance of type 'AbstractSocket'
     *  \param[inout]   chipInterface passes a pointer to the W5500 interface instance.
     *  \param[in]      port passes the 16 bit source port value.
     */
    AbstractSocket(
        W5500* chipInterface,
        const uint16_t& port = 42000);

    /**
     *  \fn         setLocalPort(void) 
     *  \brief      Configures the source port number of the socket.
     *  \param[in]  port passes the local port to configure.
     */
    void setLocalPort(const uint16_t& port);

    /**
     *  \fn         setDestinationPort(const uint16_t& port)
     *  \brief      Configures the distination port number of the socket.
     *  \param[in]  port passes the destination port to configure.
     */
    void setDestinationPort(const uint16_t& port);

    /**
     *  \fn         setDestinationAddress(const unsigned char* addressIPv4)
     *  \brief      Configures the destinationa address of the socket.
     *  \param[in]  addressIPv4 passses the destination address in 4 bytes.
     */
    void setDestinationAddress(const unsigned char* addressIPv4);

    /**
     *  \fn     open(void)
     *  \brief  Opens and initializes the socket. 
     */
    void open(void);

    /**
     *  \fn       isOpen(void)
     *  \brief    Checks whether the socket is open or not.  
     *  \return   Boolean indication the socket opening status.
     *  \todo     Make pure virtual methods possible...
     */
    virtual bool isOpen(void) {return false;}

protected:
    /**
     *  \fn         setSocketType(const SocketType& socketType)
     *  \brief      Configures the target socket type in W5500's registers.
     *  \param[in]  socketType passes the target 'SocketType'.  
     */
    void setSocketType(const SocketType& socketType);

    /**
	 *  \fn         writeControlRegister()
	 *  \brief      Writes the passed data to the specified register address.
	 *  \param[in]  addressWord passes the register address to write to.
	 *  \param[in]  dataByteArray passes the data to send as an byte array.
	 *  \param[in]  dataByteCount passes the length of the byte array.
	 */
	void writeControlRegister( 
		const uint16_t& addressWord,
		const unsigned char* dataByteArray,
		const uint8_t& dataByteCount);

	/**
	 * 	\fn			readControlRegister()
	 * 	\brief 		Reads the data of the specified register address.
	 *  \param[in]  addressWord passes the address to read from.
	 * 	\param[out]	dataByteArray passes the array to write the received data to. 
	 *  \param[in]  dataByteCount passes the length of the byte array to read.
	 *	\return		Pointer to a C array containing the registers data.
	 */
	void readControlRegister(
		const uint16_t& addressWord,
		unsigned char* dataByteArray,
		const uint8_t& dataByteCount);

private:
    /**
     *  \var    _chipInterface
     *  \brief  A pointer to the W5500 instance controlling the IP communication.
     */
    W5500* _chipInterface = nullptr;
    
    /**
     *  \var    _index
     *  \brief  A 8 bit integer representing the socket's index on the W5500.
     */
    uint8_t _index;
};

#endif //__ABSTRACT_SOCKET_HPP__