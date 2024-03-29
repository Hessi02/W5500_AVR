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
     *  \fn             bind(W5500* chipInterface, const uint16_t& port) override        
     *  \brief          Binds the socket to a port of the passed chip.
     *  \param[inout]   chipInterface passes a pointer to the W5500 interface instance.
     *  \param[in]      port passes the 16 bit source port value.
     */
    virtual void bind(W5500* chipInterface, const uint16_t& port) override;

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

    /**
     *  \fn     waitForConnected(void) 
     *  \brief  Waits until a connection is established.
     *  \note   Socket must be listening to work properly.  
     */
    void waitForConnected(void);

private:
    /**
     *  \fn     specifyType(void) 
     *  \brief  Specifies the socket type on the W5500 chip.
     */
    void specifyType(void);
};

#endif //__TCP_SOCKET_HPP__