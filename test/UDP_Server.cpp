#include <iostream>
#include "../src/sockets/UDP_socket.hpp"

int main() {
    try {
        // Create a socket for receiving data (Unicast)
        Socket* server_socket = new UDPSocket(UDP_Transmission_Type::UNICAST);
        
        // Bind to address and port (e.g., port 8080)
        server_socket->bind("0.0.0.0", 8080);
        
        std::cout << "Server is listening on port 8080..." << std::endl;
        
        // Continuously receive messages
        while (true) {
            std::string received_message = server_socket->receive();
            std::cout << "Received: " << received_message << std::endl;
        }
    } catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
