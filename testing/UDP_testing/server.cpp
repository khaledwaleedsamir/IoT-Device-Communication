#include "UDPSocket.hpp"
#include <iostream>
#include <exception>

int main(){
    UDPSocket server;
    server.connect("192.168.1.1",8080); // this should print that UDP has no connection
    try{
        server.send("Testing"); // this should give error
    }
    catch(const std::exception& e){
        std::cerr << "Error: " << e.what() << std::endl;
    }
    server.bind(12345);
    std::cout << "Server is listening on port 12345..." << std::endl;
    std::string receivedMessage;
    std::string srcIpAddress;
    unsigned short srcPort;
    while (true) {
            receivedMessage = server.receive(srcIpAddress, srcPort);
            std::cout << "Received message: " << receivedMessage << " from " 
                      << srcIpAddress << ":" << srcPort << std::endl;
            server.send("ACK :D MSG RECEIVED", srcIpAddress, srcPort);
        }
    return 0;
}