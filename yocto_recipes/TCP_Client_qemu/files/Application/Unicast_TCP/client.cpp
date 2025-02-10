#include <iostream>
#include "../src/channel/client_channel.hpp"

int main(){
    Socket* sock = new TCPSocket();
    std::string ip;
    unsigned short int port;
    std::cout<<"Enter ip address to connect to: ";
    std::cin>>ip;
    std::cout<<"Enter port number: ";
    std::cin>>port;
    Channel* client = new ClientChannel(sock, ip, port);
    std::string msg;
    client->start();
    while(true){
        msg = client->receive();
        std::cout<<"Server Sent: " + msg<<std::endl;
        if (msg == "stop"){
            break;
        }
    }
    client->stop();
    delete client;
    client = nullptr;
    delete sock;
    sock = nullptr;
    std::cout<<"Connection terminated succssefully!"<<std::endl;
    return 0;
}