#include <iostream>
#include "../src/channel/server_channel.hpp"
#include <cstdlib>
int main(){
    Socket* server_socket = new TCPSocket();
    std::string ip;
    unsigned short int port;
    std::cout<<"Enter ip: ";
    std::cin>>ip;
    std::cout<<"Enter port: ";
    std::cin>>port;
    Channel* server = new ServerChannel(server_socket, ip, port);
    server->start();
    std::string msg;
    int sensor_data = 0;
    int iterations = 10;
    while(true){
        // simulating temp sensor data until driver is written
        sensor_data = rand() % 101;
        msg = "Current Temp. is " + std::to_string(sensor_data);
        server->send(msg);
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
        sleep(1);
    }
    server->stop();
    delete server;
    server = nullptr;
    delete server_socket;
    server_socket = nullptr;
    std::cout<<"Connection terminated succssefully!"<<std::endl;
    return 0;
}