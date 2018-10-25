#include "surface.h"

#include <cmath>

// Calculate the normal of the triangle
Triangle::Triangle(Material* m, Vec3f* a, Vec3f* b, Vec3f* c)
    : Surface{m}, a{a}, b{b}, c{c}
{
    normal = cross((*b - *a), (*c - *a));
}

bool Triangle::hit(Ray ray, HitRecord* rec) {
    
    Vec3f ab = *a - *b;
    Vec3f ac = *a - *c;

    // Intermediate products
    float ei_hf, gf_di, dh_eg;

    ei_hf = ac.y * ray.d.z - ray.d.y * ac.z;
    gf_di = ray.d.x * ac.z - ac.x * ray.d.z;
    dh_eg = ac.x * ray.d.y - ac.y * ray.d.x;

    float ak_jb, jc_al, bl_kc;
    float j,k,l;

    j = a->x - ray.e.x;
    k = a->y - ray.e.y;
    l = a->z - ray.e.z;

    ak_jb = ab.x * k - j * ab.y;
    jc_al = j * ab.z - ab.x * l;
    bl_kc = ab.y * l - k * ab.z;

    float M = ab.x * (ei_hf) + 
              ab.y * (gf_di) +
              ab.z * (dh_eg);

    float t = - (ac.z * ei_hf +
                 ac.y * jc_al +
                 ac.x * bl_kc) / M;

    // Check for intersection
    if (t < 0) {
        return false;
    } else {
        float gamma = (ray.d.z * ak_jb +
                       ray.d.y * jc_al +
                       ray.d.x * bl_kc) / M; 

        if (gamma < 0 || gamma > 1) {
            return false;
        } else {
            float beta = (j * ei_hf +
                          k * gf_di +
                          l * dh_eg) / M;
            if (beta < 0 || beta > 1 - gamma) {
                return false;
            } else {
                // Fill out hit record
                if (rec) {
                    rec->t = t;
                    rec->normal = normal;
                    rec->pos = ray(t);
                    rec->m = material;
                }
                return true;
            }
        }
    }

    return false;
}


