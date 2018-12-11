# Find header files
include_directories("${PROJECT_SOURCE_DIR}/include")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Werror -Wpedantic -O3 -Wextra")

add_executable(geometry_test "geometry_test.cpp")
add_executable(sphere_test "sphere_test.cpp")
add_executable(camera_test "camera_test.cpp")
add_executable(triangle_test "triangle_test.cpp")
add_executable(mesh_test "mesh_test.cpp")

target_link_libraries(geometry_test Raytracer gtest gtest_main)
target_link_libraries(sphere_test Raytracer gtest gtest_main)
target_link_libraries(camera_test Raytracer gtest gtest_main)
target_link_libraries(triangle_test Raytracer gtest gtest_main)
target_link_libraries(mesh_test Raytracer gtest gtest_main)

add_test(NAME geometry_test COMMAND geometry_test)
add_test(NAME sphere_test COMMAND sphere_test)
add_test(NAME camera_test COMMAND camera_test)
add_test(NAME triangle_test COMMAND triangle_test)
add_test(NAME mesh_test COMMAND mesh_test)
