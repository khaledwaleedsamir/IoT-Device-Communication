#include "UDP_socket.hpp"


UDPSocket::UDPSocket(UDP_Transmission_Type trans_type) : trans_type(trans_type){
    socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if(socket_fd<0){
        throw std::runtime_error("Failed to create socket: " + std::string(strerror(errno)));
    }
    if(trans_type == UDP_Transmission_Type::MULTICAST){
        int reuse = 1;
        if(setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, (char*)&reuse, sizeof(reuse)) < 0){
            shutdown();
            throw std::runtime_error("Failed to set SO_REUSEADDR: " + std::string(strerror(errno)) + ". Socket closed.");
        }
    }
}

void UDPSocket::connect(const std::string &ip, unsigned short int port){
    client_socket_address.sin_family = AF_INET;
    client_socket_address.sin_port = htons(port);
    if(inet_pton(AF_INET, ip.c_str(),&client_socket_address.sin_addr) <= 0){
        throw std::runtime_error("Error: Invalid ip address format.");
    }
    // check if socket is multi-cast call joinMultiCast()
    if(trans_type == UDP_Transmission_Type::MULTICAST){
        joinMulticast(ip,port);
    }
}

void UDPSocket::bind(const std::string &ip, unsigned short int port) {
    int addrlen = sizeof(socket_address);
    socket_address.sin_family = AF_INET;
    socket_address.sin_port = htons(port);

    // For unicast
    if (trans_type == UDP_Transmission_Type::UNICAST) {
        socket_address.sin_addr.s_addr = INADDR_ANY;  // Bind to all interfaces
    }
    // For multicast
    else if (trans_type == UDP_Transmission_Type::MULTICAST) {
        client_socket_address.sin_family = AF_INET;
        client_socket_address.sin_port = htons(port);
        client_socket_address.sin_addr.s_addr = inet_addr(ip.c_str());
        if (ip.empty()) {
            throw std::runtime_error("Error: no multicast IP provided.");
        }
        // Use inet_pton to ensure correct IP format handling
        if (inet_pton(AF_INET, ip.c_str(), &socket_address.sin_addr) <= 0) {
            throw std::runtime_error("Error: invalid multicast IP address.");
        }
    }

    // Attempt to bind the socket
    if (::bind(socket_fd, (struct sockaddr*)&socket_address, addrlen) < 0) {
        throw std::runtime_error("Bind failed: " + std::string(strerror(errno)));
    }
}
    
void UDPSocket::send(const std::string& message) {
    if (socket_fd >= 0) {
        ssize_t bytes_sent = ::sendto(socket_fd, message.c_str(), message.size(), 0, (const struct sockaddr*)&client_socket_address, sizeof(client_socket_address));
        if (bytes_sent < 0) {
            throw std::runtime_error("Error sending message: " + std::string(strerror(errno)));
        }
    }
}

std::string UDPSocket::receive(){
    std::vector<char> buffer(1024);
    socklen_t addrlen = sizeof(client_socket_address);
    int bytes = ::recvfrom(socket_fd, buffer.data(),buffer.size(),0,(struct sockaddr*)&client_socket_address,&addrlen);
    if (bytes < 0){
        throw std::runtime_error("Error receiving message: " + std::string(strerror(errno)));
    }
    return std::string(buffer.data(), bytes);
}
void UDPSocket::shutdown(){
    if(socket_fd >= 0){
        // Leave multicast if applicable
        if((trans_type == UDP_Transmission_Type::MULTICAST) && (mreq.imr_multiaddr.s_addr != 0)){
            try {
                leaveMulticast();
            } catch (const std::runtime_error& e) {
                std::cerr << "Error leaving multicast group: " << e.what() << std::endl;
            }
        }
        
        // Close the socket and reset socket_fd
        if (close(socket_fd) < 0) {
            std::cerr << "Error closing socket: " << std::string(strerror(errno)) << std::endl;
        }
        socket_fd = -1;  // Mark the socket as closed
    }
}

const struct sockaddr_in* UDPSocket::getAddress() const{
    return &socket_address;
}

void UDPSocket::joinMulticast(const std::string &multicast_ip, unsigned short int multicast_port){

    in_addr_t multicast_address = inet_addr(multicast_ip.c_str());
    if(!IN_MULTICAST(ntohl(multicast_address))){
        shutdown();
        throw std::runtime_error("ip not valid for multicast.");
    }

    socket_address.sin_family = AF_INET;
    socket_address.sin_addr.s_addr = htonl(INADDR_ANY);
    socket_address.sin_port = htons(multicast_port);

    if(::bind(socket_fd,(struct sockaddr*)&socket_address, sizeof(socket_address)) < 0){
        shutdown();
        throw std::runtime_error("binding failed " + std::string(strerror(errno)));
    }

    mreq = {}; // reset the multicast request struct
    mreq.imr_multiaddr.s_addr = multicast_address;
    mreq.imr_interface.s_addr = htonl(INADDR_ANY);
    if(setsockopt(socket_fd, IPPROTO_IP, IP_ADD_MEMBERSHIP,(struct ip_mreq*) &mreq, sizeof(mreq)) < 0){
        shutdown();
        throw std::runtime_error("Failed to join multicast group " + std::string(strerror(errno)));
    }
}

void UDPSocket::leaveMulticast(void){
    if (setsockopt(socket_fd, IPPROTO_IP, IP_DROP_MEMBERSHIP, &mreq, sizeof(mreq)) < 0) {
        throw std::runtime_error("Failed to leave multicast group " + std::string(strerror(errno)));
    }
}
void UDPSocket::setTTL(unsigned char ttl) {
    if (socket_fd < 0) {
        throw std::runtime_error("Cannot set TTL: Socket is not initialized.");
    }
    int ttl_int = static_cast<int>(ttl);  // Convert to int
    if (setsockopt(socket_fd, IPPROTO_IP, IP_MULTICAST_TTL, &ttl_int, sizeof(ttl_int)) < 0) {
        throw std::runtime_error("Failed to set multicast TTL: " + std::string(strerror(errno)));
    }
    std::cout << "Multicast TTL set to: " << static_cast<int>(ttl) << std::endl;
}
UDPSocket::~UDPSocket(){
    if(socket_fd >= 0){
        shutdown();
    }
    std::cout<<"UDPSocket Destructor called and socket is shutdown."<<std::endl;
}