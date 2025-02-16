#include <iostream>
#include "../../src/channel/server_channel.hpp"

int main(){
    std::string multicast_ip;
    unsigned short int multicast_port;
    std::cout<<"Enter multicast address: ";
    std::cin>>multicast_ip;
    std::cout<<"Enter multicast port: ";
    std::cin>>multicast_port;
    Socket* server_sock = new UDPSocket(UDP_Transmission_Type::MULTICAST);
    Channel* server = new ServerChannel(server_sock, "0.0.0.0", multicast_port, multicast_ip);
    server->start();
    int sensor_data = 0;
    std::string msg;
    int iterations = 10;
    while (true){
        // simulating temp sensor data until driver is written
        sensor_data = rand() % 101;
        msg = "Current Temp. is " + std::to_string(sensor_data);
        server->send(msg);
        std::cout<<"message sent: "<<msg<<std::endl;
        iterations--;
        if(iterations == 0){
            std::cout<<"If you want to stop send 'stop'"<<std::endl;
            std::cout<<"message to send: ";
            std::cin>>msg;
            if(msg == "stop"){
                server->send(msg);
                break;
            }
            iterations = 10;
        }
        sleep(2);
    }
    delete server;
    server = nullptr;
    delete server_sock;
    server_sock = nullptr;
    std::cout<<"UDP multicast is closed!"<<std::endl;
    return 0;
}