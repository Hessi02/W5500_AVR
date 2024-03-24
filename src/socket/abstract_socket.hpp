/**
 *  \file   abstract_socket.hpp
 *  \brief  The file contains declaration for the AbstractSocket class.
 */

#ifndef __ABSTRACT_SOCKET_HPP__
#define __ABSTRACT_SOCKET_HPP__

class W5500;

#include <stdint.h>

/**
 *  \class  AbstractSocket
 *  \brief  The class represents a base class for all socket types.
 */
class AbstractSocket
{
public:
    /**
     *  \fn             AbstractSocket(void)
     *  \brief          The constructor initializes an instance of type 'AbstractSocket'
     */
    AbstractSocket(void);

    /**
     *  \fn     ~AbstractSocket(void)
     *  \brief  The destructor gets called when the instance gets deleted.
     */
    ~AbstractSocket(void);

    /**
     *  \fn             
     *  \brief 
     *  \param[inout]   chipInterface passes a pointer to the W5500 interface instance.
     *  \param[in]      port passes the 16 bit source port value.
     */
    virtual void bind(W5500* chipInterface, const uint16_t& port) = 0;

    /**
     *  \fn     open(void)
     *  \brief  Opens and initializes the socket.
     */
    void open(void);

    /**
     *  \fn       getIndex(void) const
     *  \brief    Returns the socket's index used by the W5500.
     *  \return   Index of the socket as a uint8_t.
     */
    uint8_t getIndex(void) const;

    /**
     *  \fn         setLocalPort(void)
     *  \brief      Configures the source port number of the socket.
     *  \param[in]  port passes the local port to configure.
     */
    void setLocalPort(const uint16_t& port);

    /**
     *  \fn       isOpen(void)
     *  \brief    Checks whether the socket is open or not.
     *  \return   Boolean indication the socket opening status.
     *  \todo     Make pure virtual methods possible...
     */
    virtual bool isOpen(void) { return false; }

    /**
     *  \fn         send(const char* data)
     *  \brief      Sends the passes string to it's destination.
     *  \param[in]  data passes the C string to send.
     */
    void send(const char* data);

public: /* SIGNALS */
    /**
     *  \fn     eventOccured(void)
     *  \brief  This signal is issued when socket is connected.
     *  \note   The signal needs callbacks to work properly.
     */
    void eventOccured(void);

    /**
     *  \fn     connected(void)
     *  \brief  This signal is issued when socket is connected.
     *  \note   The signal needs callbacks to work properly. 
     */
    void connected(void);

    /**
     *  \fn     disconnected(void)
     *  \brief  This signal is issued when socket is disconnected.
     *  \note   The signal needs callbacks to work properly.
     */
    void disconnected(void);

    /**
     *  \fn     receivedMessage(void)
     *  \brief  This signal is issued when socket received a message.
     *  \note   The signal needs callbacks to work properly. 
     */
    void receivedMessage(void);

    /**
     *  \fn     timedOut(void)
     *  \brief  This signal is issued when socket timed out.
     *  \note   The signal needs callbacks to work properly. 
     */
    void timedOut(void);

    /**
     *  \fn     messageSent(void) 
     *  \brief  This signal is issued when message is sent.
     *  \note   The signal needs callbacks to work properly. 
     */
    void messageSent(void);

    unsigned char getINTStatus(void);

protected:
    /**
     *  \fn         enableInterrupts(const unsigned char& interruptMask = 0x1f) 
     *  \brief      Enables the specified socket interrupts.
     *  \param[in]  interruptMask passes the interrupt mask to enable. 
     */
    void enableInterrupts(const unsigned char& interruptMask = 0x1f);

    /**
     *  \fn         writeControlRegister()
     *  \brief      Writes the passed data to the specified register address.
     *  \param[in]  addressWord passes the register address to write to.
     *  \param[in]  dataByteArray passes the data to send as an byte array.
     *  \param[in]  dataByteCount passes the length of the byte array.
     */
    void writeControlRegister(const uint16_t& addressWord,
                              const unsigned char* dataByteArray,
                              const uint8_t& dataByteCount);

    /**
     * 	\fn			readControlRegister()
     * 	\brief 		Reads the data of the specified register address.
     *  \param[in]  addressWord passes the address to read from.
     * 	\param[out]	dataByteArray passes the array to write the receiveddata to. 
     *  \param[in]  dataByteCount passes the length of the byte array toread. 
     *  \return		Pointer to a C array containing the registers data.
     */
    void readControlRegister(const uint16_t& addressWord,
                             unsigned char* dataByteArray,
                             const uint8_t& dataByteCount);

    /**
     *  \var    _chipInterface
     *  \brief  A pointer to the W5500 instance controlling the IP
     * communication.
     */
    W5500* _chipInterface = nullptr;

private:
    /**
     *  \fn     sendBuffer(void)
     *  \brief  Sends transmits all the data in the socket's SnTX buffer.
     */
    void sendBuffer(void);

    /**
     *  \fn         writeToBuffer(const unsigned char* data, const uint16_t length) 
     *  \brief      Writes to the sockets SnTX buffer register.
     *  \param[in]  addressRegister passes the buffers register to start writing. 
     *  \param[in]  data passes the data array to copy into the buffer.
     *  \param[in]  length passes the length of the data array.
     */
    void writeBufferRegister(const uint16_t& addressRegister,
                             const unsigned char* data,
                             const uint8_t& length);

    /**
     *  \fn     readTXBufferPointer(void)
     *  \brief  Reads the pointer on the data in the SNTxBuffer.
     *  \return 16 bit pointer to the target position.
     */
    uint16_t getTXWritePointer(void);

    /**
     *  \fn         setTXWritePointer(const uint16_t& length)
     *  \brief      Specifies the pointer on the data in the SnTX buffer.
     *  \param[in]  position passes the pointer's target position.
     */
    void setTXWritePointer(const uint16_t& position);

    /**
     *  \fn         getTXReadPointer(const uint16_t& length)
     *  \brief      Specifies the pointer on the data in the SnTX read buffer.
     *  \param[in]  position passes the pointer's target position.
     */
    void setTXReadPointer(const uint16_t& position);

    /**
     *  \var    _index
     *  \brief  A 8 bit integer representing the socket's index on the W5500.
     */
    uint8_t _index;
};

#endif //__ABSTRACT_SOCKET_HPP__