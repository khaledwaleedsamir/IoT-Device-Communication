#ifndef UDP_SOCKETS_H_
#define UDP_SOCKETS_H_

/* Includes */
#include "sockets.hpp"

/**
 * @enum UDP_Transmission_Type
 * 
 * @brief Defines the type of UDP transmission.
*/
enum class UDP_Transmission_Type{
    UNICAST,   // one-to-one
    MULTICAST, // one-to-many
};

/**
 * @class UDPSocket
 * 
 * @brief A derived class from Socket abstract class that implements UDP socket functionalities.
*/
class UDPSocket : public Socket{
    private:
    int socket_fd;
    struct sockaddr_in socket_address;
    struct sockaddr_in destination;
    struct ip_mreq mreq;
    UDP_Transmission_Type trans_type;

    public:
    /**
     * @brief Constructor to initialize a UDP socket.
     * @param trans_type Specifies whether the socket is unicast or multicast (default: UNICAST).
     * */
    UDPSocket(UDP_Transmission_Type trans_type = UDP_Transmission_Type::UNICAST);

    /**
     * @brief Connects the socket to a specified IP and port.
     * @param ip The destination IP address.
     * @param port The destination port number.
     * */
    void connect(const std::string &ip, unsigned short int port) override;

    /**
     * @brief Sends a message to the connected destination.
     * @param message The message to be sent.
     * */
    void send(const std::string& message) override;

    /**
     * @brief Receives a message from the socket.
     * @return The received message as a string.
     * */
    std::string receive() override;

    /**
     * @brief Closes the socket and performs necessary cleanup.
     * */
    void shutdown() override;

    /**
     * @brief Gets the address of the socket.
     * @return Pointer to the sockaddr_in structure containing the socket address.
     * */
    const struct sockaddr_in* getAddress() const override;

    /**
     * @brief Binds the socket to a specified IP and port.
     * @param ip The IP address to bind to.
     * @param port The port number to bind to.
     * */
    void bind(const std::string &ip, unsigned short int port) override;

    /**
     * @brief Joins a multicast group.
     * @param multicast_ip The multicast group IP address.
     * @param multicast_port The multicast port number.
     * */
    void joinMulticast(const std::string &multicast_ip, unsigned short int multicast_port);

    /**
     * @brief Leaves the currently joined multicast group.
     * */
    void leaveMulticast(void);

    /**
     * @brief Sets the Time-To-Live (TTL) value for multicast packets.
     * @param ttl The TTL value to be set.
     * */
    void setTTL(unsigned char ttl);

    /**
     * @brief Destructor to clean up resources and close the socket.
     * */
    ~UDPSocket();
};



#endif /*UDP_SOCKETS_H_*/