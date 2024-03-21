/**
 *  \file   udp_socket.hpp
 *  \brief  The file contains declaration for the UDPSocket class.
 */

#ifndef __UDP_SOCKET_HPP__
#define __UDP_SOCKET_HPP__

#include "abstract_socket.hpp"

/**
 *  \class  UDPSocket
 *  \brief  The class represents a W5500's UDP socket.
 */
class UDPSocket : public AbstractSocket
{
  public:
    /**
     *  \fn             UDPSocket()
     *  \brief          The constructor initializes an instance of type 'UDPSocket'
     *  \param[inout]   chipInterface passes a pointer to the W5500 interface instance.
     *  \param[in]      port passes the 16 bit source port value.
     */
    UDPSocket (
        W5500 *chipInterface,
        const uint16_t &port);

    /**
     *  \fn       isOpen(void)
     *  \brief    Checks whether the socket is open or not.
     *  \return   Boolean indication the socket opening status.
     */
    virtual bool isOpen (void) override;
};

#endif //__UDP_SOCKET_HPP__