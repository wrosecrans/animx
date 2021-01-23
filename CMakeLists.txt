cmake_minimum_required(VERSION 3.10)
project(AnimX)
set(CMAKE_CXX_STANDARD 17)
enable_testing()

# set( CMAKE_VERBOSE_MAKEFILE on )
option ( MAYA_64BIT_TIME_PRECISION "Use the library with a version of Maya including or after Maya after 2017 update 3" 1 )
option ( ANIMX_BUILD_MAYA_TESTSUITE "Build the Maya plugin test suite.  Requires Maya." "Auto" )
option ( ANIMX_BUILD_BASE_TESTSUITE "Build the Animx test suite." 1 )
option ( ANIMX_BUILD_STATIC "Build a static version of the AnimX library." 1 )
option ( ANIMX_BUILD_SHARED "Build a shared library version of the AnimX library." 1 )

if(${ANIMX_BUILD_MAYA_TESTSUITE} STREQUAL "Auto")
    find_package(Maya)
elseif(${ANIMX_BUILD_MAYA_TESTSUITE} EQUAL 1)
    find_package(Maya REQUIRED)
endif()

if(Maya_FOUND)
    message("Found Maya, building plugin / testsuite.")
    set(ANIMX_BUILD_MAYA_TESTSUITE 1)
endif()

if (MAYA_64BIT_TIME_PRECISION)
    add_definitions(-DMAYA_64BIT_TIME_PRECISION)
endif()

if (APPLE AND ${CMAKE_CXX_COMPILER_ID} MATCHES "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
endif()

add_subdirectory(src)
add_subdirectory(tests)
