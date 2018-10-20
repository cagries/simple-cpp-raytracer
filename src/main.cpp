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
    c.calculate_right();

    std::vector<Ray> rays = c.generate_rays();

    for (const auto& ray : rays) {
        std::cout << "[(" << ray.e.x << "," << ray.e.y << "," << ray.e.z << ")" << '\n';
        std::cout << "(" << ray.d.x << "," << ray.d.y << "," << ray.d.z << ")]" << '\n' << '\n';
    }

    std::cout << rays.size() << std::endl;
    return 0;
}
