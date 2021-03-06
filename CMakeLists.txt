cmake_minimum_required (VERSION 3.0.2)
project (Raytracer)

# Version numbers
set (Raytracer_VERSION_MAJOR 0)
set (Raytracer_VERSION_MINOR 3)
set (Raytracer_VERSION_PATCH 0)

include(CTest)

if (RT_BUILD_TESTS)
    ### Google Test specific configuration ### 

    # Download and unpack googletest at configure time
    configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
    execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
      RESULT_VARIABLE result
      WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
    if(result)
      message(FATAL_ERROR "CMake step for googletest failed: ${result}")
    endif()
    execute_process(COMMAND ${CMAKE_COMMAND} --build .
      RESULT_VARIABLE result
      WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
    if(result)
      message(FATAL_ERROR "Build step for googletest failed: ${result}")
    endif()

    # Prevent overriding the parent project's compiler/linker
    # settings on Windows
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

    # Add googletest directly to our build. This defines
    # the gtest and gtest_main targets.
    add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
                     ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
                     EXCLUDE_FROM_ALL)

    # The gtest/gtest_main targets carry header search path
    # dependencies automatically when using CMake 2.8.11 or
    # later. Otherwise we have to add them here ourselves.

    # if (CMAKE_VERSION VERSION_LESS 2.8.11)
    include_directories("${gtest_SOURCE_DIR}/include")
    # endif()

    # Add the test directory
    add_subdirectory("${PROJECT_SOURCE_DIR}/test")
endif()

set(RT_SOURCE_DIR "${PROJECT_SOURCE_DIR}/src")
set(RT_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include")

configure_file(
    "${RT_INCLUDE_DIR}/RaytracerConfig.h.in"
    "${RT_INCLUDE_DIR}/RaytracerConfig.h"
)

add_subdirectory("${PROJECT_SOURCE_DIR}/src") 
add_subdirectory("${PROJECT_SOURCE_DIR}/bin") 
