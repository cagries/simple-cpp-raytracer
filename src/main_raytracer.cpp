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

    parser::Scene sc;
    sc.loadFromXml(argv[1]);
    
    RayTracer rt;
    rt.scene = sc;
    
    rt.rayTrace(0);
    
    int width = rt.scene.cameras[0].plane.width;
    int height = rt.scene.cameras[0].plane.height;
    
    
    unsigned char* image = new unsigned char [width * height * 3];
    
    int i = 0;
    int j = 0;
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            image[i]   = rt.images[0][j].x;
            image[i+1] = rt.images[0][j].y;
            image[i+2] = rt.images[0][j].z;
            i += 3;
            j++;
        }
    }
    write_ppm(argv[2], image, width, height);

    return 0;
}
