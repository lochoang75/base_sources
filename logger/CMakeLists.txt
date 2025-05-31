set(library_name blogger)
option(USE_SYSLOG_LOGGER   "Use syslog" ON)
option(USE_STDLOG_LOGGER   "Use printf" ON)
option(USE_SYSTEMD_LOGGER   "Use journal log" ON)
option(USE_FILE_LOGGER   "Write log to file" ON)

set(logger_src  ${CMAKE_CURRENT_SOURCE_DIR}/src/blogger.cpp
                ${CMAKE_CURRENT_SOURCE_DIR}/src/blogger_server.cpp
                ${CMAKE_CURRENT_SOURCE_DIR}/adapter/src/logger_adapter.cpp
)

if (USE_SYSLOG_LOGGER)
list(APPEND logger_src ${CMAKE_CURRENT_SOURCE_DIR}/adapter/src/syslog_log_client.cpp)
endif (USE_SYSLOG_LOGGER)

if (USE_STDLOG_LOGGER)
list(APPEND logger_src ${CMAKE_CURRENT_SOURCE_DIR}/adapter/src/stdout_log_client.cpp)
endif (USE_STDLOG_LOGGER)

if (USE_SYSTEMD_LOGGER)
list(APPEND logger_src ${CMAKE_CURRENT_SOURCE_DIR}/adapter/src/systemd_log_client.cpp)
endif (USE_SYSTEMD_LOGGER)

if (USE_FILE_LOGGER)
list(APPEND logger_src ${CMAKE_CURRENT_SOURCE_DIR}/adapter/src/file_log_client.cpp)
endif (USE_FILE_LOGGER)


add_library(${library_name} STATIC ${logger_src})
target_include_directories(${library_name} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(${library_name} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/adapter/include)
target_link_libraries(${library_name} PRIVATE ${SYSTEMD_LIBRARIES})
target_include_directories(${library_name} PRIVATE ${SYSTEMD_INCLUDE_DIRS})
target_compile_options(${library_name} PRIVATE ${SYSTEMD_CFLAGS_OTHER})
if (BUILD_TESTS)
add_executable(logger_test ${CMAKE_CURRENT_SOURCE_DIR}/test/logger_test.c)
target_link_libraries(logger_test PRIVATE ${library_name})
target_include_directories(logger_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
endif(BUILD_TESTS)