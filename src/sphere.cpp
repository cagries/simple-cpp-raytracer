#include "surface.h"

#include <cmath>


Sphere::Sphere(Material *material, Vec3f center, float radius)
    : Surface{material}, center{center}, radius{radius}
{}

bool Sphere::hit(Ray ray, float dist_min, float dist_max, HitRecord hd)
{
    float discriminant = pow(ray.d * (ray.e - center), 2) - (ray.d * ray.d) * ((ray.e - center) * (ray.e - center) - radius * radius);
    if (discriminant <= 0) {
        return false;
    } else {
        float t1 = (-ray.d * (ray.e - center)  - std::sqrt(discriminant));
        float t2 = (-ray.d * (ray.e - center)  + std::sqrt(discriminant));

        if (t1 < t2) {
            if (dist_min <= t1 && t1 <= dist_max) {
                hd.t = t1;
                hd.s = this;
                return true;
            } else if (dist_min <= t2 && t2 <= dist_max) {
                hd.t = t2;
                hd.s = this;
                return true;
            }
        } else if (t2 < t1) {
            if (dist_min <= t2 && t2 <= dist_max) {
                hd.t = t2;
                hd.s = this;
                return true;
            } else if (dist_min <= t1 && t1 <= dist_max) {
                hd.t = t1;
                hd.s = this;
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
