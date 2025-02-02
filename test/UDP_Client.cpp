#include <iostream>
#include "../src/sockets/UDP_socket.hpp"

int main() {
    try {
        // Create a socket for sending data (Unicast)
        Socket* client_socket = new UDPSocket(UDP_Transmission_Type::UNICAST);
        
        // Connect to the server (e.g., server's IP is 127.0.0.1 and port is 8080)
        client_socket->connect("127.0.0.1", 8080);
        
        // Send a message to the server
        std::string message = "Hello, UDP Server!";
        client_socket->send(message);
        std::cout << "Sent: " << message << std::endl;
        
    } catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
