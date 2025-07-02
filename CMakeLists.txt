cmake_minimum_required(VERSION 3.16)
project(HttpServer LANGUAGES CXX)

# Use C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Output compile_commands.json for LSP support
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Directories
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(NET_DIR ${SRC_DIR}/net)
set(HTTP_DIR ${SRC_DIR}/http)
set(SERVER_DIR ${SRC_DIR}/server)
set(UTIL_DIR ${SRC_DIR}/util)
set(TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/test)

# Include directories for headers
include_directories(
    ${SRC_DIR}
    ${NET_DIR}
    ${HTTP_DIR}
    ${SERVER_DIR}
    ${UTIL_DIR}
)

# Source files (explicit to avoid globbing build/)
set(SRC_FILES
    ${SRC_DIR}/main.cpp
    ${SERVER_DIR}/http_server.cpp
    ${NET_DIR}/socket.cpp
		${NET_DIR}/socket_binder.cpp
		${NET_DIR}/socket_connector.cpp
		${NET_DIR}/socket_listener.cpp
    ${HTTP_DIR}/http_response.cpp
		${HTTP_DIR}/http_request.cpp
    ${HTTP_DIR}/mime_types.cpp
    ${UTIL_DIR}/logger.cpp
)

# Build the main HTTP server executable
add_executable(http_server ${SRC_FILES})

# Optional test executable using raw sockets
add_executable(test_requests ${TEST_DIR}/test_request.cpp)

