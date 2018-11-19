#include <iostream>
#include <vector>
#include <string>

#include "raytracer.h"

#include "lodepng.h"
#include "ppm.h"

int main(int argc, char** argv)
{
    if (argc < 2) {
        std::cerr << "Usage: raytracer <scene_file>" << std::endl;
        return 1;
    }

    // Initialize the ray tracer
    rt::RayTracer tracer(argv[1]);
    

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
                std::cout << "[lodepng] error" << error 
                    << ": " << lodepng_error_text(error) 
                    << std::endl;
                return 1;
            }
        } else if (extension == "ppm") {
            // Write it as a ppm file
            ppm::write_ppm(filename, image, width, height);
        } else {
            // Unrecognized format
            std::cout << "raytracer: not recognized output format" << std::endl;
            return 1;
        }
    }

    return 0;
}
