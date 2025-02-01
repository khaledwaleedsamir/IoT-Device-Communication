#include "TCP_socket.hpp"

TCPSocket::TCPSocket(){
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(socket_fd < 0){
        std::cerr<<"Failed to create socket !"<<std::endl;
    }
}

TCPSocket::TCPSocket(int socket_fd, struct sockaddr_in socket_address){
    this->socket_fd = socket_fd;
    this->socket_address = socket_address;
}

void TCPSocket::connect(const std::string &ip, unsigned short int port){
    // filling the socket_address struct
    this->socket_address.sin_family = AF_INET; // AF_INET for IPv4
    this->socket_address.sin_port = htons(port);
    if(inet_pton(AF_INET, ip.c_str(), &socket_address.sin_addr) <= 0){
        std::cerr<<"Wrong IP address"<<std::endl;
    }
    // Attempting to connect
    if(::connect(socket_fd,(struct sockaddr*)&socket_address, sizeof(socket_address)) < 0){
        throw std::runtime_error("Connection Failed!");
    }
}

void TCPSocket::bind(const std::string &ip, unsigned short int port){
    this->socket_address.sin_family = AF_INET;
    this->socket_address.sin_addr.s_addr = INADDR_ANY;
    this->socket_address.sin_port = htons(port);
    if(::bind(socket_fd,(struct sockaddr*)&socket_address, sizeof(socket_address)) < 0){
        std::cerr<<"Failed to bind!"<<std::endl;
    }

}
void TCPSocket::listen(int backlog){
    if (socket_fd < 0) {
        throw std::runtime_error("Socket is not initialized for listening");
    }

    if (::listen(socket_fd, backlog) < 0) {
        throw std::runtime_error("Listen failed: " + std::string(strerror(errno)));
    }
}
TCPSocket* TCPSocket::accept(){
    struct sockaddr_in client_address;
    int addrlen = sizeof(client_address);
    int client_socket = ::accept(socket_fd,(struct sockaddr*)&client_address, (socklen_t*)&addrlen);
    if(client_socket<0){
        throw std::runtime_error("Failed to accept connection: " + std::string(strerror(errno)));
    }
    return new TCPSocket(client_socket,client_address);
}

void TCPSocket::send(const std::string& message){
    if (socket_fd < 0) {
        throw std::runtime_error("Socket is not initialized for sending");
    }
    ssize_t bytesSent = ::send(socket_fd, message.c_str(), message.size(), 0);
    if (bytesSent < 0) {
        throw std::runtime_error("Send failed: " + std::string(strerror(errno)));
    }
}

std::string TCPSocket::receive(){
    std::vector<char> buffer(1024);
    int bytes = ::recv(socket_fd, buffer.data(), buffer.size(), 0);
    if(bytes < 0){
        throw std::runtime_error("Receive Failed!");
    }
    else if(bytes == 0 ){
        std::cout<<"Connection closed"<<std::endl;
        return ""; //returns empty string if the connection is closed.
    }
    return std::string(buffer.begin(),buffer.begin()+bytes);
}

void TCPSocket::shutdown(){
    if(socket_fd >= 0){
        // SHUT RDWR to stop both read and write operations
        ::shutdown(socket_fd, SHUT_RDWR);
        // Close the socket
        close(socket_fd);
        socket_fd = -1;
    }
}

const struct sockaddr_in* TCPSocket::getAddress() const {
    return &socket_address;
}

TCPSocket::~TCPSocket(){
    if(socket_fd >= 0){
        shutdown();
    }
    std::cout<<"TCPSocket Destructor called and socket is shutdown."<<std::endl;
} 