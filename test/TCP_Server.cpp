#include <iostream>
#include "../src/sockets/TCP_socket.hpp"

int main() {
    try {
        // Use Socket pointer to handle the actual implementation of TCPSocket
        Socket* serverSocket = new TCPSocket();

        // Cast the Socket pointer to a TCPSocket pointer to access TCP-specific methods
        TCPSocket* tcpServerSocket = dynamic_cast<TCPSocket*>(serverSocket);
        if (tcpServerSocket == nullptr) {
            throw std::runtime_error("Failed to cast to TCPSocket!");
        }

        // Bind the server to a port (e.g., 12345)
        tcpServerSocket->bind("0.0.0.0", 12345);

        // Set up the server to listen for incoming connections
        tcpServerSocket->listen();

        std::cout << "Server is listening on port 12345..." << std::endl;

        // Accept a client connection
        Socket* clientSocket = tcpServerSocket->accept();  // Since the accept function is in TCPSocket
        std::cout << "Client connected!" << std::endl;

        // Cast the client socket back to TCPSocket* to use TCP-specific functions
        TCPSocket* tcpClientSocket = dynamic_cast<TCPSocket*>(clientSocket);
        if (tcpClientSocket == nullptr) {
            throw std::runtime_error("Failed to cast to TCPSocket!");
        }

        // Receive a message from the client
        std::string receivedMessage = tcpClientSocket->receive();
        std::cout << "Received from client: " << receivedMessage << std::endl;

        // Send a response back to the client
        tcpClientSocket->send("Hello from the server!");

        // Clean up and close the client socket
        delete tcpClientSocket;
        std::cout << "Client connection closed." << std::endl;

        // Clean up and close the server socket
        delete tcpServerSocket;

    } catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}
