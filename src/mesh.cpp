#include "surface.h"

namespace rt {

Mesh::Mesh(Material* m, std::vector<Triangle> faces, Vec3f bv_min, Vec3f bv_max)
    : Surface{m},  faces{faces}, BV_min(bv_min), BV_max(bv_max) {}

bool Mesh::hit(Ray ray, HitRecord* hr) const {
    // Check if we actually hit the mesh
    float a = 1 / ray.d.x;
    float b = 1 / ray.d.y;
    float c = 1 / ray.d.z;

    float t_xmin, t_xmax;
    float t_ymin, t_ymax;
    float t_zmin, t_zmax;

    // Calculate t_min, t_max
    if (a >= 0) {
        t_xmin = a * (BV_min.x - ray.e.x);
        t_xmax = a * (BV_max.x - ray.e.x);
    } else {
        t_xmin = a * (BV_max.x - ray.e.x);
        t_xmax = a * (BV_min.x - ray.e.x);
    }

    if (b >= 0) {
        t_ymin = b * (BV_min.y - ray.e.y);
        t_ymax = b * (BV_max.y - ray.e.y);
    } else {
        t_ymin = b * (BV_max.y - ray.e.y);
        t_ymax = b * (BV_min.y - ray.e.y);
    }

    if (c >= 0) {
        t_zmin = c * (BV_min.z - ray.e.z);
        t_zmax = c * (BV_max.z - ray.e.z);
    } else {
        t_zmin = c * (BV_max.z - ray.e.z);
        t_zmax = c * (BV_min.z - ray.e.z);
    }

    // Calculate t intersections
    float t_min = std::max(std::max(t_xmin, t_ymin), t_zmin);
    float t_max = std::min(std::min(t_xmax, t_ymax), t_zmax);

    // Terminate early if not hit
    if (t_min > t_max) {
        return false;
    }

    // Find the triangle which is hit by the ray.
    // If we can't find such a triangle, then return false
    
    bool hitFlag = false;

    for (const auto& face : faces) {
        if (face.hit(ray, hr)) {
            // We hit this triangle
            hitFlag = true;
        }
    }
    return hitFlag;
}

} // namespace rt
