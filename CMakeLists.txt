cmake_minimum_required(VERSION 3.10)
project(IoT_Device_Communication)

# Use C++17 standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set output directory for compiled binaries
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Include directories for headers
include_directories(${CMAKE_SOURCE_DIR}/src)

# Find all source files inside src/ (sockets and channel implementations)
file(GLOB_RECURSE SRC_FILES src/**/*.cpp)

# ======= Unicast TCP =======
# TCP Client
add_executable(Unicast_TCP_client Application/Unicast_TCP/client.cpp ${SRC_FILES})
# TCP Server
add_executable(Unicast_TCP_server Application/Unicast_TCP/server.cpp ${SRC_FILES})

# ======= Multicast UDP =======
# UDP Clients
add_executable(Multicast_UDP_client1 Application/Multicast_UDP/client1.cpp ${SRC_FILES})
add_executable(Multicast_UDP_client2 Application/Multicast_UDP/client2.cpp ${SRC_FILES})
# UDP Server
add_executable(Multicast_UDP_server Application/Multicast_UDP/server.cpp ${SRC_FILES})
