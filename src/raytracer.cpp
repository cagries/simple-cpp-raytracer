#include "raytracer.h"
#include "parser.h"

#include <iostream>
#include <thread>

namespace rt {


RayTracer::RayTracer(const char* filename) {
    scene.loadFromXml(filename);
}


void RayTracer::trace_helper(unsigned char *image, const Camera& c, int begin, int end, int index) const {
    int width = c.plane.width;
    int height = c.plane.height;
    for (int i = begin; i < end; i++) {
        for (int j = 0; j < width; j++) {
            // Get a normalized ray
            Ray viewRay = c.generate_ray(j,height-i-1);
            Vec3f pixelColor = clampColor(calculateColor(viewRay, scene.background_color, 0));
            image[index++] = pixelColor.x;
            image[index++] = pixelColor.y;
            image[index++] = pixelColor.z;
            image[index++] = 0xff;          // Pixels are opaque.
        }
    }
}
void RayTracer::rayTrace(unsigned char *image, const Camera& c) const {
    int width = c.plane.width;
    int height = c.plane.height;
    
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
    
    std::vector<std::thread> threads;

    constexpr int num_threads = 8;
    int leap = static_cast<int>(height / num_threads);
    int jump = static_cast<int>(4 * width * height / num_threads);

    // Call the threads
    for (int i = 0; i < num_threads; i++) {
        threads.push_back(
                std::thread{
                    [this, image, c, leap, jump, i] {
                        trace_helper(image, c, i * leap, (i+1) * leap, i * jump);
                    }});
    }

    // Open a final thread if height not divisible by num_threads
    if (height % num_threads) {
         threads.push_back(std::thread{
                    [this, image, c, leap, jump, height] {
                        trace_helper(image, c, leap * num_threads,
                                height, jump * num_threads);
                    }});
    }

    // Wait for all threads before quitting
    for (auto& thread : threads) {
        thread.join();
    }
}
 

Vec3f RayTracer::calculateColor(Ray viewRay, Vec3f positionColor ,int recursionLevel) const {
    if (recursionLevel <= scene.max_recursion_depth) {
        bool hitFlag = false;
        HitRecord hr;

        for (const auto& surface : scene.surfaces) {
            if (surface.get()->hit(viewRay, &hr)) {
                hitFlag = true;
            }
        }
        
        if (hitFlag) {
            
            if (hr.m->mirror.norm() > 0) {
                Vec3f reflectionVector = viewRay.d - 2.0f * (hr.normal * viewRay.d) * hr.normal;
                Ray reflectionRay;
                reflectionRay.d = reflectionVector.normalize();
                reflectionRay.e = hr.pos + scene.shadow_ray_epsilon * reflectionVector;
                
                positionColor += hr.m->mirror.times(calculateColor(reflectionRay, scene.background_color, recursionLevel + 1));
            }
            
            positionColor += calculateLights(hr, viewRay.d);
        }
    }
    return positionColor;
}

Vec3f RayTracer::calculateLights(HitRecord hr, Vec3f viewVector) const {
    
    Vec3f color = hr.m->ambient.times(scene.ambient_light);
    
    for (size_t i = 0; i < scene.point_lights.size(); i++) {
        color += calculateEachLight(hr, scene.point_lights[i], viewVector);
    }
   
    return color;
}

Vec3f RayTracer::calculateEachLight(HitRecord hr, PointLight light, Vec3f viewVector) const {
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
    HitRecord shadowRec;
    bool shadowHitFlag = false;
    for (const auto& surface : scene.surfaces) {
        if (surface.get()->hit(lightRay, &shadowRec)) {
            shadowHitFlag = false;
        }
    }
    
    if (shadowHitFlag && (shadowRec.pos - hr.pos).norm() < distance) {
        return color;
    }
    
    //Calculate Diffuse Shading
    color += (1 / (distance * distance)) * dot * (hr.m->diffuse.times(light.intensity));
    
    //Calculations of half vector.
    Vec3f h = (lightRay.d + -viewVector);
    h = h / h.norm();
    
    //Calculate Blinn-Phong Shader
    color +=  pow((std::max(0.0f, h * hr.normal)), hr.m->phong_exponent) *
        hr.m->specular.times(light.intensity) / (distance * distance);

    return color;
}

Vec3f RayTracer::clampColor(Vec3f color) const {
    if (color.x > 255) color.x = 255;
    if (color.y > 255) color.y = 255;
    if (color.z > 255) color.z = 255;
    return color;
}

} // namespace rt
