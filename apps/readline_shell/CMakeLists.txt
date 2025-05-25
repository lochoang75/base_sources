set(base_shell_src  ${CMAKE_CURRENT_SOURCE_DIR}/src/base_shell.cpp
                    ${CMAKE_CURRENT_SOURCE_DIR}/src/application_mon.cpp )

list(APPEND base_shell_src
                    ${CMAKE_CURRENT_SOURCE_DIR}/src/control/auto_complete_entry.cpp
                    ${CMAKE_CURRENT_SOURCE_DIR}/src/control/auto_complete_lut.cpp
                    ${CMAKE_CURRENT_SOURCE_DIR}/src/control/auto_complete.cpp
                    ${CMAKE_CURRENT_SOURCE_DIR}/src/control/auto_complete_director.cpp
                    ${CMAKE_CURRENT_SOURCE_DIR}/src/control/command_executor.cpp)

list(APPEND base_shell_src
                    ${CMAKE_CURRENT_SOURCE_DIR}/src/data_model/command_data.cpp)

list(APPEND base_shell_src
                    ${CMAKE_CURRENT_SOURCE_DIR}/src/view/application_view.cpp
                    ${CMAKE_CURRENT_SOURCE_DIR}/src/view/drawing_factory.cpp
                    ${CMAKE_CURRENT_SOURCE_DIR}/src/view/drawing_request.cpp
                    ${CMAKE_CURRENT_SOURCE_DIR}/src/view/drawing_ncurses_impl.cpp
                    )


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

if(BUILD_TESTS)
add_executable(test_readline test/readline_example.c)
target_link_libraries(test_readline ${Readline_LIBRARY})
add_executable(test_curses test/curses_example.c)
target_link_libraries(test_curses ${CURSES_LIBRARIES})
endif(BUILD_TESTS)