#include "raytracer.h"
#include "parser.h"

void RayTracer::rayTrace(int cameraIndex) {
    int width = scene.cameras[cameraIndex].plane.width;
    int height = scene.cameras[cameraIndex].plane.height;
    
    std::vector<Vec3f> image(width * height, scene.background_color);
    
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            // TODO: Find out what's incorrect
            Ray viewRay = scene.cameras[cameraIndex].generate_ray(i,j);
            image[i * width + j] =
                calculateColor(viewRay, scene.background_color, 0);
        }
    }
    
    images.push_back(image);
}

Vec3f RayTracer::calculateColor(Ray viewRay, Vec3f positionColor ,int recursionLevel) {
    if (recursionLevel < scene.max_recursion_depth) {
        HitRecord hr;
        for (size_t i = 0; i < scene.triangles.size(); i++) {
            if (scene.triangles[i].hit(viewRay, &hr)) {

            }
        }
        for (size_t i = 0; i < scene.spheres.size(); i++) {
            if (scene.spheres[i].hit(viewRay, &hr)) {
                
            }
        }
        for (size_t i = 0; i < scene.meshes.size(); i++) {
            for (auto& triangle : scene.meshes[i].faces) {
                if (triangle.hit(viewRay, &hr)) {

                }
            }
        }
        
        //Still segFault
        if(hr.m == NULL) {
            return positionColor;
        }
        
        hr.pos = hr.pos + scene.shadow_ray_epsilon * hr.normal;
        positionColor += calculateLights(hr, viewRay.d);
        
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
    float distance = lightVector.norm();
    
    float dot = lightVector.normalize() * hr.normal;
    if (dot <= 0) {
        return color;
    }
    
    Ray lightRay;
    lightRay.e = hr.pos + scene.shadow_ray_epsilon * lightVector;
    lightRay.d = lightVector.normalize();
    
    //Shadows
/*    for (size_t i = 0; i < scene.spheres.size(); i++) {
        if (scene.spheres[i].hit(lightRay, nullptr)) {
            return color;
        }
    }
*/
    color += (1 / (distance * distance)) * dot * hr.m->diffuse.times(light.intensity);
    
    //Calculations of half vector.
    Vec3f h = (1 / (lightRay.d + viewVector).norm()) * (lightVector + viewVector);
    color += (1 / (distance * distance)) * pow((std::max(0.0f, h * hr.normal)), hr.m->phong_exponent) * hr.m->specular * light.intensity;
    
    return color;
}



