#ifndef RAYTRACER_H
#define RAYTRACER_H

#include "camera.h"
#include "surface.h"
#include "light.h"

#include <vector>
#include <cmath>
#include <algorithm>

class RayTracer {
public:
    parser::Scene scene;
    std::vector<std::vector<Vec3f>> images;
    
    void rayTrace(int cameraIndex);
    Vec3f calculateColor(Ray r, Vec3f positionColor, int recursionLevel);
    Vec3f calculateLights(HitRecord hr, Vec3f viewVector);
    Vec3f calculateEachLight(HitRecord hr, PointLight light, Vec3f viewVector);
};

void RayTracer::rayTrace(int cameraIndex) {
    int width = scene.cameras[cameraIndex].plane.width;
    int height = scene.cameras[cameraIndex].plane.height;
    
    std::vector<Vec3f> image(width * height, scene.background_color);
    
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            Ray r = scene.cameras[cameraIndex].generate_ray(i,j);
            image[i * width + j] =
                calculateColor(r, scene.background_color, 0);
        }
    }
    
    images.push_back(image);
}

Vec3f RayTracer::calculateColor(Ray r, Vec3f positionColor ,int recursionLevel) {
    if (recursionLevel < scene.max_recursion_depth) {
        HitRecord hr;
        for (size_t i = 0; i < scene.triangles.size(); i++) {
            if (scene.triangles[i].hit(r, &hr)) {
                hr.pos = hr.pos + scene.shadow_ray_epsilon * hr.normal;
                positionColor += calculateLights(hr, r.d);
                
                //TODO: Reflection
            }
        }
        for (size_t i = 0; i < scene.triangles.size(); i++) {
            if (scene.spheres[i].hit(r, &hr)) {
                hr.pos = hr.pos + scene.shadow_ray_epsilon * hr.normal;
                positionColor += calculateLights(hr, r.d);
                
                //TODO: Reflection
            }
        }
        for (size_t i = 0; i < scene.meshes.size(); i++) {
            for (auto& triangle : scene.meshes[i].faces) {
                if (triangle.hit(r, &hr)) {
                    hr.pos = hr.pos + scene.shadow_ray_epsilon * hr.normal;
                    positionColor += calculateLights(hr, r.d);
                }
            }
        }
    }
    
    return positionColor;
}

Vec3f RayTracer::calculateLights(HitRecord hr, Vec3f viewVector) {
    Vec3f color = hr.m->ambient.times(scene.ambient_light);
    
    for (int i = 0; i < scene.point_lights.size(); i++) {
        color += calculateEachLight(hr, scene.point_lights[i], viewVector);
    }
    
    return color;
}

Vec3f RayTracer::calculateEachLight(HitRecord hr, PointLight light, Vec3f viewVector) {
    Vec3f color = {0, 0, 0};
    
    Vec3f lightVector = light.position - hr.pos;
    float distance = lightVector.norm();
    
    float dot = lightVector.normalize() * hr.normal;
    if (dot <= 0) {
        return color;
    }
    
    Ray lightRay;
    lightRay.e = hr.pos + scene.shadow_ray_epsilon * lightVector;
    lightRay.d = lightVector;
    
    for (int i = 0; i < scene.spheres.size(); i++) {
        if (scene.spheres[i].hit(lightRay, nullptr)) {
            return color;
        }
    }
    
    color += (1 / (distance * distance)) * dot * hr.m->diffuse.times(light.intensity);
    
    //Calculations of half vector.
    Vec3f h = (1 / (lightVector + viewVector).norm()) * (lightVector + viewVector);
    color += pow((std::max(0.0f, h * hr.normal)), hr.m->phong_exponent) * hr.m->specular * light.intensity / (distance * distance);
    
    return color;
}

#endif // raytracer.h
