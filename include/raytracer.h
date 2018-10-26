#ifndef RAYTRACER_H
#define RAYTRACER_H

#include "camera.h"
#include "surface.h"
#include "light.h"
#include "parser.h"

#include <vector>
#include <cmath>
#include <algorithm>


/**
 * @brief The ray tracer class.
 */
class RayTracer {
public:
    Scene scene;
    std::vector<std::vector<Vec3f>> images;
    
    void rayTrace(int cameraIndex);
    Vec3f calculateColor(Ray r, Vec3f positionColor, int recursionLevel);
    Vec3f calculateLights(HitRecord hr, Vec3f viewVector);
    Vec3f calculateEachLight(HitRecord hr, PointLight light, Vec3f viewVector);
    Vec3f clampColor(Vec3f);
};

#endif // raytracer.h
