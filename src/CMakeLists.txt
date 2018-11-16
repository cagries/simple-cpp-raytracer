
# Find header files
include_directories("${PROJECT_SOURCE_DIR}/include")

# Files to use for 'raytracer'
set (RT_SOURCES "camera.cpp"
    "geometry.cpp"
    "light.cpp"
    "main_raytracer.cpp"
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
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin/")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Werror -Wpedantic -O3")

# Create the executable
add_executable(raytracer ${RT_SOURCES})

target_link_libraries(raytracer pthread)
