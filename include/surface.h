#ifndef SURFACE_H
#define SURFACE_H

#include "geometry.h"
#include "material.h"

#include <vector>

class Surface;

struct HitRecord {
    float t;
    Surface* s;
};


struct Surface {
    Surface(Material *m) : material{m} {}

    virtual bool hit(Ray r, float dist_min, float dist_max, HitRecord rec) = 0;
    virtual ~Surface() = default;

    Material *material;
};


struct Face {
    Vec3f *v0, *v1, *v2;
};

struct Triangle : Surface {

    Triangle(Material*, Vec3f*, Vec3f*, Vec3f*);

    // TODO: Implement this afterwards
    bool hit(Ray r, float dist_min, float dist_max, HitRecord rec);

    ~Triangle() = default;

    Face indices;
};


struct Sphere : Surface {

    Sphere(Material*, Vec3f, float);
    bool hit(Ray r, float dist_min, float dist_max, HitRecord rec);
    ~Sphere() = default;

    Vec3f center;
    float radius;
};


struct Mesh
{
    int material_id;
    std::vector<Face> faces;
};



#endif // surface.h
