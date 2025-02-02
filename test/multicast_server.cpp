#include <iostream>
#include "../src/sockets/UDP_socket.hpp"

int main() {
    // Create a socket for receiving multicast messages
    Socket* socket = new UDPSocket(UDP_Transmission_Type::MULTICAST);
    UDPSocket* server_socket = dynamic_cast<UDPSocket*>(socket);
    try {
        std::cout << "Server is listening for multicast messages..." << std::endl;
        
        // Join the multicast group (Optional)
        server_socket->joinMulticast("224.0.0.1", 8080);

        // Continuously receive messages
        while (true) {
            std::string received_message = server_socket->receive();
            std::cout << "Received: " << received_message << std::endl;
        }
    } catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        delete server_socket;
    }

    return 0;
}
