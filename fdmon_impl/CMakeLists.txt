set(library_name fdmon_impl)
set(fdmon_impl_src     ${CMAKE_CURRENT_SOURCE_DIR}/src/pollfd_mon.c
                        ${CMAKE_CURRENT_SOURCE_DIR}/src/selectfd_mon.c
                        ${CMAKE_CURRENT_SOURCE_DIR}/src/mon_factory.c
                        ${CMAKE_CURRENT_SOURCE_DIR}/src/epollfd_mon.c
    )
add_library(${library_name} STATIC ${fdmon_impl_src})
target_include_directories(${library_name} PRIVATE  ${CMAKE_CURRENT_SOURCE_DIR}/include
                                                    ${CMAKE_CURRENT_SOURCE_DIR}/internal
    )
target_link_libraries(${library_name} blogger base_abstract)
if (BUILD_TESTS)
add_subdirectory(test)
endif(BUILD_TESTS)