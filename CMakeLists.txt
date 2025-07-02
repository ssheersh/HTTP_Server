
cmake_minimum_required(VERSION 3.14)
project(http_server)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Source directories
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(NET_DIR ${SRC_DIR}/net)
set(HTTP_DIR ${SRC_DIR}/http)
set(SERVER_DIR ${SRC_DIR}/server)
set(UTILS_DIR ${SRC_DIR}/utils)

# Collect all source files
file(GLOB_RECURSE SRC_FILES
    ${SRC_DIR}/main.cpp
    ${NET_DIR}/*.cpp
    ${HTTP_DIR}/*.cpp
    ${SERVER_DIR}/*.cpp
)

# Include paths
include_directories(
    ${SRC_DIR}
    ${NET_DIR}
    ${HTTP_DIR}
    ${SERVER_DIR}
    ${UTILS_DIR}
)

# Create the executable
add_executable(http_server ${SRC_FILES})

# Optional: link pthread if using multithreading later
# target_link_libraries(http_server pthread)

# Optional: Test support
enable_testing()
add_executable(test_requests tests/test_requests.cpp)
add_test(NAME BasicTest COMMAND test_requests)
