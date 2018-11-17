# Find header files
include_directories("${PROJECT_SOURCE_DIR}/include")

add_executable(geometry_test "geometry_test.cpp")
add_executable(sphere_test "sphere_test.cpp")

target_link_libraries(geometry_test Raytracer gtest gtest_main)
target_link_libraries(sphere_test Raytracer gtest gtest_main)

add_test(NAME geometry_test COMMAND geometry_test)

add_test(NAME sphere_test COMMAND sphere_test)
