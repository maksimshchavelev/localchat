cmake_minimum_required(VERSION 3.28 FATAL_ERROR)

set(PROJECT_NAME LocalChat)
set(PROJECT_VERSION 1.0.0)
set(CMAKE_CXX_STANDARD 23)
project(${PROJECT_NAME} LANGUAGES CXX)


# If no build type is set, default to Release
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to 'Release' by default")
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()


# Finding sources
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    ${CMAKE_SOURCE_DIR}/src/*.cpp
    ${CMAKE_SOURCE_DIR}/src/*.hpp)


add_executable(${PROJECT_NAME} ${SOURCES})


target_link_libraries(${PROJECT_NAME} drogon)
target_link_libraries(${PROJECT_NAME} ncurses)
target_link_libraries(${PROJECT_NAME} jsoncpp)
