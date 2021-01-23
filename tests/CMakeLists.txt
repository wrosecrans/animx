cmake_minimum_required(VERSION 3.10)
project(AnimXPlugin)


set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_BINARY_DIR}/install)
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/modules)

if(ANIMX_BUILD_MAYA_TESTSUITE)
    add_subdirectory(maya_test)
endif()

if(ANIMX_BUILD_BASE_TESTSUITE)
    add_executable(animx_test base_test/main.cpp)
    target_link_libraries(animx_test AnimX_shared)
    add_test(NAME run_animx_test COMMAND $<TARGET_FILE:animx_test>)
endif()
