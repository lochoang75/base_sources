cmake_minimum_required(VERSION 3.10)
project(base_source)
include(cmake/config/Options.cmake)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Og -Wall -Wextra -Wno-unused-function -std=gnu11 -fPIC")
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules)


include_directories(${CMAKE_CURRENT_SOURCE_DIR}/abstract/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/logger/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/data_structure/include)

configure_file(cmake/config/module_config.h.in ${CMAKE_BINARY_DIR}/config_gen/module_config.h)
include_directories(${CMAKE_BINARY_DIR}/config_gen)

add_subdirectory(third_party)
add_subdirectory(logger)
add_subdirectory(signal_handler)
add_subdirectory(data_structure)
add_subdirectory(abstract)
add_subdirectory(apps)
add_subdirectory(fdmon_impl)
add_subdirectory(threadpool)
add_subdirectory(posix_timer)