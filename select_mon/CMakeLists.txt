set(library_name select_mon)
set(${library_name}_src ${CMAKE_CURRENT_SOURCE_DIR}/src/scheduler_select.c)
add_library(${library_name} STATIC ${${library_name}_src})
target_link_libraries(${library_name} PRIVATE blogger)
