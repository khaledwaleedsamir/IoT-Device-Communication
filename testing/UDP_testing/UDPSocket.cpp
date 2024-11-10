/**
 * @file UDPSocket.cpp
 * @brief 
 * 
 * @author Khaled Waleed
 * @version 1.0
 */
#include "UDPSocket.hpp"

UDPSocket::UDPSocket() : socket_fd(-1) {
    // Create a UDP socket
    if ((socket_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        std::cerr << "Socket creation failed: " << strerror(errno) << std::endl;
        throw std::runtime_error("Socket creation failed");
    }
}
void UDPSocket::connect(const std::string& ipAddress, const unsigned short int& port){
    std::cout<<"UDP doesn't need a connection Channel."<<std::endl;
}
void UDPSocket::bind(unsigned short int port){
    // Specifying the address
    address.sin_family = AF_INET;
    address.sin_port = htons(port);

    if (::bind(socket_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        std::cerr << "Binding Failed: " << strerror(errno) << std::endl;
        throw std::runtime_error("Binding failed");
    }
}

void UDPSocket::send(const std::string& message) {
    throw std::runtime_error("UDP send needs IP address and port.");
}
void UDPSocket::send(const std::string& message, const std::string& destIpAddress, unsigned short destPort){
    sockaddr_in destAddress;
        destAddress.sin_family = AF_INET;
        destAddress.sin_port = htons(destPort);

        if (inet_pton(AF_INET, destIpAddress.c_str(), &destAddress.sin_addr) <= 0) {
            throw std::runtime_error("Invalid destination IP address");
        }

        // Send the message to the specified address and port
        if (::sendto(socket_fd, message.c_str(), message.size(), 0,
                     (struct sockaddr*)&destAddress, sizeof(destAddress)) < 0) {
            throw std::runtime_error("Send failed");
        }
}
std::string UDPSocket::receive() {
    throw std::runtime_error("UDP send needs IP address and port.");
}
std::string UDPSocket::receive(std::string &srcIpAddress, unsigned short &srcPort){
    char buffer[1024];  // Buffer for incoming data
    sockaddr_in srcAddress;
    socklen_t addrlen = sizeof(srcAddress);

    // Receive data from the socket
    ssize_t bytesReceived = recvfrom(socket_fd, buffer, sizeof(buffer), 0,
                                      (struct sockaddr*)&srcAddress, &addrlen);
    if (bytesReceived == -1) {
        throw std::runtime_error("Receive failed");
    }
    
    // Null-terminate the received data
    buffer[bytesReceived] = '\0';
    
    // Extract the source IP address and port from the received address
    srcIpAddress = inet_ntoa(srcAddress.sin_addr);  // Convert IP address to string
    srcPort = ntohs(srcAddress.sin_port);           // Convert port to host byte order

    return std::string(buffer);  // Return the received message as a string
}
void UDPSocket::shutdown() {
    if (socket_fd != -1) {
        close(socket_fd);
        socket_fd = -1;
    }
}

UDPSocket::~UDPSocket() {
    if (socket_fd != -1) {
        close(socket_fd);  // Ensure proper cleanup of the socket
    }
}