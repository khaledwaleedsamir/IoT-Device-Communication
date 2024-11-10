/**
 * @file UDPSocket.hpp
 * @brief 
 * 
 * @author [Khaled Waleed]
 * @version 1.0
 */
#ifndef UDPSOCKET_HPP_
#define UDPSOCKET_HPP_

#include "socket.hpp"
#include <stdexcept>  // For runtime_error
#include <iostream>   // For std::cout
#include <cstring>    // For memset()
#include <sys/socket.h>  // For socket, sendto, recvfrom
#include <arpa/inet.h>   // For inet_pton()
#include <unistd.h>      // For close()

class UDPSocket : public Socket {
private:
    int socket_fd;
    struct sockaddr_in address;
public:
    /* Constructor */
    UDPSocket();
    /* Functions */
    void bind(unsigned short int port) override;
    void send(const std::string& message) override;
    void send(const std::string& message, const std::string& destIpAddress, unsigned short destPort);
    std::string receive() override;
    std::string receive(std::string &srcIpAddress, unsigned short &srcPort);
    void shutdown() override;
    void connect(const std::string& ipAddress, const unsigned short int& port) override;
    /* Destructor */
    ~UDPSocket();
};
#endif /* UDPSOCKET_HPP_ */