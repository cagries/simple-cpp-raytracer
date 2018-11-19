/**
 * \file parser.h
 * @brief Contains the Scene class and parsing functions.
 *
 */

#ifndef __HW1__PARSER__
#define __HW1__PARSER__

#include <string>
#include <vector>
#include <memory>

#include "geometry.h"
#include "camera.h"
#include "light.h"
#include "material.h"
#include "surface.h"


namespace rt {

/**
 * @brief The Scene class.
 */
struct Scene
{
public:

    void loadFromXml(const std::string& filepath);

    Vec3f background_color;
    float shadow_ray_epsilon;
    int max_recursion_depth;

    std::vector<Camera> cameras;
    Vec3f ambient_light;
    std::vector<PointLight> point_lights;
    std::vector<Material> materials;
    std::vector<Vec3f> vertex_data;
    std::vector<std::unique_ptr<Surface>> surfaces;
};

} // namespace rt
#endif

