set(library_name pollfd_mon)
set(${library_name}_src ${CMAKE_CURRENT_SOURCE_DIR}/src/scheduler_pollfd.c)
add_library(${library_name} STATIC ${${library_name}_src})
target_link_libraries(${library_name} PRIVATE blogger)
target_include_directories(${library_name} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include
)
