set(abstract_src ${CMAKE_CURRENT_SOURCE_DIR}/src/base_event.c)
add_library(abstract STATIC ${abstract_src})
target_include_directories(abstract ${CMAKE_CURRENT_SOURCE_DIR}/include)