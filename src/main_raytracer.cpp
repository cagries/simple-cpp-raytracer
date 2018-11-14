#include "parser.h"
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

    rt::Scene sc;
    sc.loadFromXml(argv[1]);
    
    rt::RayTracer rt;
    rt.scene = std::move(sc);
    
    int width;
    int height;

    int max = 0;
    for (size_t i = 0; i < rt.scene.cameras.size(); i++) {
        int x = rt.scene.cameras[i].plane.width * rt.scene.cameras[i].plane.height;
        if (x > max)
            max = x;
    }

    auto image = std::make_unique<unsigned char[]>(max * 3);
    
    for (size_t a = 0; a < rt.scene.cameras.size(); a++) {
        rt.rayTrace(image.get(), a);
        
        width = rt.scene.cameras[a].plane.width;
        height = rt.scene.cameras[a].plane.height;
        
        ppm::write_ppm(rt.scene.cameras[a].plane.image_name.data(), image.get(), width, height);
    }

    return 0;
}
