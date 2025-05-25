if (BUILD_SOCKET_EXAMPLE_APP)
    add_subdirectory(socket)
endif(BUILD_SOCKET_EXAMPLE_APP)

if (BUILD_SHELL_EXAMPLE_APP)
add_subdirectory(readline_shell)
endif(BUILD_SHELL_EXAMPLE_APP)

if (BUILD_CURL_EXAMPLE_APP)
add_subdirectory(curl_app)
endif (BUILD_CURL_EXAMPLE_APP)

if (BUILD_VIRTUAL_ADDR_EXAMPLE_APP)
add_subdirectory(virtual_address)
endif (BUILD_VIRTUAL_ADDR_EXAMPLE_APP)