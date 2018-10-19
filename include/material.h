#ifndef MATERIAL_H
#define MATERIAL_H

    
struct Material
{
    Vec3f ambient;
    Vec3f diffuse;
    Vec3f specular;
    Vec3f mirror;
    float phong_exponent;
};


#endif
