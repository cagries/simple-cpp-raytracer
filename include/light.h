/**
 * \file light.h
 * @brief Declarations of Light structures.
 *
 */

#ifndef LIGHT_H
#define LIGHT_H

#include "geometry.h"

/**
 * @brief A base class for lights.
 */
struct Light {
    Vec3f intensity;
};



/**
 * @brief A global light.
 */
struct AmbientLight : Light {};

/**
 * @brief A light emanating from a single position.
 */
struct PointLight : Light {
    Vec3f position;

    /**
     * @brief   Returns a shadow ray from the light source to another point.
     *
     * @param x A point.
     *
     * @return  The product Ray.
     */
    Ray shadow_ray(Vec3f x);
};

#endif // light.h
