#ifndef TCP_SOCKETS_H_
#define TCP_SOCKETS_H_

/* Includes */
#include "sockets.hpp"

/* TCP_socket derived class from abstract class sockets */
class TCPSocket: public Socket{
    private:
    int socket_fd;
    struct sockaddr_in socket_address;
    // Private constructor used within the class only
    explicit TCPSocket(int socket_fd, struct sockaddr_in socket_address);
    public:
    /* Constructor*/
    TCPSocket();
    /* base class functions override */
    void connect(const std::string &ip, unsigned short int port) override;
    void send(const std::string& message) override;
    std::string receive() override;
    void shutdown() override;
    const struct sockaddr_in* getAddress() const override;
    void bind(const std::string &ip, unsigned short int port) override;
    void listen(int backlog = 5);
    TCPSocket* accept();
    /* Destructor */
    ~TCPSocket();
};

#endif /*TCP_SOCKETS_H_*/