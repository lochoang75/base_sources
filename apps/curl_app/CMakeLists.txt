add_executable(curl_http_ex ${CMAKE_CURRENT_SOURCE_DIR}/src/curl_http.c)
target_include_directories(curl_http_ex PRIVATE
                                    ${PROJECT_SOURCE_DIR}/logger/include)
target_link_libraries(curl_http_ex blogger curl)