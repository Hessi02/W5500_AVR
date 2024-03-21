/**
 *  \file   tcp_socket.hpp
 *  \brief  The file contains declaration for the TCPSocket class.
 */

#ifndef __TCP_SOCKET_HPP__
#define __TCP_SOCKET_HPP__

#include "abstract_socket.hpp"

/**
 *  \class  TCPSocket
 *  \brief  The class represents a W5500's TCP socket.
 */
class TCPSocket : public AbstractSocket
{
public:
    /**
     *  \fn             TCPSocket()
     *  \brief          The constructor initializes an instance of type 'TCPSocket'
     *  \param[inout]   chipInterface passes a pointer to the W5500 interface instance.
     *  \param[in]      port passes the 16 bit source port value.
     */
    TCPSocket(W5500* chipInterface, const uint16_t& port);

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
};

#endif //__TCP_SOCKET_HPP__