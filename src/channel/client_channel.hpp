#ifndef CLIENT_CHANNEL_H_
#define CLIENT_CHANNEL_H_
#include "channel.hpp"

/* Derived ClientChannel Class */
class ClientChannel : public Channel {
    private:
    unsigned short int port;
    std::string ip;
    public:
    /* Constructor*/
    ClientChannel(Socket* socket, std::string ip, unsigned short int port);
    /* Functions */
    void start() override;
    void stop() override;
    void send(const std::string& message) override;
    std::string receive() override;
    /* Destructor */
    ~ClientChannel();
};


#endif /*CLIENT_CHANNEL_H_*/