# Find header files
include_directories("${PROJECT_SOURCE_DIR}/include"
    "${PROJECT_SOURCE_DIR}/src/lodepng"
    "${PROJECT_SOURCE_DIR}/src/tinyxml2"
    )

# Find lodepng header
# Files to use for 'raytracer' (except the main file)
set (RT_SOURCES "camera.cpp"
    "geometry.cpp"
    "light.cpp"
    "mesh.cpp"
    "parser.cpp"
    "ppm.cpp"
    "raytracer.cpp"
    "sphere.cpp"
    "triangle.cpp"
    "${PROJECT_SOURCE_DIR}/src/lodepng/lodepng.cpp"
    "${PROJECT_SOURCE_DIR}/src/tinyxml2/tinyxml2.cpp"
)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Werror -Wpedantic -O3 -Wextra")

# Output the created libraries and executables in these directories
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/lib/")
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin/")


# Create the library
add_library (Raytracer ${RT_SOURCES})

# Create the main executable
add_executable(raytracer "main_raytracer.cpp")


target_link_libraries(Raytracer pthread)

target_link_libraries(raytracer pthread Raytracer)


# Installing the library and executable
install(TARGETS Raytracer DESTINATION "lib/raytracer")

install(TARGETS raytracer DESTINATION "bin")

# Installing the header files 
install(
    DIRECTORY "${PROJECT_SOURCE_DIR}/include/"
    DESTINATION "include/raytracer"
    FILES_MATCHING PATTERN "*.h*")

