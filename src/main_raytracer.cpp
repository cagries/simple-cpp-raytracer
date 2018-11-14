#include "raytracer.h"
#include "ppm.h"

#include <iostream>
#include <memory>

int main(int argc, char** argv)
{
    if (argc < 2) {
        std::cerr << "Usage: ./main <scene_file>" << std::endl;
        return 1;
    }

    rt::RayTracer tracer(argv[1]);
    
    int width;
    int height;

    int max = 0;
    for (const auto& camera : tracer.get_cameras()) {
        int x = camera.plane.width * camera.plane.height;
        if (x > max)
            max = x;
    }

    auto image = std::make_unique<unsigned char[]>(max * 3);
    
    for (const auto& camera : tracer.get_cameras()) {
        tracer.rayTrace(image.get(), camera);
        
        width = camera.plane.width;
        height = camera.plane.height;
        
        ppm::write_ppm(camera.plane.image_name.data(), image.get(), width, height);
    }

    return 0;
}
