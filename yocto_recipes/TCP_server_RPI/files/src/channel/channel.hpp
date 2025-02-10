#ifndef CHANNEL_H_
#define CHANNEL_H_
/* Includes */
#include <iostream>
#include "../sockets/sockets.hpp"
#include "../sockets/TCP_socket.hpp"
#include "../sockets/UDP_socket.hpp"

/* Channel Base Class */
class Channel{
    protected:
    Socket* channelSocket;
    public:
    /* Constructor */
    Channel(Socket *socket): channelSocket(socket){}
    /* Base Class Virtual Functions */
    virtual void start() = 0;
    virtual void stop() = 0;
    virtual void send(const std::string& message) = 0;
    virtual std::string receive() = 0;
    /* Destructor */
    virtual ~Channel() = default;
};



#endif /*CHANNEL_H_*/