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

    Scene sc;
    sc.loadFromXml(argv[1]);
    
    RayTracer rt;
    rt.scene = sc;
    
//    Vec3f color_black = {0, 0, 0};
//    Ray observeRay = rt.scene.cameras[0].generate_ray(210, 180);
//    rt.calculateColor(observeRay, color_black, 0);
    
    int width;
    int height;
    int i = 0, j = 0;
    
    for (size_t a = 0; a < sc.cameras.size(); a++) {
        std::cout << std::to_string(a);
        rt.rayTrace(a);
        
        width = rt.scene.cameras[a].plane.width;
        height = rt.scene.cameras[a].plane.height;
        
        unsigned char* image = new unsigned char [width * height * 3];
        
        i = 0;
        j = 0;
        for (int y = 0; y < height; ++y)
        {
            for (int x = 0; x < width; ++x)
            {
                image[i]   = rt.images[a][j].x;
                image[i+1] = rt.images[a][j].y;
                image[i+2] = rt.images[a][j].z;
                i += 3;
                j++;
            }
        }
        
        write_ppm((std::to_string(a) + std::string(argv[2])).data(), image, width, height);
    }
    
     
    return 0;
}
