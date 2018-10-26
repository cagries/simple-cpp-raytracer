#include "raytracer.h"
#include "parser.h"
#include <iostream>

void RayTracer::rayTrace(int cameraIndex) {
    int width = scene.cameras[cameraIndex].plane.width;
    int height = scene.cameras[cameraIndex].plane.height;
    
    std::vector<Vec3f> image(width * height, scene.background_color);
    
/**
 * The book's image plane indexing is different from the slides.
 * Thus we have
 *
 *                            
 *            *-----------------------* <-- (n_x-1, n_y-1)
 *            |                       |
 *            |                       |
 *            |                       |
 *  (0,0) --> *-----------------------*
 *
 */
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            // Get a normalized ray
            Ray viewRay = scene.cameras[cameraIndex].generate_ray(j,height-i-1);
            image[i * width + j] =
                clampColor(calculateColor(viewRay, scene.background_color, 0));
        }
    }
    
    images.push_back(image);
}

Vec3f RayTracer::calculateColor(Ray viewRay, Vec3f positionColor ,int recursionLevel) {
    if (recursionLevel < scene.max_recursion_depth) {
        bool hitFlag = false;
        HitRecord hr;
        for (size_t i = 0; i < scene.triangles.size(); i++) {
            if (scene.triangles[i].hit(viewRay, &hr)) {
                hitFlag = true;
            }
        }
        for (size_t i = 0; i < scene.spheres.size(); i++) {
            if (scene.spheres[i].hit(viewRay, &hr)) {
                hitFlag = true;
            }
        }
        for (size_t i = 0; i < scene.meshes.size(); i++) {
            for (auto& triangle : scene.meshes[i].faces) {
                if (triangle.hit(viewRay, &hr)) {
                    hitFlag = true;
                }
            }
        }
        
        if (hitFlag) {
            positionColor += calculateLights(hr, viewRay.d);
        }
        //TODO: Reflection
    }
    
    return positionColor;
}

Vec3f RayTracer::calculateLights(HitRecord hr, Vec3f viewVector) {
    
    Vec3f color = hr.m->ambient.times(scene.ambient_light);
    
    for (size_t i = 0; i < scene.point_lights.size(); i++) {
        color += calculateEachLight(hr, scene.point_lights[i], viewVector);
    }
   
    return color;
 
}

Vec3f RayTracer::calculateEachLight(HitRecord hr, PointLight light, Vec3f viewVector) {
    Vec3f color = {0, 0, 0};
    Vec3f lightVector = light.position - hr.pos;
    
    Ray lightRay;
    lightRay.d = lightVector.normalize();
    lightRay.e = hr.pos + scene.shadow_ray_epsilon * lightRay.d;
    
    float distance = lightVector.norm();
    
    float dot = lightRay.d * hr.normal;
    if (dot <= 0) {
        return color;
    }

    
    //Shadows
/*    for (size_t i = 0; i < scene.spheres.size(); i++) {
        if (scene.spheres[i].hit(lightRay, nullptr)) {
            return color;
        }
    }
*/
    color += (1 / (distance * distance)) * dot * (hr.m->diffuse.times(light.intensity));
    
    //Calculations of half vector.
    Vec3f h = (lightVector + -viewVector);
    h = h / h.norm();
    color += (1 / (distance * distance)) * pow((std::max(0.0f, h * hr.normal)), hr.m->phong_exponent) * hr.m->specular.times(light.intensity);

    return color;
}

Vec3f RayTracer::clampColor(Vec3f color) {
    if (color.x > 255) color.x = 255;
    if (color.y > 255) color.y = 255;
    if (color.z > 255) color.z = 255;
    return color;
}



