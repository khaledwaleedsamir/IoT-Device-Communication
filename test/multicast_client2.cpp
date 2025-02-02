#include <iostream>
#include "../src/sockets/UDP_socket.hpp"

int main() {
    try {
        // Create a socket for sending multicast messages
        Socket* client_socket = new UDPSocket(UDP_Transmission_Type::MULTICAST);
        
        // Connect to the multicast group (Multicast address 224.0.0.1 and port 8080)
        client_socket->connect("224.0.0.1", 8080);
        
        // Send a message to the multicast group
        while(1){
        std::string message = "Hello, Multicast Group!, client 2";
        client_socket->send(message);
        std::cout << "Sent: " << message << std::endl;
        sleep(2);
        }
        
    } catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
