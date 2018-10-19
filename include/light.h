#ifndef LIGHT_H
#define LIGHT_H

#include "geometry.h"

struct Light {
    Vec3f intensity;
};



struct AmbientLight : Light {};

struct PointLight : Light {
    Vec3f position;
};

#endif // light.h
