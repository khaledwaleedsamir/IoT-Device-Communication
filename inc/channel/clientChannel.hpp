/**
 * @file clientChannel.hpp
 * @brief 
 * 
 * @author Khaled Waleed
 * @version 1.0
 */
#ifndef CLIENT_CHANNEL_HPP_
#define CLIENT_CHANNEL_HPP_

#include "channel.hpp"

class clientChannel: public Channel{
    private:
    std::string serverIP;
    unsigned short serverPort;
    public:
    clientChannel(std::string connection);
    virtual void start() override;
    virtual void stop() override;
    virtual void send(const std::string& message) override;
    virtual std::string receive() override;
    void setServerInfo(std::string IP, unsigned short port);
    ~clientChannel();
};

#endif /*CLIENT_CHANNEL_HPP_*/