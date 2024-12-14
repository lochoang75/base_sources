add_executable(test_threadpool ${CMAKE_CURRENT_SOURCE_DIR}/test_threadpool.c)
target_link_libraries(test_threadpool   blogger pthread threadpool)
target_include_directories(test_threadpool PRIVATE      ${PROJECT_SOURCE_DIR}/abstract/include
                                                        ${PROJECT_SOURCE_DIR}/logger/include
                                                        ${PROJECT_SOURCE_DIR}/threadpool/include
                            )

add_executable(test_threadpool_shutdown ${CMAKE_CURRENT_SOURCE_DIR}/test_shutdown.c)
target_link_libraries(test_threadpool_shutdown   blogger pthread threadpool)
target_include_directories(test_threadpool_shutdown PRIVATE      ${PROJECT_SOURCE_DIR}/abstract/include
                                                                ${PROJECT_SOURCE_DIR}/logger/include
                                                                ${PROJECT_SOURCE_DIR}/threadpool/include
                            )

add_executable(test_threadpool_heavy ${CMAKE_CURRENT_SOURCE_DIR}/test_threadpool_heavy.c)
target_link_libraries(test_threadpool_heavy   blogger pthread threadpool)
target_include_directories(test_threadpool_heavy PRIVATE      ${PROJECT_SOURCE_DIR}/abstract/include
                                                                ${PROJECT_SOURCE_DIR}/logger/include
                                                                ${PROJECT_SOURCE_DIR}/threadpool/include
                            )