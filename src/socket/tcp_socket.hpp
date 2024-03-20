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
     *  \param[in]      index passes the socket's index on the W5500.
     *  \param[in]      port passes the 16 bit source port value.
     */
    TCPSocket(
        W5500* chipInterface,
        const uint8_t& index,
        const uint16_t& port);

    /**
     *  \fn     open(void)
     *  \brief  Opens and initializes the socket. 
     */
    void open(void);

    /**
     *  \fn     listen(void) 
     *  \brief  Listens for incoming TCP connections.
     */
    void listen(void);
};

#endif //__TCP_SOCKET_HPP__