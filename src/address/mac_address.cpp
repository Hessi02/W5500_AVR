/**
 *  \file   mac_address.cpp
 *  \brief  The file contains implementations for the class 'MacAddress'.
 */

#include "mac_address.hpp"

#include <stdint.h>

MacAddress::MacAddress(const char* addressAsString)
{
    if (validateAddressString(addressAsString))
    {
        char addressInTwoDim[6][2] = {};
        parseToTwoDim(addressAsString, addressInTwoDim);
        convertCharToInt(addressInTwoDim);
    }
}

bool MacAddress::validateAddressString(const char* addressAsString) const
{
    uint8_t iterator = 0;
    uint8_t periodCounter = 0;

    while (addressAsString[iterator] != '\0')
    {
        if (addressAsString[iterator] == '-')
        {
            periodCounter++;
        }

        iterator++;
    }

    return periodCounter == 5;
}

void MacAddress::parseToTwoDim(const char* addressString, char addressInTwoDim[6][2]) const
{
    uint8_t globalIterator = 0;

    for (uint8_t i = 0; i < 6; i++)
    {
        for (uint8_t n = 0; n < 2; n++)
        {
            addressInTwoDim[i][n] = addressString[globalIterator];
            globalIterator++;
        }
        globalIterator++;
    }
}

void MacAddress::convertCharToInt(const char addressInTwoDim[6][2])
{
    for (uint8_t i = 0; i < 6; i++)
    {
        unsigned char totalByte = 0x00;

        for (uint8_t n = 0; n < 2; n++)
        {
            if (addressInTwoDim[i][n] >= 'a' && addressInTwoDim[i][n] <= 'f')
            {
                totalByte += (addressInTwoDim[i][n] + 0xa - 'a') * (n == 0 ? 0x10 : 1);
            }
            else if (addressInTwoDim[i][n] >= '0' && addressInTwoDim[i][n] <= '9')
            {
                totalByte += (addressInTwoDim[i][n] - '0') * (n == 0 ? 0x10 : 1);
            }
        }

        _bytes[i] = totalByte;
    }
}

const unsigned char* MacAddress::toArray(void) const
{
    return _bytes;
}
