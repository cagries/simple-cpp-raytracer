#include "light.h"
#include "geometry.h"


Ray PointLight::shadow_ray(Vec3f x)
{
    Vec3f w_i = position - x;
    // To avoid self-intersection due to fp, offset
    // the origin by a small amount
    float eps = 1e-4;
    return Ray{(x + eps *w_i), w_i};
}
