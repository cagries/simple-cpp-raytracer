#include "parser.h"
#include "tinyxml2.h"
#include "surface.h"

#include <sstream>
#include <stdexcept>
#include <iostream>
#include <vector>
#include <memory>

namespace rt {

void Scene::loadFromXml(const std::string& filepath)
{
    tinyxml2::XMLDocument file;
    std::stringstream stream;

    int material_id;

    auto res = file.LoadFile(filepath.c_str());
    if (res)
    {
        throw std::runtime_error("Error: The xml file cannot be loaded.");
    }

    auto root = file.FirstChild();
    if (!root)
    {
        throw std::runtime_error("Error: Root is not found.");
    }

    //Get BackgroundColor
    auto element = root->FirstChildElement("BackgroundColor");
    if (element)
    {
        stream << element->GetText() << std::endl;
    }
    else
    {
        stream << "0 0 0" << std::endl;
    }
    stream >> background_color.x >> background_color.y >> background_color.z;

    //Get ShadowRayEpsilon
    element = root->FirstChildElement("ShadowRayEpsilon");
    if (element)
    {
        stream << element->GetText() << std::endl;
    }
    else
    {
        stream << "0.001" << std::endl;
    }
    stream >> shadow_ray_epsilon;

    //Get MaxRecursionDepth
    element = root->FirstChildElement("MaxRecursionDepth");
    if (element)
    {
        stream << element->GetText() << std::endl;
    }
    else
    {
        stream << "0" << std::endl;
    }
    stream >> max_recursion_depth;

    //Get Cameras
    element = root->FirstChildElement("Cameras");
    element = element->FirstChildElement("Camera");

    Vec3f position, gaze, up;
    Vec4f near_plane;
    float distance;
    std::string name;
    int width, height;

    while (element)
    {
        auto child = element->FirstChildElement("Position");
        stream << child->GetText() << std::endl;
        child = element->FirstChildElement("Gaze");
        stream << child->GetText() << std::endl;
        child = element->FirstChildElement("Up");
        stream << child->GetText() << std::endl;
        child = element->FirstChildElement("NearPlane");
        stream << child->GetText() << std::endl;
        child = element->FirstChildElement("NearDistance");
        stream << child->GetText() << std::endl;
        child = element->FirstChildElement("ImageResolution");
        stream << child->GetText() << std::endl;
        child = element->FirstChildElement("ImageName");
        stream << child->GetText() << std::endl;

        stream >> position.x >> position.y >> position.z;
        stream >> gaze.x >> gaze.y >> gaze.z;
        stream >> up.x >> up.y >> up.z;
        stream >> near_plane.l >> near_plane.r >> near_plane.b >> near_plane.t;
        stream >> distance;
        stream >> width >> height;
        stream >> name;

        cameras.push_back({
                position, gaze, up, 
                {near_plane, width, height, name, distance} // image plane
                });
        element = element->NextSiblingElement("Camera");
    }

    //Get Lights
    element = root->FirstChildElement("Lights");
    auto child = element->FirstChildElement("AmbientLight");
    stream << child->GetText() << std::endl;
    stream >> ambient_light.x >> ambient_light.y >> ambient_light.z;
    element = element->FirstChildElement("PointLight");
    PointLight point_light;
    while (element)
    {
        child = element->FirstChildElement("Position");
        stream << child->GetText() << std::endl;
        child = element->FirstChildElement("Intensity");
        stream << child->GetText() << std::endl;

        stream >> point_light.position.x >> point_light.position.y >> point_light.position.z;
        stream >> point_light.intensity.x >> point_light.intensity.y >> point_light.intensity.z;

        point_lights.push_back(point_light);
        element = element->NextSiblingElement("PointLight");
    }

    //Get Materials
    element = root->FirstChildElement("Materials");
    element = element->FirstChildElement("Material");
    Material material;
    while (element)
    {
        child = element->FirstChildElement("AmbientReflectance");
        stream << child->GetText() << std::endl;
        child = element->FirstChildElement("DiffuseReflectance");
        stream << child->GetText() << std::endl;
        child = element->FirstChildElement("SpecularReflectance");
        stream << child->GetText() << std::endl;
        child = element->FirstChildElement("MirrorReflectance");
        stream << child->GetText() << std::endl;
        child = element->FirstChildElement("PhongExponent");
        stream << child->GetText() << std::endl;

        stream >> material.ambient.x >> material.ambient.y >> material.ambient.z;
        stream >> material.diffuse.x >> material.diffuse.y >> material.diffuse.z;
        stream >> material.specular.x >> material.specular.y >> material.specular.z;
        stream >> material.mirror.x >> material.mirror.y >> material.mirror.z;
        stream >> material.phong_exponent;

        materials.push_back(material);
        element = element->NextSiblingElement("Material");
    }

    //Get VertexData
    element = root->FirstChildElement("VertexData");
    stream << element->GetText() << std::endl;
    Vec3f vertex;
    while (!(stream >> vertex.x).eof())
    {
        stream >> vertex.y >> vertex.z;
        vertex_data.push_back(vertex);
    }
    stream.clear();

    //Get Meshes
    element = root->FirstChildElement("Objects");
    element = element->FirstChildElement("Mesh");

//    Mesh mesh;
    int v0_id, v1_id, v2_id;

    while (element)
    {
        child = element->FirstChildElement("Material");
        stream << child->GetText() << std::endl;
        stream >> material_id;
        Material* material = &materials[material_id - 1];

        child = element->FirstChildElement("Faces");
        stream << child->GetText() << std::endl;
        
        std::vector<Triangle> faces;
        
        // Use these to calculate bounding box edges.
        float x_min, y_min, z_min, x_max, y_max, z_max;
        x_min = y_min = z_min = std::numeric_limits<float>::max();
        x_max = y_max = z_max = std::numeric_limits<float>::min();
        
        while (!(stream >> v0_id).eof())
        {
            stream >> v1_id >> v2_id;
            
            Vec3f current_vertex = vertex_data[v0_id-1];
            
            //Calculate mins
            if (current_vertex.x < x_min)
                x_min = current_vertex.x;
            if (current_vertex.y < y_min)
                y_min = current_vertex.y;
            if (current_vertex.z < z_min)
                z_min = current_vertex.z;
            //calculate maxs
            if (current_vertex.x > x_max)
                x_max = current_vertex.x;
            if (current_vertex.y > y_max)
                y_max = current_vertex.y;
            if (current_vertex.z > z_max)
                z_max = current_vertex.z;
            
            current_vertex = vertex_data[v1_id-1];
            
            if (current_vertex.x < x_min)
                x_min = current_vertex.x;
            if (current_vertex.y < y_min)
                y_min = current_vertex.y;
            if (current_vertex.z < z_min)
                z_min = current_vertex.z;
            //calculate maxs
            if (current_vertex.x > x_max)
                x_max = current_vertex.x;
            if (current_vertex.y > y_max)
                y_max = current_vertex.y;
            if (current_vertex.z > z_max)
                z_max = current_vertex.z;
            
            current_vertex = vertex_data[v2_id-1];
            
            if (current_vertex.x < x_min)
                x_min = current_vertex.x;
            if (current_vertex.y < y_min)
                y_min = current_vertex.y;
            if (current_vertex.z < z_min)
                z_min = current_vertex.z;
            //calculate maxs
            if (current_vertex.x > x_max)
                x_max = current_vertex.x;
            if (current_vertex.y > y_max)
                y_max = current_vertex.y;
            if (current_vertex.z > z_max)
                z_max = current_vertex.z;
            
            faces.push_back({
                    material,
                    &vertex_data[v0_id-1],
                    &vertex_data[v1_id-1],
                    &vertex_data[v2_id-1]});
        }
        stream.clear();

        surfaces.emplace_back(std::make_unique<Mesh>(
                    Mesh(material, faces, {x_min, y_min, z_min}, {x_max, y_max, z_max})));

        element = element->NextSiblingElement("Mesh");
    }
    stream.clear();

    //Get Triangles
    element = root->FirstChildElement("Objects");
    element = element->FirstChildElement("Triangle");

    while (element)
    {
        child = element->FirstChildElement("Material");
        stream << child->GetText() << std::endl;
        stream >> material_id;


        child = element->FirstChildElement("Indices");
        stream << child->GetText() << std::endl;
        stream >> v0_id >> v1_id >> v2_id;

        surfaces.emplace_back(std::make_unique<Triangle>(
                    Triangle{&materials[material_id-1],
                    &vertex_data[v0_id-1], &vertex_data[v1_id-1], &vertex_data[v2_id-1]}));

        element = element->NextSiblingElement("Triangle");
    }

    //Get Spheres
    element = root->FirstChildElement("Objects");
    element = element->FirstChildElement("Sphere");

    int center_vertex_id;
    float radius;

    while (element)
    {
        child = element->FirstChildElement("Material");
        stream << child->GetText() << std::endl;

        stream >> material_id;

        child = element->FirstChildElement("Center");
        stream << child->GetText() << std::endl;

        stream >> center_vertex_id;

        child = element->FirstChildElement("Radius");
        stream << child->GetText() << std::endl;
        stream >> radius;

        surfaces.emplace_back(std::make_unique<Sphere>(
                    Sphere{&materials[material_id-1], vertex_data[center_vertex_id-1], radius}));
        element = element->NextSiblingElement("Sphere");
    }
}

} // namespace rt
