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


# ======= Multicast UDP =======
# UDP Clients
add_executable(Multicast_UDP_client Application/Multicast_UDP/client1.cpp ${SRC_FILES})

# Install the compiled executable
install(TARGETS Multicast_UDP_client DESTINATION bin)

# Installation Rules
install(FILES ${CMAKE_SOURCE_DIR}/src/sockets/sockets.hpp
              ${CMAKE_SOURCE_DIR}/src/sockets/TCP_socket.hpp
              ${CMAKE_SOURCE_DIR}/src/sockets/UDP_socket.hpp
              ${CMAKE_SOURCE_DIR}/src/channel/channel.hpp
              ${CMAKE_SOURCE_DIR}/src/channel/client_channel.hpp
              DESTINATION include)