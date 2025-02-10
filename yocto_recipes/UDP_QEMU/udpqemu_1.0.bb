DESCRIPTION = "UDP client for running on simulated environment on QEMU"
SECTION = "examples"
LICENSE = "CLOSED"

SRC_URI = "file://CMakeLists.txt \
    file://Application/Multicast_UDP/client1.cpp \
    file://src/channel/client_channel.cpp \
    file://src/sockets/TCP_socket.cpp \
    file://src/sockets/UDP_socket.cpp \
    file://src/channel/channel.hpp \
    file://src/channel/client_channel.hpp \
    file://src/sockets/sockets.hpp \
    file://src/sockets/TCP_socket.hpp \
    file://src/sockets/UDP_socket.hpp"

S = "${WORKDIR}"

inherit cmake

# The rest of the steps are now inherited from the cmake class
