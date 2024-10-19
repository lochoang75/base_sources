project(epoll_scheduler)
set(${PROJECT_NAME}_src ${CMAKE_CURRENT_SOURCE_DIR}/src/epoll_scheduler.c)
add_library(${PROJECT_NAME} STATIC ${PROJECT_NAME}_src)
target_link_libraries(${PROJECT_NAME} PRIVATE blogger)
