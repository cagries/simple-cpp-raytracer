#include <iostream>
#include <vector>
#include <string>

#include "raytracer.h"
#include "RaytracerConfig.h"

#include "lodepng.h"
#include "ppm.h"
#include "cxxopts.hpp"

int main(int argc, char** argv)
{
    // Take care of argument parsing
    cxxopts::Options options("raytracer", "raytracer: A simple C++ ray tracer");
    options.add_options()
        ("v,version", "Print version")
        ("h,help", "Print help message")
        ;

    try {
        auto result = options.parse(argc, argv);

        if (result["v"].as<bool>()) {
            std::cout << "raytracer" <<  " version "
                << Raytracer_VERSION_MAJOR << "."
                << Raytracer_VERSION_MINOR << "."
                << Raytracer_VERSION_PATCH << std::endl;
            return 0;
        } else if (result["h"].as<bool>()) {
            std::cout << options.help() << std::endl;
            return 0;
        }
    } catch (std::exception& e) {
        // Unrecognized option
        std::cout << "[raytracer]: " << e.what() << std::endl 
                  << options.help() << std::endl;
        return 1;
    }

    if (argc != 2) {
        std::cout << "[raytracer]: no scene file provided" << std::endl;
        return 1;
    }


    // Initialize the ray tracer
    rt::RayTracer tracer;
    try {
        tracer.load_scene(argv[1]);
    } catch (std::exception& e) {
        std::cout << "[tinyxml2]: " << e.what() << std::endl;
        return 1;
    }


    // Get maximum image resolution
    int max = 0;
    for (const auto& camera : tracer.get_cameras()) {
        int x = camera.plane.width * camera.plane.height;
        if (x > max)
            max = x;
    }


    // Reuse the same RGBA pixel array 
    std::vector<unsigned char> image(max * 4);
    
    for (const auto& camera : tracer.get_cameras()) {
        tracer.rayTrace(image.data(), camera);
        
        std::size_t width = camera.plane.width;
        std::size_t height = camera.plane.height;
        
        // Remove filename extension
        std::string filename = camera.plane.image_name;

        auto extension = filename.substr(filename.find_last_of(".") + 1);

        if (extension == "png") {
            // Write as a PNG file 
            auto error = lodepng::encode(filename, image, width, height);
            if (error) {
                std::cout << "[lodepng] Error" << error 
                    << ": " << lodepng_error_text(error) 
                    << std::endl;
                return 1;
            }
        } else if (extension == "ppm") {
            // Write it as a ppm file
            ppm::write_ppm(filename, image, width, height);
        } else {
            // Unrecognized format
            std::cout << "[raytracer]: Output format not recognized. Outputting as PPM..." << std::endl;
            ppm::write_ppm(filename + ".ppm", image, width ,height);
            return 1;
        }
    }

    return 0;
}
