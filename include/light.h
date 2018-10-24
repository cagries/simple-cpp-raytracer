#ifndef LIGHT_H
#define LIGHT_H

#include "geometry.h"

struct Light {
    Vec3f intensity;
};



struct AmbientLight : Light {};

struct PointLight : Light {
    Vec3f position;

    // Creates a shadow ray from the light source to a point
    Ray shadow_ray(Vec3f x);
};

#endif // light.h
