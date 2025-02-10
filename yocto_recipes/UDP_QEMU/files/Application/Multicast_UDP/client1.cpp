#include <iostream>
#include "../../src/channel/client_channel.hpp"

int main(){
    std::string multicast_ip;
    unsigned short int multicast_port;
    int client_num;
    std::cout<<"Enter multicast ip (ex. 224.0.0.1): ";
    std::cin>>multicast_ip;
    std::cout<<"Enter multicast port (ex. 8080): ";
    std::cin>>multicast_port;
    std::cout<<"Enter Client number: ";
    std::cin>>client_num;
    Socket* client_sock = new UDPSocket(UDP_Transmission_Type::MULTICAST);
    Channel* client = new ClientChannel(client_sock, multicast_ip, multicast_port);
    std::cout<<"====================================================="<<std::endl;
    std::cout<<"Multicast ip: "+multicast_ip<<std::endl;
    std::cout<<"Multicast port: "+std::to_string(multicast_port)<<std::endl;
    std::cout<<"Client number: "+std::to_string(client_num)<<std::endl;
    std::cout<<"====================================================="<<std::endl;
    client->start();
    std::cout<<"Client " + std::to_string(client_num) + " Started..."<<std::endl;
    std::string msg;
    while(true){
        msg = client->receive();
        std::cout<<"Server Sent: "<<msg<<std::endl;
        if(msg == "stop"){
            break;
        }
    }
    delete client;
    client = nullptr;
    delete client_sock;
    client_sock = nullptr;
    std::cout<<"Client 1 closed!"<<std::endl;
    return 0;
}