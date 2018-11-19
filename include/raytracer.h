#ifndef RAYTRACER_H
#define RAYTRACER_H

#include "camera.h"
#include "surface.h"
#include "light.h"
#include "parser.h"

#include <vector>
#include <cmath>
#include <algorithm>

namespace rt {

/**
 * @brief The ray tracer class.
 */
class RayTracer {
public:
    RayTracer() = default;

    void load_scene(const char* filename);
    
    void rayTrace(unsigned char *image, const Camera& camera) const;
    Vec3f calculateColor(Ray r, Vec3f positionColor, int recursionLevel) const;
    Vec3f calculateLights(HitRecord hr, Vec3f viewVector) const;
    Vec3f calculateEachLight(HitRecord hr, PointLight light, Vec3f viewVector) const;
    Vec3f clampColor(Vec3f) const;

    const std::vector<Camera>& get_cameras() const {
        return scene.cameras;
    }
    
private:
    Scene scene;
    void trace_helper(unsigned char *image, const Camera& camera,
            int begin, int end, int index) const;
};

} // namespace rt

#endif // raytracer.h
