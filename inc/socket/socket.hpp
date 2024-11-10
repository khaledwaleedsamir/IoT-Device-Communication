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
    virtual void send(const std::string& message) = 0;
    virtual std::string receive() = 0;
    virtual void shutdown() = 0;
    virtual void connect(const std::string& ipAddress, const unsigned short int& port) = 0;
    virtual void bind(unsigned short int port) = 0;  // Pure virtual bind function
    virtual ~Socket() = default;
};

#endif /*SOCKET_HPP*/