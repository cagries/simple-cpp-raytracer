#ifndef __HW1__PARSER__
#define __HW1__PARSER__

#include <string>
#include <vector>

#include "../include/geometry.h"
#include "../include/camera.h"
#include "../include/light.h"
#include "../include/material.h"
#include "../include/surface.h"

namespace parser
{
    //Notice that all the structures are as simple as possible
    //so that you are not enforced to adopt any style or design.

    struct Scene
    {
        //Data
        Vec3f background_color;
        float shadow_ray_epsilon;
        int max_recursion_depth;
        std::vector<Camera> cameras;
        Vec3f ambient_light;
        std::vector<PointLight> point_lights;
        std::vector<Material> materials;
        std::vector<Vec3f> vertex_data;
        std::vector<Mesh> meshes;
        std::vector<Triangle> triangles;
        std::vector<Sphere> spheres;

        //Functions
        void loadFromXml(const std::string& filepath);
    };
};

#endif

