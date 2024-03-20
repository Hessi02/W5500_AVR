/**
 *  \file   mac_address.hpp
 *  \brief  The file contains declaration for the 'MACAddress' class.
*/

#ifndef __MAC_ADDRESS_HPP__
#define __MAC_ADDRESS_HPP__

/**
 *  \class  MACAddress 
 *  \brief  The class represents a six byte MAC address.
 */
class MACAddress
{
public:
    /**
     *  \fn         MACAddress
     *  \brief      The constructor initializes an instance of type 'MACAddress'.
     *  \param[in]  addressAsString passes the address as a C string (char[]).
     */
    MACAddress(const char* addressAsString);
    
    /**
     *  \fn         validateAddressString(const char* addressAsString) const
     *  \brief      Validates the string as an MAC address.
     *  \param[in]  addressAsString passes the address in a C string (char[]).
     *  \return     Boolean validating the passed string. 
     */  
    bool validateAddressString(const char* addressAsString) const;

    /**
     *  \fn         parseToTwoDim(const char* addressString)
     *  \brief      Parses the address to a two dimensional array.
     *  \param[in]  addressAsString passes the address in a C string.
     *  \param[out] addressInTwoDim passes the two dimensional output array.
     */
    void parseToTwoDim(const char* addressString, char addressInTwoDim[6][2]) const;

    /** 
     *  \fn         convertCharToInt(char addressInTwoDim[6][2])     
     *  \brief      Converts the two dimensional array into a hex byte array.
     *  \param[in]  addressInTwoDim passes the two dimensional input array.
     *  \note       The method writes the bytes directly in the member _bytes.
     */
    void convertCharToInt(char addressInTwoDim[6][2]);

    /**
     *  \fn       toArray(void)
     *  \brief    Returns the MAC address in six bytes.
     *  \return   Array of uinsigned chars representing the address.
     */
    const unsigned char* toArray(void) const; 

private:
    /**
     *  \var    _bytes
     *  \brief  The array contains the bytes of the IP address.
     */
    unsigned char _bytes[6] = {};
};


#endif //__MAC_ADDRESS_HPP__