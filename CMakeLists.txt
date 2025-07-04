cmake_minimum_required(VERSION 3.28 FATAL_ERROR)

set(PROJECT_NAME localchat)
set(CMAKE_CXX_STANDARD 23)
project(${PROJECT_NAME} LANGUAGES CXX VERSION 1.0.1)


if(WIN32)
  set(PLATFORM windows)
elseif(LINUX)
  set(PLATFORM linux)
endif()


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



add_executable(${PROJECT_NAME} ${SOURCES} libs/AlexandreRouma-net/net.cpp)

target_link_directories(${PROJECT_NAME} PRIVATE libs)
target_include_directories(${PROJECT_NAME} PRIVATE libs)


include(FetchContent)


set(FTXUI_ENABLE_INSTALL OFF CACHE BOOL "" FORCE)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE) # To build FTXUI as static library

# For FTXUI

message(STATUS "Configuring FTXUI...")
FetchContent_Declare(ftxui
  GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
  GIT_TAG v6.1.9
)
FetchContent_MakeAvailable(ftxui)



# For jsoncpp

message(STATUS "Configuring jsoncpp...")
FetchContent_Declare(jsoncpp
  GIT_REPOSITORY https://github.com/open-source-parsers/jsoncpp.git
  GIT_TAG 1.9.6
  EXCLUDE_FROM_ALL
)
FetchContent_Populate(jsoncpp)
add_subdirectory(${jsoncpp_SOURCE_DIR} ${jsoncpp_BINARY_DIR} EXCLUDE_FROM_ALL)

# Disable uneccessary things for jsoncpp
set(JSONCPP_WITH_TESTS OFF)
set(JSONCPP_WITH_POST_BUILD_UNITTEST OFF)




target_link_libraries(${PROJECT_NAME} PRIVATE
    # Chose a submodule
    ftxui::component
    ftxui::dom
    ftxui::screen

    jsoncpp_static # static linking with jsoncpp
)




if(WIN32)
    target_compile_definitions(${PROJECT_NAME} PRIVATE NOMINMAX)
    target_link_libraries(${PROJECT_NAME} PRIVATE wsock32 ws2_32 iphlpapi)
endif()




install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin COMPONENT executable)




# Building package
message(STATUS "Building .deb package for Linux: ON")

set(CPACK_GENERATOR "DEB")
set(CPACK_PACKAGE_NAME ${PROJECT_NAME})
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
set(CPACK_DEBIAN_PACKAGE_ARCHITECTURE "amd64")
set(CPACK_PACKAGE_DESCRIPTION "Console-based local network messenger")
set(CPACK_DEBIAN_PACKAGE_SECTION "utils")
set(CPACK_DEBIAN_PACKAGE_LICENSE "MIT")
set(CPACK_PACKAGING_INSTALL_PREFIX "/usr")
set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${PROJECT_VERSION}-${PLATFORM}-${CPACK_DEBIAN_PACKAGE_ARCHITECTURE}")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Maksim Shchavelev maksimshchavelev@gmail.com")
set(CPACK_DEBIAN_PACKAGE_HOMEPAGE "https://github.com/maksimshchavelev/localchat")

include(CPack)




