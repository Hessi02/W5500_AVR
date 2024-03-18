/**
 *  \file   abstract_socket.hpp 
 *  \brief  The file contains implementation for the AbstractSocket class.
 */

#include "abstract_socket.hpp"

AbstractSocket::AbstractSocket(
    W5500* chipInterface, 
    const uint8_t& index, 
    const uint16_t& port) :
_chipInterface(chipInterface),
_index(index)
{}

void AbstractSocket::setSocketType(const SocketType& socketType) const
{}

void AbstractSocket::setLocalPort(const uint16_t& port) const
{}

void AbstractSocket::setLocalAddress(const unsigned char* addressIPv4) const
{}

void AbstractSocket::setDestinationPort(const uint16_t& port) const
{}

void AbstractSocket::setDestinationAddress(const unsigned char* addressIPv4) const
{}
