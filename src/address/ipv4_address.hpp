/**
 *  \file   ipv4_address.hpp
 *  \brief  The file contains declarations for the class 'IPv4Address'.
 */

#ifndef __IPV4_ADDRESS_HPP__
#define __IPV4_ADDRESS_HPP__

/**
 *  \class  IPv4Address
 *  \brief  The class represents a four byte IPv4 address.
 *
 *  The class abstracts the IPv4 address. This allows it to be defined and
 *  used in different formats. This results in a great simplification from
 *  the user's perspective. Nevertheless, the class must be expanded to
 *  handle incorrect entries in order to rule out incorrect behavior.
 */
class IPv4Address
{
public:
    /**
     *  \fn         IPv4Address(const char* adressAsString)
     *  \brief      The constructor initializes an element of type
     * 'IPv4Address'. \param[in]  addressAsString passes the address in a C
     * string.
     *
     *  This is the preferred constructor. Even if the class is extended by
     *  additional constructors, it is still the easiest way to enter the
     * address. Please note: The format of the address is as follows:
     * "XYZ.XYZ.XYZ.XYZ"
     */
    IPv4Address(const char* addressASString);

    /**
     *  \fn       toArray(void)
     *  \brief    Returns the IPv4 address in four bytes.
     *  \return   Array of uinsigned chars representing the address.
     *
     *  The method returns a pointer to its own member '_bytes'. This avoids
     * storage replication. Even though this getter method is an anti-pattern,
     * it is still the currently best method for accessing the bytes of the
     * address.
     */
    const unsigned char* toArray(void) const;

private:
    /**
     *  \fn         validateAddressString(const char* addressAsString) const
     *  \brief      Validates the string as an IPv4 address.
     *  \param[in]  addressAsString passes the address in a C string.
     *  \return     Boolean validating the passed string.
     *
     *  This method needs to be expanded to include further validation steps.
     *  Currently only the number of periods is counted. It would also be
     * obvious to validate the characters contained, the entire length and the
     * respective byte length.
     */
    bool validateAddressString(const char* addressAsString) const;

    /**
     *  \fn         parseAddressString(const char* addressString)
     *  \brief      Parses the address and writes it into _bytes.
     *  \param[in]  addressAsString passes the address in a C string (char[]).
     *
     *  The method currently cannot handle incorrect input. Even if the
     *  'validateAddressString' method takes care of the pre-validation, it is
     * still necessary to strengthen the resilience of the method against
     * incorrect entries. In addition, the use of hexadecimal numbers is
     * currently not possible. This also needs to be expanded.
     */
    void parseAddressString(const char* addressString);

    /**
     *  \var    _bytes
     *  \brief  The array contains the bytes of the IP address.
     *
     *  It represents the main storage of the IPv4 address. The methods based on
     * it are merely tools for assignment, modification and use.
     */
    unsigned char _bytes[4] = {};
};

/**
 *  \typedef    SubnetMask
 *  \brief      The SubnetMask type uses functionalities of the IPv4Address.
 *
 *  Even if the format of the subnet mask and the IPv4 address are the same,
 * they are different objects and must be treated as such. This is achieved by
 * using a typedef.
 */
typedef IPv4Address SubnetMask;

#endif //__IPV4_ADDRESS_HPP__