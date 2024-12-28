cmake_minimum_required(VERSION 3.10)
project(base_source)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Og -Wall -Wextra -Wno-unused-function -std=gnu11 -fPIC")
option(BUILD_TESTS "Build test apps" ON)
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules)


include_directories(${CMAKE_CURRENT_SOURCE_DIR}/abstract/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/logger/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/data_structure/include)

add_subdirectory(third_party)
add_subdirectory(logger)
add_subdirectory(signal_handler)
add_subdirectory(data_structure)
add_subdirectory(abstract)
add_subdirectory(apps)
add_subdirectory(fdmon_impl)
add_subdirectory(threadpool)