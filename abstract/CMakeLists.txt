set(library_name base_abstract)
set(abstract_src ${CMAKE_CURRENT_SOURCE_DIR}/src/base_event.c
                 ${CMAKE_CURRENT_SOURCE_DIR}/src/base_fd_mon.c)
add_library(${library_name} STATIC ${abstract_src})
target_include_directories(${library_name} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include
                                                    ${PROJECT_SOURCE_DIR}/epollfd_mon/include
                                                    ${PROJECT_SOURCE_DIR}/select_mon/include
                                                    ${PROJECT_SOURCE_DIR}/pollfd_mon/include)
if (BUILD_TESTS)
add_subdirectory(test)
endif (BUILD_TESTS)