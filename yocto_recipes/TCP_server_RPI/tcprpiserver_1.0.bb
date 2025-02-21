DESCRIPTION = "TCP server for running on raspberry pi"
SECTION = "examples"
LICENSE = "CLOSED"

SRC_URI = "file://CMakeLists.txt \
    file://Application/Unicast_TCP/server.cpp \
    file://src/channel/server_channel.cpp \
    file://src/sockets/TCP_socket.cpp \
    file://src/sockets/UDP_socket.cpp \
    file://src/HW_modules/CLed.cpp \ 
    file://src/HW_modules/CBsc.cpp \
    file://src/HW_modules/CGpio.cpp \
    file://src/HW_modules/CMemoryMapper.cpp \
    file://src/HW_modules/CPhysicalMemory.cpp \ 
    file://src/HW_modules/CRaspberryPi.cpp \
    file://src/HW_modules/CSystemTimer.cpp \
    file://src/HW_modules/CDht11.cpp \ 
    file://src/channel/channel.hpp \
    file://src/channel/server_channel.hpp \
    file://src/sockets/sockets.hpp \
    file://src/sockets/TCP_socket.hpp \
    file://src/sockets/UDP_socket.hpp \
    file://src/HW_modules/CLed.hpp \ 
    file://src/HW_modules/CBsc.hpp \
    file://src/HW_modules/CGpio.hpp \
    file://src/HW_modules/CMemoryMapper.hpp \
    file://src/HW_modules/CPhysicalMemory.hpp \ 
    file://src/HW_modules/CRaspberryPi.hpp \
    file://src/HW_modules/CSystemTimer.hpp \
    file://src/HW_modules/CDht11.hpp"

S = "${WORKDIR}"

inherit cmake

# The rest of the steps are now inherited from the cmake class
