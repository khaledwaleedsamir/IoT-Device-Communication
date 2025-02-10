#ifndef SERVER_CHANNEL_H_
#define SERVER_CHANNEL_H_
/* Includes */
#include "channel.hpp"

/* Derived ServerChannel Class */
class ServerChannel : public Channel {
    private:
    unsigned short int port;
    std::string ip;
    Socket* ClientSocket;
    std::string destination_ip;
    public:
    /* Constructor*/
    ServerChannel(Socket* socket, std::string bind_ip, unsigned short int port);
    ServerChannel(Socket* socket, std::string bind_ip, unsigned short int port, std::string destination_ip);
    /* Functions */
    void start() override;
    void stop() override;
    void send(const std::string& message) override;
    std::string receive() override;
    /* Destructor */
    ~ServerChannel();
};




#endif /*SERVER_CHANNEL_H_*/