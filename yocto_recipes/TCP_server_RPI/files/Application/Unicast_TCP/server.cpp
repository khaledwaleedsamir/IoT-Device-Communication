#include <iostream>
#include <cstdlib>
#include "../src/channel/server_channel.hpp"
#include "../../src/HW_modules/CLed.hpp"
#include "../../src/HW_modules/CRaspberryPi.hpp"
#include "../../src/HW_modules/CDht11.hpp"
#include <thread>
int main(){
    // Networking init
    std::cout<<"==================TCP Raspberry pi Server=================="<<std::endl;
    std::cout<<"=                         Welcome                         ="<<std::endl;
    std::cout<<"==========================================================="<<std::endl;
    Socket* server_socket = new TCPSocket();
    std::string ip = "0.0.0.0";
    unsigned short int port;
    std::cout<<"Enter port number: ";
    std::cin>>port;
    Channel* server = new ServerChannel(server_socket, ip, port);
    server->start();

    std::string msg;
    int iterations = 5;

    // Hardware init
    CRaspberryPi Raspi;
    CLed Led(Raspi, 22);
    std::cout<<"DHT11 on rpi pin 4!"<<std::endl;
    CDht11 Dht11(Raspi, 4);
    CDht11::CData sensor_data;

    while(true){
        // Getting the DHT11 Sensor Data
        try{
            sensor_data = Dht11.Measure();
        }
        catch(const std::exception& e){
            std::cerr<<"Error: "<<e.what()<<std::endl;
        }
        Led.On();
        msg.clear();
        msg.append("Current Temp: ")
           .append(std::to_string(static_cast<int>(sensor_data.Temperature)))
           .append("°C Current Humidity: ")
           .append(std::to_string(static_cast<int>(sensor_data.Humidity)))
           .append("%");
        std::cout<<"message sent: "<<msg<<std::endl;
        server->send(msg);
        iterations--;
        if(iterations == 0){
            std::cout<<"If you want to stop send 'stop'"<<std::endl;
            std::cout<<"message to send: ";
            std::cin>>msg;
            if(msg == "stop"){
                server->send(msg);
                Led.Off();
                break;
            }
            iterations = 5;
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
        Led.Off();
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
    server->stop();
    delete server;
    server = nullptr;
    delete server_socket;
    server_socket = nullptr;
    std::cout<<"Connection terminated succssefully!"<<std::endl;
    return 0;
}