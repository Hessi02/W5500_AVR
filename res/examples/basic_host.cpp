/**
 *  \file   basic_host.cpp
 *  \brief  This is an example file for an basic host send operation.
 *  
 *  The W5500 listens on PORT 1000. After a new connection is established,
 *  the chip sends "Hello World" to the client.
 */

#include "w5500.hpp"

int main(void)
{
    W5500 chip = W5500("00-08-dc-ff-ff-ff", "192.168.178.1", "255.255.255.0", "192.168.178.101");

    TcpSocket socket;
    socket.bind(&chip, 1000);
    socket.open();
    socket.listen();

    socket.waitForConnected();
    socket.send("Successfully connected to 192.168.178.101.");

    return 0;
}
