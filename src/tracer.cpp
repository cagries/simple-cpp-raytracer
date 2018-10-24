#include "parser.h"
#include "camera.h"
#include "ppm.h"

#include <iostream>
#include <limits>


int main(int argc, char **argv)
{

    if (argc < 3) {
        std::cerr << "Usage: ./tracer <scene_file> <output_file>" << std::endl;
        return 1;
    }

    parser::Scene sc;
    sc.loadFromXml(argv[1]);

    Camera c = sc.cameras[0];
    float t_min = std::numeric_limits<float>::max();

    std::vector<Vec3f> pixels(c.plane.width * c.plane.height,
            {0,0,0});

    for (int i = 0; i < c.plane.width; i++) {
        for (int j = 0; j < c.plane.height; j++) {
            Ray r = c.generate_ray(i, j);

            // Only test for spheres for now
            HitRecord hr, record;
            bool hit = false;

            for (auto &triangle : sc.triangles) {
                if (triangle.hit(r, &hr)) {
                    if (hr.t < t_min) {
                        t_min = hr.t;
                        record = hr;
                        hit = true;
                    }
                }
            }

            // Color the pixel
            if (hit) {
                // For now, just color it white
                /*
                Sphere* sp = static_cast<Sphere*>(s);

                float f = sp->diff(r(hr.t));
                std::cout << f << std::endl;
                */

                pixels[i * c.plane.width + j] = {255, 255, 255};
            }
        }
    }

    unsigned char *array = new unsigned char[c.plane.width * c.plane.height * 3];
    int idx = 0;
    for (const auto& pixel : pixels) {
        array[idx++] = pixel.x;
        array[idx++] = pixel.y;
        array[idx++] = pixel.z;
    }

    write_ppm(argv[2], array, c.plane.width, c.plane.height);
    delete[] array;

    return 0;
}
