/**
 *  \file   tcp_socket.hpp
 *  \brief  The file contains declaration for the TcpSocket class.
 */

#ifndef __TCP_SOCKET_HPP__
#define __TCP_SOCKET_HPP__

#include "abstract_socket.hpp"

/**
 *  \class  TcpSocket
 *  \brief  The class represents a W5500's TCP socket.
 */
class TcpSocket : public AbstractSocket
{
public:
    /**
     *  \fn             TcpSocket()
     *  \brief          The constructor initializes an instance of type 'TcpSocket'
     */
    TcpSocket(void);

    /**
     *  \fn     listen(void)
     *  \brief  Listens for incoming TCP connections.
     */
    void listen(void);

    /**
     *  \fn       isOpen(void)
     *  \brief    Checks whether the socket is open or not.
     *  \return   Boolean indicating the socket's opening status.
     */
    virtual bool isOpen(void) override;

    /**
     *  \fn       isListening(void)
     *  \brief    Checks whether the socket is listening or not.
     *  \return   Boolaean indicating the socket's listening status.
     */
    bool isListening(void);

    /**
     *   \fn       isConnected(void)
     *   \brief    Checks whether the socket is connected or not.
     *   \return   Boolean indicating the socket's connection status.
     */
    bool isConnected(void);

private:
    /**
     *  \fn     specifyType(void) 
     *  \brief  Specifies the socket type on the W5500 chip.
     */
    virtual void specifyType(void) override;
};

#endif //__TCP_SOCKET_HPP__