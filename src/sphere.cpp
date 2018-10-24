#include "surface.h"

#include <cmath>


Sphere::Sphere(Material *material, Vec3f center, float radius)
    : Surface{material}, center{center}, radius{radius}
{}

bool Sphere::hit(Ray ray, HitRecord* hr)
{
    float discriminant = pow(ray.d * (ray.e - center), 2) - (ray.d * ray.d) * ((ray.e - center) * (ray.e - center) - radius * radius);

    if (discriminant > 0) {
        float t1 = (-ray.d) * (ray.e - center)  - std::sqrt(discriminant);
        float t2 = (-ray.d) * (ray.e - center)  + std::sqrt(discriminant);
        hr->s = this;

        
        float divisor = ray.d * ray.d;
        if (t1 < t2) {
            if (0 < t1) {        // 0 < t1 < t2
                hr->t = t1 / divisor;
                return true;
            } else if (0 < t2) { // t1 < 0 < t2
                hr->t = t2 / divisor;
                return true;
            }
        } else {
            if (0 < t2) {        // 0 < t2 < t1
                hr->t = t2 / divisor;
                return true;
            } else if (0 < t1) { // t2 < 0 < t1
                hr->t = t1 / divisor;
                return true;
            }
        }
    }

    return false;
}

// TODO
Vec3f normal() {
    return {0,0,0};
}

