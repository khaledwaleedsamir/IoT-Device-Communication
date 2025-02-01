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

/* Sockets Abstract Class */
class Socket{
    public:
    virtual void connect(const std::string &ip, unsigned short int port) = 0;
    virtual void send(const std::string& message) = 0;
    virtual std::string receive() = 0;
    virtual void shutdown() = 0;
    virtual const struct sockaddr_in* getAddress() const = 0;
    virtual void bind(const std::string &ip, unsigned short int port) = 0;
    // Virtual destructor for proper clean up
    virtual ~Socket() = default;
};

#endif /*SOCKETS_H_*/