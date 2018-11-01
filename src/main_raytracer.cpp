#include "camera.h"
#include "parser.h"
#include "raytracer.h"
#include "ppm.h"

#include <iostream>

int main(int argc, char** argv)
{
    if (argc < 2) {
        std::cerr << "Usage: ./main <scene_file>" << std::endl;
        return 1;
    }

    rt::Scene sc;
    sc.loadFromXml(argv[1]);
    
    rt::RayTracer rt;
    rt.scene = sc;
    
    int width;
    int height;

    int max = 0;
    for (size_t i = 0; i < sc.cameras.size(); i++) {
        int x = sc.cameras[i].plane.width * sc.cameras[i].plane.height;
        if (x > max)
            max = x;
    }

    unsigned char* image = new unsigned char [max * 3];
    
    for (size_t a = 0; a < sc.cameras.size(); a++) {
        rt.rayTrace(image, a);
        
        width = rt.scene.cameras[a].plane.width;
        height = rt.scene.cameras[a].plane.height;
        
        ppm::write_ppm(sc.cameras[a].plane.image_name.data(), image, width, height);
    }
    
     
    return 0;
}
