project(base_source)
cmake_minimum_required(VERSION 3.10)
option(BUILD_TESTS "Build test apps" ON)

find_path(KERNEL_HEADERS_DIR linux/unistd.h
        HINTS /usr/src/linux-headers-$(uname -r) /usr/include)

if (KERNEL_HEADERS_DIR)
    message(WARNING "Found Linux kernel headers at ${KERNEL_HEADERS_DIR}")
    include_directories(${KERNEL_HEADERS_DIR})
else()
    message(FATAL_ERROR "Linux kernel headers not found")
endif(KERNEL_HEADERS_DIR)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/abstract/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/logger/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/data_structure/include)

add_subdirectory(logger)
add_subdirectory(epollfd_mon)
add_subdirectory(pollfd_mon)
add_subdirectory(abstract)