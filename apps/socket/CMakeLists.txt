set(socket_client_src ${CMAKE_CURRENT_SOURCE_DIR}/src/socket_client.c)
add_executable(socket_client ${socket_client_src})
target_link_libraries(socket_client PRIVATE blogger)
target_include_directories(socket_client PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

set(socket_server_src ${CMAKE_CURRENT_SOURCE_DIR}/src/socket_server.c)
add_executable(socket_server ${socket_server_src})
target_link_libraries(socket_server PRIVATE blogger)
target_include_directories(socket_server PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)