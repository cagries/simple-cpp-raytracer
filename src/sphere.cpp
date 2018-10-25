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
        if (hr) {
            hr->m = material;
        }
        
        float divisor = ray.d * ray.d;
        if (t1 < t2) {
            if (0 < t1) {        // 0 < t1 < t2
                if (hr && hr->t > t1 / divisor) {
                hr->t = t1 / divisor;
                Vec3f pos = ray.e + hr->t * ray.d;
                hr->pos = pos;
                hr->normal = normal(pos);
                }
		return true;
            } else if (0 < t2) { // t1 < 0 < t2
                if (hr && hr->t > t2 / divisor) {
                hr->t = t2 / divisor;
                Vec3f pos = ray.e + hr->t * ray.d;
                hr->pos = pos;
                hr->normal = normal(pos);
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
                }
            return true;
            } else if (0 < t1) { // t2 < 0 < t1
                if (hr && hr->t > t1 / divisor) {
                hr->t = t1 / divisor;
                Vec3f pos = ray.e + hr->t * ray.d;
                hr->pos = pos;
                hr->normal = normal(pos);
                }
            return true;
            }
        }
    }

    return false;
}


Vec3f Sphere::normal(Vec3f p) {
    return (p - center).normalize();
}

