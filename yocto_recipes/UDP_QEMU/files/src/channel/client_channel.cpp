#include "client_channel.hpp"
/* Constructor*/
ClientChannel::ClientChannel(Socket* socket, std::string ip, unsigned short int port) : Channel(socket),ip(ip), port(port){}
/* Functions */
void ClientChannel::start(){
    try{
        UDPSocket* udpSocket = dynamic_cast<UDPSocket*>(channelSocket);
        if(udpSocket != nullptr){
            channelSocket->bind("0.0.0.0", port);
        }
        channelSocket->connect(ip,port);
    }
    catch(const std::exception &e){
        std::cerr<<"Error in ClientChannel::start(): "<<e.what()<<std::endl;
    }
}
void ClientChannel::stop(){
    try{
        if(channelSocket != nullptr){
            channelSocket->shutdown();
        }
    }
    catch(const std::exception &e){
        std::cerr<<"Error shutting down socket in ClientChannel::stop(): "<<e.what()<<std::endl;   
    }
}
void ClientChannel::send(const std::string& message){
    try{
        channelSocket->send(message);
    }
    catch(const std::exception &e){
        std::cerr<<"Error in ClientChannel::send: "<<e.what()<<std::endl;
    }
}
std::string ClientChannel::receive(){
    try{
        return channelSocket->receive();
    }
    catch(const std::exception &e){
        std::cerr<<"Error in ClientChannel::receive: "<<e.what()<<std::endl;
        return "";
    }
}
/* Destructor */
ClientChannel::~ClientChannel(){
    stop();
    std::cout<<"ClientChannel Destructor Called and channel is stopped."<<std::endl;
}