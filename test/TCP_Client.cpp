#include <iostream>
#include "../src/sockets/TCP_socket.hpp"

int main() {
    try {
        // Use Socket pointer to handle the actual implementation of TCPSocket
        Socket* clientSocket = new TCPSocket();

        // Connect to the server (localhost and port 12345)
        clientSocket->connect("127.0.0.1", 12345);
        std::cout << "Connected to server!" << std::endl;

        // Send a message to the server
        clientSocket->send("Hello from the client!");

        // Receive a response from the server
        std::string receivedMessage = clientSocket->receive();
        std::cout << "Received from server: " << receivedMessage << std::endl;

        // Clean up and close the client socket
        delete clientSocket;

    } catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}
