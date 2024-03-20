/**
 *  \file   ipv4_address.hpp   
 *  \brief  The file contains declarations for the class 'IPv4Address'.
 */

#ifndef __IPV4_ADDRESS_HPP__
#define __IPV4_ADDRESS_HPP__

/**
 *  \class  IPv4Address
 *  \brief  The class represents a four byte IP address (IPv4).
 */
class IPv4Address
{
public:
    /**
     *  \fn         IPv4Address(const char* adressAsString)
     *  \brief      The constructor initializes an element of type 'IPv4Address'.
     *  \param[in]  addressAsString passes the address in a C string (char[]).
     */
    IPv4Address(const char* addressASString);

    /**
     *  \fn         validateAddressString(const char* addressAsString) const
     *  \brief      Validates the string as an IPv4 address.
     *  \param[in]  addressAsString passes the address in a C string (char[]).
     *  \return     Boolean validating the passed string. 
     */  
    bool validateAddressString(const char* addressAsString) const;

    /**
     *  \fn         parseAddressString(const char* addressString)
     *  \brief      Parses the address and writes it into _bytes.
     *  \param[in]  addressAsString passes the address in a C string (char[]).
     */
    void parseAddressString(const char* addressString);

    /**
     *  \fn       toArray(void)
     *  \brief    Returns the IPv4 address in four bytes.
     *  \return   Array of uinsigned chars representing the address.
     */
    const unsigned char* toArray(void) const; 

private:
    /**
     *  \var    _bytes
     *  \brief  The array contains the bytes of the IP address.
     */
    unsigned char _bytes[4] = {};
};

/**
 *  \typedef    SubnetMask
 *  \brief      The subnet mask uses the same form as an IPv4Address.
 */
typedef IPv4Address SubnetMask;

#endif //__IPV4_ADDRESS_HPP__