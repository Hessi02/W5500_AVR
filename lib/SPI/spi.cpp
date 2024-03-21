/**
 *	\file		spi.cpp
 *  \brief      The file contains function implementations for AVR's SPI communication.
 */

#include "spi.hpp"

#include <avr/io.h>

void
SPI::init (const unsigned char &mode)
{
    constexpr uint8_t ssPinIndex = 4;
    constexpr uint8_t mosiPinIndex = 5;
    constexpr uint8_t misoPinIndex = 6;
    constexpr uint8_t sckPinIndex = 7;

    DDRB |= (1 << ssPinIndex) | (1 << mosiPinIndex) | (1 << sckPinIndex);
    DDRB &= ~(1 << misoPinIndex);

    SPCR |= (1 << SPE) | (1 << MSTR) | (1 << SPR0);

    ((mode & 0b01) != 0 ? SPCR |= (1 << CPOL) : SPCR &= ~(1 << CPOL));
    ((mode & 0b10) != 0 ? SPCR |= (1 << CPHA) : SPCR &= ~(1 << CPHA));

    deselectSlave ();
}

void
SPI::sendByte (const unsigned char &byte)
{
    SPDR = byte;

    while (!(SPSR & (1 << SPIF)))
        {
            ;
        }
}

unsigned char
SPI::recvByte (void)
{
    SPDR = 0x00;

    while (!(SPSR & (1 << SPIF)))
        {
            ;
        }

    return SPDR;
}

void
SPI::selectSlave (void)
{
    constexpr uint8_t ssPin = 4;
    PORTB &= ~(1 << ssPin);
}

void
SPI::deselectSlave (void)
{
    constexpr uint8_t ssPin = 4;
    PORTB |= (1 << ssPin);
}