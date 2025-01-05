add_executable(test_posix_timer test_posix_timer.c)
target_include_directories(test_posix_timer PRIVATE ${PROJECT_SOURCE_DIR}/logger/include
                                                    ${PROJECT_SOURCE_DIR}/abstract/include
                                                    )
target_link_libraries(test_posix_timer blogger base_abstract rt posix_timer fdmon_impl)