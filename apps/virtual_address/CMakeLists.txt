add_executable(virtual_addr ${CMAKE_CURRENT_SOURCE_DIR}/src/virtual_address.c)
target_include_directories(virtual_addr PRIVATE
                                ${PROJECT_SOURCE_DIR}/logger/include
                                ${PROJECT_SOURCE_DIR}/signal_handler/include)
target_link_libraries(virtual_addr signal_handler blogger)