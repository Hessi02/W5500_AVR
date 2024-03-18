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
     *  \param[in]      index passes the socket's index on the W5500.
     *  \param[in]      port passes the 16 bit source port value.
     */
    AbstractSocket(
        W5500* chipInterface,
        const uint8_t& index,
        const uint16_t& port);

    /**
     *  \fn         setLocalPort(void) const 
     *  \brief      Configures the source port number of the socket.
     *  \param[in]  port passes the local port to configure.
     */
    void setLocalPort(const uint16_t& port) const;

    /**
     *  \fn         setLocalAddress(const unsigned char* localIPv4Address) const
     *  \brief      Configures the local address of the socket.
     *  \param[in]  addressIPv4 passes the local IPv4 address in 4 bytes. 
     */
    void setLocalAddress(const unsigned char* addressIPv4) const;

    /**
     *  \fn         setDestinationPort(const uint16_t& port) const
     *  \brief      Configures the distination port number of the socket.
     *  \param[in]  port passes the destination port to configure.
     */
    void setDestinationPort(const uint16_t& port) const;

    /**
     *  \fn         setDestinationAddress(const unsigned char* addressIPv4) const
     *  \brief      Configures the destinationa address of the socket.
     *  \param[in]  addressIPv4 passses the destination address in 4 bytes.
     */
    void setDestinationAddress(const unsigned char* addressIPv4) const;

protected:
    /**
     *  \fn         setSocketType(const SocketType& socketType) const
     *  \brief      Configures the target socket type in W5500's registers.
     *  \param[in]  socketType passes the target 'SocketType'.  
     */
    void setSocketType(const SocketType& socketType) const;

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