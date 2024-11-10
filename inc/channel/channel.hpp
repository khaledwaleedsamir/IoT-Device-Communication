/**
 * @file channel.hpp
 * @brief 
 * 
 * @author Khaled Waleed
 * @version 1.0
 */
#ifndef CHANNEL_HPP_
#define CHANNEL_HPP_

#include <string>
#include "socket.hpp"
#include "TCPSocket.hpp"
#include "UDPSocket.hpp"
class Channel{
public:
    Socket* channelSocket;
    virtual void start() = 0;
    virtual void stop() = 0;
    virtual void send(const std::string& message) = 0;
    virtual std::string receive() = 0;
    virtual ~Channel() = default;
};




#endif /*CHANNEL_HPP_*/