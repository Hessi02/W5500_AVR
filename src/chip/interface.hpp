/**
 *  \file   interface.hpp
 *  \brief  The file contains declaration for the class 'Interface'.
 */

#ifndef __INTERFACE_HPP__
#define __INTERFACE_HPP__

#include "../address/host_address.hpp"
#include "../address/mac_address.hpp"
#include "../chip/wiznet_w5500.hpp"

class Interface
{
public:
    Interface();

    ~Interface();

private:
    const W5500* w5500;

    const HostAddress _sourceAddress;
    const HostAddress _gatewayAddress;
    const SubnetMask _subnetMask;
    const MacAddress _macAddress;
};

#endif //__INTERFACE_HPP__