#include "../include/camera.h"
#include <iostream>
#include "../utils/parser.h"

int main(int argc, char** argv)
{
    parser::Scene sc;
    sc.loadFromXml(argv[1]);

    Camera c = sc.cameras[0];
    c.calculate_right();

    std::vector<Ray> rays = c.generate_rays();

    for (const auto& ray : rays) {
        std::cout << "[(" << ray.e.x << "," << ray.e.y << "," << ray.e.z << ")" << '\n';
        std::cout << "(" << ray.d.x << "," << ray.d.y << "," << ray.d.z << ")]" << '\n' << '\n';
    }

    std::cout << rays.size() << std::endl;
    return 0;
}
