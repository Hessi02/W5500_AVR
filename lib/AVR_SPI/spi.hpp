/**
 *	\file		spi.hpp
 *  \brief      The file contains function delcarations for AVR's SPI communication. 
 */

#ifndef __SPI_HPP__
#define __SPI_HPP__

/**
 *  \namespace  SPI
 *  \brief      The namepsace contains functions used for SPI communication.
 */
namespace SPI
{
    /**
     *  \fn         init(const unsigned char& mode = 0)
     *  \brief      The function initializes the communication.
     *  \param[in]  mode passes the SPI mode for operation.
     */
    void init(const unsigned char& mode = 0);

    /**
     *  \fn         sendByte(const unsigned char& byte)
     *  \brief      The function sends a byte to the selected SPI slave.
     *  \param[in]  byte passes the data byte to send.
     */
    void sendByte(const unsigned char& byte);

    /**
     *  \fn         recvByte(void)
     *  \brief      The function receives a byte from a SPI slave.
     *  \return     Returns the received byte.
     */
    unsigned char recvByte(void);

    /**
     *  \fn     selectSlave(void)
     *  \brief  The function selects the SPI slave.
     */
    void selectSlave(void);

    /**
     *  \fn     deselectSlave(void)
     *  \brief  The function deselects the SPI slave.
     */
    void deselectSlave(void);
}

#endif //__SPI_HPP__
