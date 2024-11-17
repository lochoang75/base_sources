add_executable(pollfd_test ${CMAKE_CURRENT_SOURCE_DIR}/test_pollfd_scheduler.c)
target_link_libraries(pollfd_test PRIVATE base_abstract pollfd_mon blogger)
target_include_directories(logger_test PRIVATE ${PROJECT_SOURCE_DIR}/abstract/include
                                                ${PROJECT_SOURCE_DIR}/logger/include)