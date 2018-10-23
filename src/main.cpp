#include "camera.h"
#include "parser.h"

#include <iostream>

int main(int argc, char** argv)
{
if (argc < 2) {
    std::cerr << "Usage: ./main <scene_file>" << std::endl;
    return 1;
    }

    parser::Scene sc;
    sc.loadFromXml(argv[1]);

    Camera c = sc.cameras[0];

    std::vector<Ray> rays;
    for (int i = 0; i < c.plane.width; i++) {
        for (int j = 0; j < c.plane.height; j++) {
            rays.push_back(c.generate_ray(i,j));
        }
    }

    for (const auto& ray : rays) {
        std::cout << "[(" << ray.e.x << "," << ray.e.y << "," << ray.e.z << ")" << '\n';
        std::cout << "(" << ray.d.x << "," << ray.d.y << "," << ray.d.z << ")]" << '\n' << '\n';
    }

    std::cout << rays.size() << std::endl;
    return 0;
}
