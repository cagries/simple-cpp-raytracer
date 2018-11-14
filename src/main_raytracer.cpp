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
    // sc.loadFromXml(argv[1]);
    
    // rt::RayTracer rt;
    // rt.scene = std::move(sc);
    
    int width;
    int height;

    int max = 0;
    for (size_t i = 0; i < tracer.scene.cameras.size(); i++) {
        int x = tracer.scene.cameras[i].plane.width * tracer.scene.cameras[i].plane.height;
        if (x > max)
            max = x;
    }

    auto image = std::make_unique<unsigned char[]>(max * 3);
    
    for (size_t a = 0; a < tracer.scene.cameras.size(); a++) {
        tracer.rayTrace(image.get(), a);
        
        width = tracer.scene.cameras[a].plane.width;
        height = tracer.scene.cameras[a].plane.height;
        
        ppm::write_ppm(tracer.scene.cameras[a].plane.image_name.data(), image.get(), width, height);
    }

    return 0;
}
