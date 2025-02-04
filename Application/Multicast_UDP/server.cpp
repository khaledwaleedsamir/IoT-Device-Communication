#include <iostream>
#include "../../src/channel/server_channel.hpp"

int main(){
    Socket* server_sock = new UDPSocket(UDP_Transmission_Type::MULTICAST);
    Channel* server = new ServerChannel(server_sock, "224.0.0.1", 8080);
    server->start();
    int beats = 6;
    std::cout<<"Server started sending"<<std::endl;
    while (beats > 0){
        server->send("Tic");
        sleep(1);
        server->send("Toc");
        sleep(1);
        std::cout<<"Beat "<<6-beats<<std::endl;
        beats--;
    }
    server->send("END");
    delete server;
    server = nullptr;
    delete server_sock;
    server_sock = nullptr;
    std::cout<<"Server closed!"<<std::endl;
    return 0;
}