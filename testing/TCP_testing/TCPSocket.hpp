/**
 * @file TCPSocket.hpp
 * @brief
 * 
 * @author Khaled Waleed
 * @version 1.0
 */
#ifndef TCPSOCKET_HPP
#define TCPSOCKET_HPP

#include "socket.hpp"
#include <stdexcept> 
#include <iostream>   
#include <cstring>    
#include <sys/socket.h>  
#include <arpa/inet.h>   
#include <unistd.h>     

class TCPSocket : public Socket {
private:
    int socket_fd;
    int new_socket_fd;                 
    struct sockaddr_in address;
    std::string ipAddress;
    std::string received_msg;
public:
    /* Constructor */
    TCPSocket();
    /* Functions */
    void bind_tcp(unsigned short int port);
    void listen_tcp(int backlog);
    TCPSocket accept_tcp();
    void connect(const std::string& ipAddress, const unsigned short int& port) override;
    void send(const std::string& message) override;
    std::string receive() override;
    void shutdown() override;
    /* Destructor */
    ~TCPSocket();
};

#endif /*TCPSOCKET_HPP*/