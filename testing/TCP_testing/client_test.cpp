#include <iostream>
#include <string>
#include "TCPSocket.hpp"

int main() {
    try {
        // Create client socket
        TCPSocket clientSocket;

        // Connect to the server (change to the actual IP of the server)
        clientSocket.connect("127.0.0.1", 8080);
        std::string message;
        while (true){
            // Send message to the server
            std::cout<<"Enter msg to send: "<<std::endl;
            std::cin>>message;
            clientSocket.send(message);
            std::cout << "Sent to server: " << message << std::endl;
            
            if (message == "end"){
            // Close the connection
            clientSocket.shutdown();
            }

            // Receive response from the server
            std::string response = clientSocket.receive();
            std::cout << "Received from server: " << response << std::endl;

        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
