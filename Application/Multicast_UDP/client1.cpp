#include <iostream>
#include "../../src/channel/client_channel.hpp"

int main(){
    Socket* client_sock = new UDPSocket(UDP_Transmission_Type::MULTICAST);
    Channel* client = new ClientChannel(client_sock,"224.0.0.1", 8080);
    client->start();
    std::cout<<"Client 1 Started..."<<std::endl;
    std::string msg;
    while(msg != "END"){
        msg = client->receive();
        std::cout<<"Server Sent: "<<msg<<std::endl;
    }
    delete client;
    client = nullptr;
    delete client_sock;
    client_sock = nullptr;
    std::cout<<"Client 1 closed!"<<std::endl;
    return 0;
}