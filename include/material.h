/**
 * \file material.h
 * @brief Contains the Material definition.
 *
 */

#ifndef MATERIAL_H
#define MATERIAL_H

    
/**
 * @brief The Material structure.
 */
struct Material
{
    Vec3f ambient;          //! The ambient coefficient
    Vec3f diffuse;          //! The diffuse coefficient
    Vec3f specular;         //! The specular coefficient
    Vec3f mirror;           //! The reflectance coefficient
    float phong_exponent;   //! The phong exponent
};


#endif
