#ifndef TCP_SOCKETS_H_
#define TCP_SOCKETS_H_

/* Includes */
#include "sockets.hpp"

/**
 * @class TCPSocket
 * @brief Derived class for handling TCP socket communication.
 * 
 * This class provides an implementation for the `Socket` interface 
 * using the TCP protocol. It supports client and server functionalities, 
 * including binding, listening, accepting connections, sending, and receiving data.
 */
class TCPSocket: public Socket{
    private:
    int socket_fd;                     ///< File descriptor for the TCP socket.
    struct sockaddr_in socket_address; ///< Structure holding socket address information.

    /**
     * @brief Private constructor used internally for accepted connections.
     * 
     * This constructor is used when accepting a new client connection in `accept()`.
     * @param socket_fd File descriptor of the accepted connection.
     * @param socket_address The address information of the connected client.
     */
    explicit TCPSocket(int socket_fd, struct sockaddr_in socket_address);

    public:
    /**
     * @brief Default constructor for creating a TCP socket.
     * 
     * Initializes a new TCP socket and sets default options.
     * @throws std::runtime_error if socket creation fails.
     */
    TCPSocket();

    /**
     * @brief Connects to a remote server.
     * 
     * @param ip The IP address of the server.
     * @param port The port number to connect to.
     * @throws std::runtime_error if the connection fails.
     */
    void connect(const std::string &ip, unsigned short int port) override;

    /**
     * @brief Sends data over the TCP connection.
     * 
     * @param message The data to send.
     * @throws std::runtime_error if sending fails.
     */
    void send(const std::string& message) override;

    /**
     * @brief Receives data from the TCP connection.
     * 
     * @return A `std::string` containing the received data.
     * @throws std::runtime_error if receiving fails.
     */
    std::string receive() override;

    /**
     * @brief Closes the socket connection.
     * 
     * Properly shuts down the TCP socket to release resources.
     */
    void shutdown() override;

    /**
     * @brief Returns the socket's address information.
     * 
     * @return Pointer to `sockaddr_in` structure containing address details.
     */
    const struct sockaddr_in* getAddress() const override;

    /**
     * @brief Binds the socket to a specific IP and port.
     * 
     * Typically used in server applications before calling `listen()`.
     * @param ip The IP address to bind to.
     * @param port The port number to bind to.
     * @throws std::runtime_error if binding fails.
     */
    void bind(const std::string &ip, unsigned short int port) override;

    /**
     * @brief Puts the socket in a listening state.
     * 
     * Used in server applications to accept incoming connections.
     * @param backlog The maximum number of pending connections (default: 5).
     * @throws std::runtime_error if listening fails.
     */
    void listen(int backlog = 5);

    /**
     * @brief Accepts a new incoming connection.
     * 
     * Used in server applications to handle client connections.
     * @return A new `TCPSocket` instance representing the accepted client connection.
     * @throws std::runtime_error if accepting a connection fails.
     */
    TCPSocket* accept();
   
    /**
     * @brief Destructor that cleans up resources.
     * 
     * Ensures the socket is properly closed before destruction.
     */
    ~TCPSocket();
};

#endif /*TCP_SOCKETS_H_*/