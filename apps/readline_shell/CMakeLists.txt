set(base_shell_src  ${CMAKE_CURRENT_SOURCE_DIR}/src/base_shell.cpp
                    ${CMAKE_CURRENT_SOURCE_DIR}/src/auto_complete.cpp)
add_executable(base_shell ${base_shell_src})

find_package(Readline REQUIRED)
find_package(Curses REQUIRED)
target_include_directories(base_shell PRIVATE   ${CMAKE_CURRENT_SOURCE_DIR}/include
                                                ${PROJECT_SOURCE_DIR}/logger/include
                                                ${PROJECT_SOURCE_DIR}/signal_handler/include
                                                ${Readline_INCLUDE_DIR}
                                                ${CURSES_INCLUDE_DIR}
)
target_link_libraries(base_shell blogger signal_handler ${Readline_LIBRARY} ${CURSES_LIBRARIES})