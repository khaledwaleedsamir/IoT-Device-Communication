#ifndef UDP_SOCKETS_H_
#define UDP_SOCKETS_H_

/* Includes */
#include "sockets.hpp"

/*enum for communication type*/
enum class UDP_Transmission_Type{
    UNICAST,   // one-to-one
    MULTICAST, // one-to-many
};

/* UDP_socket derived class from abstract class sockets */
class UDPSocket : public Socket{
    private:
    int socket_fd;
    struct sockaddr_in socket_address;
    struct sockaddr_in destination;
    struct ip_mreq mreq;
    UDP_Transmission_Type trans_type;

    public:
    /* Constructor */
    UDPSocket(UDP_Transmission_Type trans_type = UDP_Transmission_Type::UNICAST);
    /* Functions */
    void connect(const std::string &ip, unsigned short int port) override;
    void send(const std::string& message) override;
    std::string receive() override;
    void shutdown() override;
    const struct sockaddr_in* getAddress() const override;
    void bind(const std::string &ip, unsigned short int port) override;
    void joinMulticast(const std::string &multicast_ip, unsigned short int multicast_port);
    void leaveMulticast(void);
    void setTTL(unsigned char ttl);

    /* Destructor */
    ~UDPSocket();
};



#endif /*UDP_SOCKETS_H_*/