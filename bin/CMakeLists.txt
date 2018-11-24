## Find header files
include_directories("${PROJECT_SOURCE_DIR}/include")
include_directories("${PROJECT_SOURCE_DIR}/src/lodepng")
include_directories("${PROJECT_SOURCE_DIR}/src/tinyxml2")
include_directories("${PROJECT_SOURCE_DIR}/src/cxxopts/include")

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin/")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Werror -Wpedantic -O3 -Wextra")

# Create the main executable
add_executable(raytracer "${PROJECT_SOURCE_DIR}/src/main_raytracer.cpp")

target_link_libraries(raytracer Raytracer)

install(TARGETS raytracer DESTINATION "bin")
