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