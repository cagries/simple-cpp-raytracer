
# Find header files
include_directories("${PROJECT_SOURCE_DIR}/include")

# Files to use for 'raytracer' (except the main file)
set (RT_SOURCES "camera.cpp"
    "geometry.cpp"
    "light.cpp"
    "mesh.cpp"
    "parser.cpp"
    "ppm.cpp"
    "raytracer.cpp"
    "sphere.cpp"
    "tinyxml2.cpp"
    "triangle.cpp"
)

# message (FATAL_ERROR "The message: ${PROJECT_SOURCE_DIR}")

# Produce the executable at project root level

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Werror -Wpedantic -O3")

# Create the library
add_library (Raytracer ${RT_SOURCES})

# Create the executable
add_executable(raytracer "main_raytracer.cpp")

target_link_libraries(Raytracer pthread)

target_link_libraries(raytracer pthread Raytracer)
