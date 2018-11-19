#include "surface.h"

#include <cmath>

#include <iostream>

namespace rt {

Sphere::Sphere(Material *material, Vec3f center, float radius)
    : Surface{material}, center{center}, radius{radius}
{}



bool Sphere::hit(Ray ray, HitRecord* hr) const
{
    float discriminant = pow(ray.d * (ray.e - center), 2) - (ray.d * ray.d) * ((ray.e - center) * (ray.e - center) - radius * radius);

    if (discriminant >= 0) {
        float t1 = (-ray.d) * (ray.e - center)  - std::sqrt(discriminant);
        float t2 = (-ray.d) * (ray.e - center)  + std::sqrt(discriminant);
        
        float divisor = ray.d * ray.d;
        if (t1 < t2) {
            if (0 < t1) {        // 0 < t1 < t2
                if (hr && hr->t > t1 / divisor) {
                    hr->t = t1 / divisor;
                    Vec3f pos = ray.e + hr->t * ray.d;
                    hr->pos = pos;
                    hr->normal = normal(pos);
                    hr->m = material;
                }
                return true;
            } else if (0 < t2) { // t1 < 0 < t2
                if (hr && hr->t > t2 / divisor) {
                    hr->t = t2 / divisor;
                    Vec3f pos = ray.e + hr->t * ray.d;
                    hr->pos = pos;
                    hr->normal = normal(pos);
                    hr->m = material;
                }
                return true;
            }
        } else {
            if (0 < t2) {        // 0 < t2 < t1
                if (hr && hr->t > t2 / divisor) {
                    hr->t = t2 / divisor;
                    Vec3f pos = ray.e + hr->t * ray.d;
                    hr->pos = pos;
                    hr->normal = normal(pos);
                    hr->m = material;
                }
                return true;
            } else if (0 < t1) { // t2 < 0 < t1
                if (hr && hr->t > t1 / divisor) {
                    hr->t = t1 / divisor;
                    Vec3f pos = ray.e + hr->t * ray.d;
                    hr->pos = pos;
                    hr->normal = normal(pos);
                    hr->m = material;
                }
                return true;
            }
        }
    }

    return false;
}


Vec3f Sphere::normal(Vec3f p) const {
    return (p - center).normalize();
}

} // namespace rt
