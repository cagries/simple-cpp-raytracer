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


struct Triangle : Surface {

    Triangle(Material*, Vec3f*, Vec3f*, Vec3f*);

    bool hit(Ray r, HitRecord*);


    // Indices in counter-clockwise order 
    Vec3f *a, *b, *c;
    Vec3f normal;

    ~Triangle() = default;
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
    Material *material;
    std::vector<Triangle> faces;
};



#endif // surface.h
