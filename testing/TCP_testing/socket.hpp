/**
 * @file socket.hpp
 * @brief Abstract base class for socket communication.
 *
 * This file contains the declaration of the Socket class, which defines the common
 * interface for socket communication.
 * 
 * @author Khaled Waleed
 * @version 1.0
 */
#ifndef SOCKET_HPP
#define SOCKET_HPP

#include <string>
class Socket {
public:
    /**
     * @brief Pure virtual function to connect the socket.
     */
    virtual void connect(const std::string& ipAddress, const unsigned short int& port) = 0;

    /**
     * @brief Pure virtual function to send a message through the socket.
     * 
     * @param message The message to send.
     */
    virtual void send(const std::string& message) = 0;

    /**
     * @brief Pure virtual function to receive a message from the socket.
     */
    virtual std::string receive() = 0;

    /**
     * @brief Pure virtual function to shut down the socket.
     */
    virtual void shutdown() = 0;

    /**
     * @brief Virtual destructor for the Socket class. 
     * Ensures proper cleanup of derived class objects.
     */
    virtual ~Socket() = default;
};

#endif /*SOCKET_HPP*/