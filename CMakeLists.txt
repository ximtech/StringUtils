cmake_minimum_required(VERSION 3.20)
project(StringUtils VERSION 1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES StringUtils.c include/StringUtils.h)
add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})
set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "")

target_include_directories(${PROJECT_NAME} PUBLIC
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)

install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/StringUtils.h
        DESTINATION ${CMAKE_INSTALL_PREFIX}/include/StringUtils)

install(TARGETS ${PROJECT_NAME}
        EXPORT StringUtilsExport
        DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/StringUtils)

install(EXPORT StringUtilsExport
        FILE StringUtils-config.cmake
        DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/StringUtils)