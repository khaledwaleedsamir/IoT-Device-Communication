#include "server_channel.hpp"

/* Constructor */
ServerChannel::ServerChannel(Socket* socket, std::string ip, unsigned short int port)
    : Channel(socket), ip(ip), port(port), ClientSocket(nullptr) {}

/* Start function */
void ServerChannel::start() {
    try {
        channelSocket->bind(ip, port);
        
        TCPSocket* tcpSocket = dynamic_cast<TCPSocket*>(channelSocket);
        if (tcpSocket != nullptr) {
            tcpSocket->listen();
            std::cout << "TCP Server listening on " << ip << " : " << port << std::endl;
            ClientSocket = tcpSocket->accept();
            std::cout << "Client connected!" << std::endl;
        } else {
            std::cout << "UDP Server started on " << ip << " : " << port << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error in ServerChannel::start(): " << e.what() << std::endl;
    }
}

/* Stop function */
void ServerChannel::stop() {
    try {
        TCPSocket* tcpSocket = dynamic_cast<TCPSocket*>(channelSocket);
        if (tcpSocket != nullptr && ClientSocket != nullptr) {
            try {
                ClientSocket->shutdown();
            } catch (const std::exception& e) {
                std::cerr << "Error shutting down client socket: " << e.what() << std::endl;
            }
            delete ClientSocket;
            ClientSocket = nullptr;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error in ServerChannel::stop(): " << e.what() << std::endl;
    }

    try {
        if (channelSocket != nullptr) {
            channelSocket->shutdown();
        }
    } catch (const std::exception& e) {
        std::cerr << "Error shutting down server socket: " << e.what() << std::endl;
    }
}

/* Send function */
void ServerChannel::send(const std::string& message) {
    if (ClientSocket != nullptr) {
        try {
            ClientSocket->send(message);
        } catch (const std::exception& e) {
            std::cerr << "Error sending message to client: " << e.what() << std::endl;
        }
    } else if (channelSocket != nullptr) {
        try {
            channelSocket->send(message);
        } catch (const std::exception& e) {
            std::cerr << "Error sending message: " << e.what() << std::endl;
        }
    } else {
        std::cerr << "Error: No valid socket to send message." << std::endl;
    }
}

/* Receive function */
std::string ServerChannel::receive() {
    if (ClientSocket != nullptr) {
        try {
            return ClientSocket->receive();
        } catch (const std::exception& e) {
            std::cerr << "Error receiving message from client: " << e.what() << std::endl;
            return "";
        }
    } else if (channelSocket != nullptr) {
        try {
            return channelSocket->receive();
        } catch (const std::exception& e) {
            std::cerr << "Error receiving message: " << e.what() << std::endl;
            return "";
        }
    } else {
        std::cerr << "Error: No valid socket to receive message." << std::endl;
        return "";
    }
}

/* Destructor */
ServerChannel::~ServerChannel() {
    stop();
    std::cout << "ServerChannel Destructor Called and channel is stopped." << std::endl;
}
