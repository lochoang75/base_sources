set(library_name posix_timer)
set(${library_name}_src ${CMAKE_CURRENT_SOURCE_DIR}/src/posix_timer.c)
add_library(${library_name} STATIC ${${library_name}_src})
target_include_directories(${library_name} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include
                                                    ${PROJECT_SOURCE_DIR}/logger/include)