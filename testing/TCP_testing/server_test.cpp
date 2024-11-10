#include <iostream>
#include <string>
#include "TCPSocket.hpp"

int main() {
    try {
        // Create server socket
        TCPSocket serverSocket;

        // Bind server to a port
        serverSocket.bind_tcp(8080);
        
        // Listen for incoming connections
        serverSocket.listen_tcp(5);

        std::cout << "Server listening on port 8080..." << std::endl;

        // Accept client connection
        TCPSocket clientSocket = serverSocket.accept_tcp();
        
        std::cout << "Client connected!" << std::endl;
        int msgCount = 0;
        while(true){
            // Receive message from the client
            std::string receivedMessage = clientSocket.receive();
            std::cout << "Received from client: " << receivedMessage << std::endl;

            // Send response to client
            std::string response = "Message "+ std::to_string(++msgCount) +" Received";
            clientSocket.send(response);
            std::cout << "Response sent to client: " << response << std::endl;
            if(receivedMessage == "end"){
            // Close the client connection
            clientSocket.shutdown();
            return 0;
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
