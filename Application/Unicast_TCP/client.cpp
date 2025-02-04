#include <iostream>
#include "../src/channel/client_channel.hpp"

int main(){
    Socket* sock = new TCPSocket();
    Channel* client = new ClientChannel(sock,"127.0.0.1",12345);
    std::string msg;
    client->start();
    while(true){
        std::cout<<"Enter Message to send to client: ";
        std::cin>>msg;
        client->send(msg);
        if (msg == "stop"){
            std::cout<<"Server Sent: "+client->receive()<<std::endl;
            break;
        }
        msg = client->receive();
        std::cout<<"Server Sent: " + msg<<std::endl;
    }
    client->stop();
    delete client;
    client = nullptr;
    delete sock;
    sock = nullptr;
    std::cout<<"Connection terminated succssefully!"<<std::endl;
    return 0;
}