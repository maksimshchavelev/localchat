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
    ${CMAKE_SOURCE_DIR}/src/*.hpp
    ${CMAKE_SOURCE_DIR}/src/*.tpp)


# fingind jsoncpp
find_package(jsoncpp CONFIG REQUIRED)


add_executable(${PROJECT_NAME} ${SOURCES} libs/AlexandreRouma-net/net.cpp)

target_link_directories(${PROJECT_NAME} PRIVATE libs)
target_include_directories(${PROJECT_NAME} PRIVATE libs)


# For FTXUI
include(FetchContent)
FetchContent_Declare(ftxui
  GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
  GIT_TAG v6.1.9
)
FetchContent_MakeAvailable(ftxui)

target_link_libraries(${PROJECT_NAME} PRIVATE
    # Chose a submodule
    ftxui::component
    ftxui::dom
    ftxui::screen

    jsoncpp_static
)



if(WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE wsock32 ws2_32 iphlpapi)
    target_compile_options(${PROJECT_NAME} PRIVATE /std:c++23)
endif()
