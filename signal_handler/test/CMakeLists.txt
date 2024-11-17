add_executable(signal_test ${CMAKE_CURRENT_SOURCE_DIR}/signal_test.c)
target_link_libraries(signal_test signal_handler blogger signal_handler)
target_include_directories(signal_test PRIVATE ${PROJECT_SOURCE_DIR}/blogger/include
                                        ${PROJECT_SOURCE_DIR}/signal_handler/include)