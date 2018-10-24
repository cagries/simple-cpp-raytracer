#ifndef SURFACE_H
#define SURFACE_H

#include "geometry.h"
#include "material.h"

#include <vector>

struct Surface;

struct HitRecord {
    float t;
    Material* m;
    Vec3f normal;
    Vec3f pos;
};


struct Surface {
    Surface(Material *m) : material{m} {}

    virtual bool hit(Ray, HitRecord*) = 0;

    virtual ~Surface() = default;

    Material *material;
};


struct Face {
    Vec3f *v0, *v1, *v2;
};

struct Triangle : Surface {

    Triangle(Material*, Vec3f*, Vec3f*, Vec3f*);

    // TODO: Implement this afterwards
    bool hit(Ray r, HitRecord*);

    ~Triangle() = default;

    Face indices;
};


struct Sphere : Surface {

    Sphere(Material*, Vec3f, float);
    bool hit(Ray r, HitRecord*);
    ~Sphere() = default;

    Vec3f center;
    float radius;

    float diff(Vec3f p);
    Vec3f normal(Vec3f pos);
};


struct Mesh
{
    int material_id;
    std::vector<Face> faces;
};



#endif // surface.h
