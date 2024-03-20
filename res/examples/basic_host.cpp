/**
 *  \file   basic_host.cpp
 *  \brief  This is an example file for an basic host send operation.
 *  
 *  The W5500 listens on PORTS 1000 - 1007. After a new connection on
 *  a specific port, the chip sends "Hello World" in a loop with a
 *  frequency of 2 Hz. The example uses the 'Vector' container. This 
 *  is not required to make this example work.
 */

#include <util/delay.h>
#include "w5500.hpp"
#include "vector.hpp"

int main(void)
{
    const IPv4Address gatewayAddress("192.168.178.1");
    const IPv4Address sourceAddress("192.168.178.101");
    const SubnetMask subnetMask("255.255.255.0");
    const MACAddress macAddress("00-08-dc-ff-ff-ff");

    W5500 chip = W5500(macAddress, gatewayAddress, subnetMask, sourceAddress);

    Vector<TCPSocket*> sockets;

    for(uint8_t i = 0; i < 8; i++)
    {
        TCPSocket* newSocket = new TCPSocket(&chip, 1000 + i); 
        newSocket->open();
        newSocket->listen(); 
        sockets.append(newSocket);
    }

    while(true)
    {
        for(uint8_t i = 0; i < 8; i++)
        {
            TCPSocket* currentSocket = sockets.at(i); 
            if(currentSocket->isConnected())
            {
                currentSocket->send("Hello, World!\n");
            }
        }

        _delay_ms(500);
    }

    return 0;
}