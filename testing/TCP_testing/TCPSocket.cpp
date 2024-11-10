#include "TCPSocket.hpp"
#include <iostream>
#include <stdexcept>
#include <cstring>
#include <cerrno>
#include <unistd.h>

TCPSocket::TCPSocket() : socket_fd(-1) {
    if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        std::cerr << "Socket creation failed: " << strerror(errno) << std::endl;
        throw std::runtime_error("Socket creation failed");
    }
}

void TCPSocket::bind_tcp(unsigned short int port) {
    // Specifying the address
    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    address.sin_addr.s_addr = INADDR_ANY;
    
    if (::bind(socket_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        std::cerr << "Binding Failed: " << strerror(errno) << std::endl;
        throw std::runtime_error("Binding failed");
    }
}

void TCPSocket::listen_tcp(int backlog) {
    if (::listen(socket_fd, backlog) < 0) {
        std::cerr << "Listen Failed: " << strerror(errno) << std::endl;
        throw std::runtime_error("Listen failed");
    }
}

TCPSocket TCPSocket::accept_tcp() {
    int addrlen = sizeof(address);
    int new_socket_fd = ::accept(socket_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen);
    if (new_socket_fd < 0) {
        std::cerr << "Accepting connection failed: " << strerror(errno) << std::endl;
        throw std::runtime_error("Accept failed");
    }

    TCPSocket newSocket;
    newSocket.socket_fd = new_socket_fd;
    return newSocket;
}

void TCPSocket::connect(const std::string& ipAddress, const unsigned short int& port) {
    address.sin_family = AF_INET;
    address.sin_port = htons(port);

    if (inet_pton(AF_INET, ipAddress.c_str(), &address.sin_addr) <= 0) {
        throw std::runtime_error("Invalid IP address!");
    }

    // Connect to the server
    if (::connect(socket_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        std::cout<<"connection error!"<<std::endl;
        throw std::runtime_error("connection failed!");
    }
}

void TCPSocket::send(const std::string& message) {
    if (::send(socket_fd, message.c_str(), message.size(), 0) < 0) {
        throw std::runtime_error("Send failed");
    }
}

std::string TCPSocket::receive() {
    char buffer[1024];  // Buffer to store incoming data
    ssize_t bytesReceived = recv(socket_fd, buffer, sizeof(buffer), 0);
    if (bytesReceived == -1) {
        throw std::runtime_error("Receive failed");
    }
        
    // Null-terminate the received data and return as a string
    buffer[bytesReceived] = '\0';
    return std::string(buffer);
}

void TCPSocket::shutdown() {
    if (socket_fd != -1) {
        close(socket_fd);
    }
}

TCPSocket::~TCPSocket() {
    if (socket_fd != -1) {
        close(socket_fd);  // Ensure proper cleanup of the socket
    }
}
