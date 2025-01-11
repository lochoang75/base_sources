add_executable(test_posix_timer test_posix_timer.c)
target_include_directories(test_posix_timer PRIVATE ${PROJECT_SOURCE_DIR}/logger/include
                                                    ${PROJECT_SOURCE_DIR}/abstract/include
                                                    )
target_link_libraries(test_posix_timer blogger base_abstract rt posix_timer)

add_executable(test_timerfd test_timer_use_fd.c)
target_include_directories(test_timerfd PRIVATE ${PROJECT_SOURCE_DIR}/logger/include
                                                    ${PROJECT_SOURCE_DIR}/abstract/include
                                                    )
target_link_libraries(test_timerfd blogger base_abstract rt posix_timer)

if(SUPPORT_TIMER_FD_WITH_POLL)
target_link_libraries(test_posix_timer fdmon_impl)
target_link_libraries(test_timerfd fdmon_impl)
endif(SUPPORT_TIMER_FD_WITH_POLL)