#pragma once

#include "camera.h"
#include "surface.h"

#include <vector>

class RayTracer {
public:
    parser::Scene scene;
    std::vector<std::vector<Vec3f>> images;
    
    void rayTrace(int cameraIndex);
    Vec3f calculateColor(Ray r, Vec3f positionColor, int recursionLevel);
    Vec3f calculateLights(HitRecord hr, Vec3f viewVector);
//    Vec3f calculateEachLight();
    
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
        for (int i = 0; i < scene.spheres.size(); i++) {
            HitRecord hr;
            if (scene.spheres[i].hit(r, &hr)) {
                hr.pos = hr.pos + scene.shadow_ray_epsilon * hr.normal;
                positionColor += calculateLights(hr, r.d);
                
                //TODO: Reflection
            }
        }
    }
    
    return positionColor;
}

Vec3f RayTracer::calculateLights(HitRecord hr, Vec3f viewVector) {
    return Vec3f {255, 255, 255};
}
