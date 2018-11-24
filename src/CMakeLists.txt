# Find header files
if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  # using regular Clang or AppleClang, use libc++
  set (CMAKE_CXX_FLAGS "-stdlib=libc++" ${CMAKE_CXX_FLAGS})
endif()


include_directories("${RT_INCLUDE_DIR}"
    "${RT_SOURCE_DIR}/lodepng"
    "${RT_SOURCE_DIR}/tinyxml2"
    "${RT_SOURCE_DIR}/cxxopts/include"
    )

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
    "${RT_SOURCE_DIR}/lodepng/lodepng.cpp"
    "${RT_SOURCE_DIR}/tinyxml2/tinyxml2.cpp"
)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Werror -Wpedantic -O3 -Wextra")

# Output the created library in these directories
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/lib/")

# Create the library
# add_library (Raytracer ${RT_SOURCES})
# target_link_libraries(Raytracer pthread)

# Create the main executable
add_executable(raytracer "main_raytracer.cpp" ${RT_SOURCES})
target_link_libraries(raytracer pthread)

# Installing the library and executable
install(TARGETS Raytracer DESTINATION "lib/raytracer")

# Installing the header files 
install(
    DIRECTORY "${PROJECT_SOURCE_DIR}/include/"
    DESTINATION "include/raytracer"
    FILES_MATCHING PATTERN "*.h*"
)

