/**
 *  \file   ipv4_address.cpp
 *  \brief  The file contains implementations for the class 'HostAddress'.
 */

#include "host_address.hpp"

#include <stdint.h>

HostAddress::HostAddress(const char* addressAsString)
{
    if (validateAddressString(addressAsString)) {
        parseAddressString(addressAsString);
    }
}

bool HostAddress::validateAddressString(const char* addressAsString) const
{
    uint8_t iterator = 0;
    uint8_t periodCounter = 0;

    while (addressAsString[iterator] != '\0') {
        if (addressAsString[iterator] == '.') {
            periodCounter++;
        }

        iterator++;
    }

    return periodCounter == 3;
}

void HostAddress::parseAddressString(const char* addressString)
{
    uint8_t iterator = 0;

    for (uint8_t i = 0; i < 4; i++) {
        uint8_t innerIterator = 0;
        char digitAsByteArray[3] = {};

        while (addressString[iterator] != '.' && addressString[iterator] != '\0') {
            digitAsByteArray[innerIterator] = addressString[iterator];
            innerIterator++;
            iterator++;
        }

        if (innerIterator == 1) {
            digitAsByteArray[2] = digitAsByteArray[0];
            digitAsByteArray[1] = '0';
            digitAsByteArray[0] = '0';
        } else if (innerIterator == 2) {
            digitAsByteArray[2] = digitAsByteArray[1];
            digitAsByteArray[1] = digitAsByteArray[0];
            digitAsByteArray[0] = '0';
        }

        unsigned char byteAsNum = 0x00;

        for (uint8_t n = 0; n < 3; n++) {
            uint8_t currentDigit = digitAsByteArray[2 - n] - '0';

            for (uint8_t r = 0; r < n; r++) {
                currentDigit *= 10;
            }

            byteAsNum += currentDigit;
        }

        _bytes[i] = byteAsNum;

        iterator++;
    }
}

const unsigned char* HostAddress::toArray(void) const
{
    return _bytes;
}
