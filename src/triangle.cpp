#include "surface.h"

#include <cmath>


Triangle::Triangle(Material* m, Vec3f* v0, Vec3f* v1, Vec3f* v2)
    : Surface{m}, indices{v0, v1, v2}
{}

// TODO: implement this
bool Triangle::hit(Ray r, float dist_min, float dist_max, HitRecord rec) {
    return true;
}
