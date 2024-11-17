add_executable(test_list ${CMAKE_CURRENT_SOURCE_DIR}/test_list.c)
target_include_directories(test_list PRIVATE ${PROJECT_SOURCE_DIR}/logger/include
                                               ${PROJECT_SOURCE_DIR}/signal_handler/include)
target_link_libraries(test_list blogger signal_handler)