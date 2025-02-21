#ifndef CHANNEL_H_
#define CHANNEL_H_
/* Includes */
#include <iostream>
#include "../sockets/sockets.hpp"
#include "../sockets/TCP_socket.hpp"
#include "../sockets/UDP_socket.hpp"

/**
 * @class Channel
 * @brief Abstract base class for communication channels.
 *
 * The Channel class defines a common interface for communication channels.
 * It encapsulates a socket and provides pure virtual functions that must be
 * implemented by derived classes to handle sending and receiving data.
 */
class Channel{
    protected:
    Socket* channelSocket; ///< Pointer to the underlying socket used for communication.
    public:

    /**
     * @brief Constructs a Channel with a given socket.
     * @param socket Pointer to the socket used for communication.
     *
     * This constructor initializes the Channel with a socket object, allowing
     * derived classes to use the socket for sending and receiving data.
     */
    Channel(Socket *socket): channelSocket(socket){}

    /**
     * @brief Starts the communication channel.
     *
     * Initializes the channel to be ready for communication depending on the channel's 
     * socket(TCP or UDP) and the channel type (server or client)
     */
    virtual void start() = 0;

    /**
     * @brief Stops the communication channel.
     *
     * Stops the communication channel and cleans up resources depending on the channel's 
     * socket type (TCP or UDP) and whether the channel is a server or client.
     *
     * @note The caller is responsible for deleting both the Channel object and 
     * the associated Socket object after calling this function. 
     * 
     * Example cleanup:
     * @code
     * delete server;
     * server = nullptr;
     * delete server_sock;
     * server_sock = nullptr;
     * @endcode
     */
    virtual void stop() = 0;

    /**
     * @brief Sends a message through the channel.
     * @param message The message to be sent.
     *
     */
    virtual void send(const std::string& message) = 0;

    /**
     * @brief Receives a message from the channel.
     * @return The received message as a std::string.
     */
    
    virtual std::string receive() = 0;
    /* Destructor */
    virtual ~Channel() = default;
};



#endif /*CHANNEL_H_*/