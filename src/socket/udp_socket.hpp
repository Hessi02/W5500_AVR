/**
 *  \file   udp_socket.hpp
 *  \brief  The file contains declaration for the UdpSocket class.
 */

#ifndef __UDP_SOCKET_HPP__
#define __UDP_SOCKET_HPP__

#include "abstract_socket.hpp"

/**
 *  \class  UdpSocket
 *  \brief  The class represents a W5500's UDP socket.
 */
class UdpSocket : public AbstractSocket
{
public:
    /**
     *  \fn             UdpSocket()
     *  \brief          The constructor initializes an instance of type 'UdpSocket'
     */
    UdpSocket(void);

    /**
     *  \fn       isOpen(void)
     *  \brief    Checks whether the socket is open or not.
     *  \return   Boolean indication the socket opening status.
     */
    virtual bool isOpen(void) override;

private:
    /**
     *  \fn     specifyType(void) 
     *  \brief  Specifies the socket type on the W5500 chip.
     */
    void specifyType(void);
};

#endif //__UDP_SOCKET_HPP__