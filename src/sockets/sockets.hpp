#ifndef SOCKETS_H_
#define SOCKETS_H_

/* Includes */
#include <netinet/in.h>
#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <iostream>
#include <unistd.h>
#include <cstring>
#include <vector>
#include <exception>

/**
 * @class Socket
 * @brief Abstract class defining a generic socket interface.
 * 
 * This class provides a standard interface for both TCP and UDP sockets.
 */
class Socket{
    public:
    /**
     * @brief Establishes a connection to a remote host and has different behaviour depending on the type of socket.
     * 
     * @param ip The IP address of the remote host.
     * @param port The port number on the remote host.
     * @throws std::runtime_error if the connection fails.
     */
    virtual void connect(const std::string &ip, unsigned short int port) = 0;

    /**
     * @brief Sends data to the connected peer. (or to a specified ip and port for UDP socket using the connect method)
     * 
     * @param message The message to be sent.
     * @throws std::runtime_error if sending fails.
     */
    virtual void send(const std::string& message) = 0;

     /**
     * @brief Receives data from the connected peer. (or from a specified ip and port for UDP socket using the connect method)
     * 
     * @return The received message as a std::string.
     * @throws std::runtime_error if receiving fails.
     */
    virtual std::string receive() = 0;

    /**
     * @brief Gracefully shuts down the socket connection.
     */
    virtual void shutdown() = 0;

    /**
     * @brief Retrieves the socket address structure.
     * 
     * @return Pointer to `sockaddr_in` structure representing the socket's address.
     */
    virtual const struct sockaddr_in* getAddress() const = 0;

    /**
     * @brief Binds the socket to a specific IP and port.
     * 
     * @param ip The IP address to bind to.
     * @param port The port number to bind to.
     * @throws std::runtime_error if binding fails.
     */
    virtual void bind(const std::string &ip, unsigned short int port) = 0;

    /**
     * @brief Virtual destructor for proper cleanup in derived classes.
     */
    virtual ~Socket() = default;
};

#endif /*SOCKETS_H_*/