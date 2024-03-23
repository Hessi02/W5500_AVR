/**
 *  \file   mac_address.hpp
 *  \brief  The file contains declaration for the 'MacAddress' class.
 */

#ifndef __MAC_ADDRESS_HPP__
#define __MAC_ADDRESS_HPP__

/**
 *  \class  MacAddress
 *  \brief  The class represents a six byte MAC address.
 *
 *  The class abstracts the MAC address. This allows it to be defined and
 *  used in different formats. This results in a great simplification from
 *  the user's perspective. Nevertheless, the class must be expanded to
 *  handle incorrect entries in order to rule out incorrect behavior.
 */
class MacAddress
{
public:
    /**
     *  \fn         MacAddress
     *  \brief      The constructor initializes an instance of type 'MacAddress'.
     *  \param[in]  addressAsString passes the address as a C string.
     *
     *  This is the preferred constructor. Even if the class is extended by
     *  additional constructors, it is still the easiest way to enter the
     *  address. Please note: The format of the address is as follows:
     *  "XX-XX-XX-XX-XX-XX"
     */
    MacAddress(const char* addressAsString);

    /**
     *  \fn       toArray(void)
     *  \brief    Returns the MAC address in six bytes.
     *  \return   Array of uinsigned chars representing the address.
     *
     *  The method returns a pointer to its own member '_bytes'. This avoids
     *  storage replication. Even though this getter method is an anti-pattern,
     *  it is still the currently best method for accessing the bytes of the
     *  address.
     */
    const unsigned char* toArray(void) const;

private:
    /**
     *  \fn         validateAddressString(const char* addressAsString) const
     *  \brief      Validates the string as an MAC address.
     *  \param[in]  addressAsString passes the address in a C string.
     *  \return     Boolean validating the passed string.
     *
     *  This method needs to be expanded to include further validation steps.
     *  Currently only the number of hyphens is counted. It would also be
     *  obvious to validate the characters contained, the entire length and the
     *  respective byte length.
     */
    bool validateAddressString(const char* addressAsString) const;

    /**
     *  \fn         parseToTwoDim(const char* addressString)
     *  \brief      Parses the address to a two dimensional array.
     *  \param[in]  addressAsString passes the address in a C string.
     *  \param[out] addressInTwoDim passes the two dimensional output array.
     *
     *  The method currently cannot handle incorrect input. Even if the
     *  'validateAddressString' method takes care of the pre-validation, it is
     *  still necessary to strengthen the resilience of the method against
     *  incorrect entries. The use of other address formats such as
     *  "XX.XX.XX.XX.XX.XX" should also be enabled. In addition, the use of
     *  decimal numbers is currently not possible. This also needs to be
     *  expanded.
     */
    void parseToTwoDim(const char* addressString, char addressInTwoDim[6][2]) const;

    /**
     *  \fn         convertCharToInt(char addressInTwoDim[6][2])
     *  \brief      Converts the two dimensional array into a hex byte array.
     *  \param[in]  addressInTwoDim passes the two dimensional input array.
     *  \note       The method writes the bytes directly in the member _bytes.
     *
     *  The method converts the six different character pairs into one byte
     *  each. Only hexadecimal format can be used. There is a need for
     *  optimization in this regard. In addition, the use of the two-dimensional
     *  C array should be reconsidered.
     */
    void convertCharToInt(const char addressInTwoDim[6][2]);

    /**
     *  \var    _bytes
     *  \brief  The array contains the bytes of the IP address.
     *
     *  It represents the main storage of the MAC address. The methods based on
     *  it are merely tools for assignment, modification and use.
     */
    unsigned char _bytes[6] = {};
};

#endif //__MAC_ADDRESS_HPP__