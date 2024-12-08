add_executable(test_scheduler_pollfd ${CMAKE_CURRENT_SOURCE_DIR}/scheduler_pollfd_test.c)
target_link_libraries(test_scheduler_pollfd blogger base_abstract pollfd_mon signal_handler)
target_include_directories(test_scheduler_pollfd PRIVATE    ${PROJECT_SOURCE_DIR}/abstract/include
                                                            ${PROJECT_SOURCE_DIR}/logger/include
                                                            ${PROJECT_SOURCE_DIR}/signal_handler/include
                                                            )
