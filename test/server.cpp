#include <iostream>
#include "../src/channel/server_channel.hpp"

int main(){
    Socket* server_socket = new TCPSocket();
    Channel* server = new ServerChannel(server_socket, "0.0.0.0", 12345);
    server->start();
    std::string msg;
    while(true){
        msg = server->receive();
        std::cout<<"Client Sent: "+ msg<<std::endl;
        server->send("ACK msg");
        if(msg == "stop"){
            server->send("Ack Stop");
            break;
        }
    }
    server->stop();
    delete server;
    server = nullptr;
    delete server_socket;
    server_socket = nullptr;
    std::cout<<"Connection terminated succssefully!"<<std::endl;
    return 0;
}