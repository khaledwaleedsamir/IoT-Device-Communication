/**
 * @file clientChannel.cpp
 * @brief 
 * 
 * @author Khaled Waleed
 * @version 1.0
 */
#include "clientChannel.hpp"
clientChannel::clientChannel(std::string connection):serverIP(" "),serverPort(0){
    if(connection == "TCP"){
        this->channelSocket = new TCPSocket;
    }
    else if(connection == "UDP"){
        this->channelSocket = new UDPSocket;
    }
    else {
        throw std::invalid_argument("Invalid connection type. Use 'TCP' or 'UDP'.");
    }
}
void clientChannel::setServerInfo(std::string IP, unsigned short port){
    this->serverIP = IP;
    this->serverPort = port;
}
void clientChannel::start(){
    // Connect to the server using the specific socket type (TCP or UDP)
    if (dynamic_cast<TCPSocket*>(channelSocket)) {
        dynamic_cast<TCPSocket*>(channelSocket)->connect(serverIP, serverPort);
        std::cout << "Connected to server at " << serverIP << ":" << serverPort << std::endl;
    } 
    else if (dynamic_cast<UDPSocket*>(channelSocket)) {
        // UDP does not need a connect
    }
}

void clientChannel::send(const std::string& message){
    if (dynamic_cast<UDPSocket*>(channelSocket)) {
        dynamic_cast<UDPSocket*>(channelSocket)->send(message, serverIP, serverPort);  // UDP requires IP and port
    } else {
        dynamic_cast<TCPSocket*>(channelSocket)->send(message);  // TCP does not need IP and port for send
    }
}

std::string clientChannel::receive(){
    if (dynamic_cast<UDPSocket*>(channelSocket)) {
        return dynamic_cast<UDPSocket*>(channelSocket)->receive(serverIP, serverPort);
    } 
    else {
        return dynamic_cast<TCPSocket*>(channelSocket)->receive();  // TCP receive without IP and port
    }
}

void clientChannel::stop(){
    channelSocket->shutdown();
    std::cout << "Disconnected from server." << std::endl;
}