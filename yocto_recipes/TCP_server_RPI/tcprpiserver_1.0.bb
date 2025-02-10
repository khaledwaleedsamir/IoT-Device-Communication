DESCRIPTION = "TCP server for running on raspberry pi"
SECTION = "examples"
LICENSE = "CLOSED"

SRC_URI = "file://CMakeLists.txt \
    file://Application/Unicast_TCP/server.cpp \
    file://src/channel/server_channel.cpp \
    file://src/sockets/TCP_socket.cpp \
    file://src/sockets/UDP_socket.cpp \
    file://src/channel/channel.hpp \
    file://src/channel/server_channel.hpp \
    file://src/sockets/sockets.hpp \
    file://src/sockets/TCP_socket.hpp \
    file://src/sockets/UDP_socket.hpp"

S = "${WORKDIR}"

inherit cmake

# The rest of the steps are now inherited from the cmake class
