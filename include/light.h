/**
 * \file light.h
 * @brief Declarations of Light structures.
 *
 */

#ifndef LIGHT_H
#define LIGHT_H

#include "geometry.h"


namespace rt {

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
};

} // namespace rt

#endif // light.h
