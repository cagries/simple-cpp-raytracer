#ifndef SURFACE_H
#define SURFACE_H

#include "geometry.h"
#include "material.h"

#include <vector>
#include <limits>

/**
 * @brief A HitRecord stores information for a Surface hit by a Ray.
 */
struct HitRecord {
    float t;
    Material* m;  //! A pointer to a Material.
    Vec3f pos;    //! The point hit by the Ray.
    Vec3f normal; //! The surface normal for the Surface at \a pos.
    
    HitRecord() : t(std::numeric_limits<float>::max()) {}
};



/**
 * @brief The abstract Surface class for implementing objects.
 *
 * Objects in the scene file must derive from Surface and thus
 * implement the pure virtual hit function.
 */
struct Surface {
    Surface(Material *m) : material{m} {}

    /**
     * @brief Returns true if the given Ray intersects the Surface. If it does, fills out the given HitRecord pointer.
     *
     * @param ray   A Ray.
     * @param hr    A HitRecord pointer
     *
     * @return True if the ray hits the surface.
     */
    virtual bool hit(Ray ray, HitRecord* hr) = 0;
    
    virtual ~Surface() = default;

    Material *material;
};



/**
 * @brief A Surface made of three Vec3f points.
 *
 */
struct Triangle : Surface {

    /**
     * @brief Triangle constructor.
     * The three vertices of the triangles are provided in
     * counter-clockwise order, meaning that the surface
     * follows the right-hand rule.
     *
     * @param material  A pointer to the triangle's Material.
     * @param a     First vertex
     * @param b     Second vertex
     * @param c     Third vertex
     */
    Triangle(Material* material, Vec3f* a, Vec3f* b, Vec3f* c);

    
    bool hit(Ray r, HitRecord*);


    Vec3f *a, *b, *c; //! Indices in counter-clockwise order 

    Vec3f normal;     //! The surface normal of the Triangle, computed at initialization

};



/**
 * @brief The Sphere class.
 */
struct Sphere : Surface {

    /**
     * @brief Sphere constructor.
     *
     * @param material A pointer to the sphere's Material.
     * @param center   The sphere's center point.
     * @param radius   The sphere's radius.
     */
    Sphere(Material*, Vec3f, float);

    bool hit(Ray r, HitRecord*);

    Vec3f center;
    float radius;

    /**
     * @brief Returns the surface normal of the sphere at the point p.
     *
     * @param pos
     *
     * @return The surface normal.
     */
    Vec3f normal(Vec3f pos);
};



/**
 * @brief The Mesh class is a collection of Triangle objects.
 */
struct Mesh
{
    Material *material;
    std::vector<Triangle> faces;
};



#endif // surface.h
