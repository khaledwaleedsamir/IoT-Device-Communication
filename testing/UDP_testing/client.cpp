#include "UDPSocket.hpp"
#include <iostream>

int main() {
    try {
        UDPSocket udpClient;

        // Specify server IP address and port to send the message
        std::string serverIp = "127.0.0.1";
        unsigned short serverPort = 12345;
        
        std::string message = "Hello from the UDP client!";
        
        // Send message to the server
        udpClient.send(message, serverIp, serverPort);
        std::cout << "Message sent to server: " << message << std::endl;
        message = udpClient.receive(serverIp, serverPort);
        std::cout<<"SERVER SENT: "<<message<<std::endl;
        
    } catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
