add_executable(test_pollfd_mon ${CMAKE_CURRENT_SOURCE_DIR}/test_pollfd_mon.c)
target_link_libraries(test_pollfd_mon blogger
                                            base_abstract
                                            fdmon_impl
                                            signal_handler)
target_include_directories(test_pollfd_mon PRIVATE    ${PROJECT_SOURCE_DIR}/abstract/include
                                                            ${PROJECT_SOURCE_DIR}/logger/include
                                                            ${PROJECT_SOURCE_DIR}/signal_handler/include
                                                            )