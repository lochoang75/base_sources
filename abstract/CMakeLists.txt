set(library_name base_abstract)
set(abstract_src ${CMAKE_CURRENT_SOURCE_DIR}/src/abstract_event.c
                 ${CMAKE_CURRENT_SOURCE_DIR}/src/abstract_fd_mon.c
                 ${CMAKE_CURRENT_SOURCE_DIR}/src/abstract_string_helper.c
                 )
add_library(${library_name} STATIC ${abstract_src})
target_include_directories(${library_name} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include
                                                    ${PROJECT_SOURCE_DIR}/fdmon_impl/include)
if (BUILD_TESTS)
endif (BUILD_TESTS)