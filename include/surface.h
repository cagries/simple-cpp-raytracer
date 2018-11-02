#ifndef SURFACE_H
#define SURFACE_H

#include "geometry.h"
#include "material.h"

#include <vector>
#include <limits>

namespace rt {

/**
 * @brief A HitRecord stores information for a Surface hit by a Ray.
 */
struct HitRecord {
    float t;
    Material* m;  //! A pointer to a Material.
    Vec3f pos;    //! The point hit by the Ray.
    Vec3f normal; //! The surface normal for the Surface at \a pos.
    
    constexpr HitRecord() : t{std::numeric_limits<float>::max()}, m{nullptr} {}
};



/**
 * @brief The abstract Surface class for implementing objects.
 *
 * Objects in the scene file must derive from Surface and thus
 * implement the pure virtual hit function.
 */
struct Surface {
    explicit Surface(Material *m) : material{m} {}

    /**
     * @brief Returns true if the given Ray intersects the Surface. If it does, fills out the given HitRecord pointer.
     *
     * @param ray   A Ray.
     * @param hr    A HitRecord pointer
     *
     * @return True if the ray hits the surface.
     */
    virtual bool hit(Ray ray, HitRecord* hr) const = 0;
    
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

    
    bool hit(Ray r, HitRecord*) const;


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

    bool hit(Ray r, HitRecord*) const;

    Vec3f center;
    float radius;

    /**
     * @brief Returns the surface normal of the sphere at the point p.
     *
     * @param pos
     *
     * @return The surface normal.
     */
    constexpr Vec3f normal(Vec3f pos) const {
        return (pos - center) / radius;
    }
};



/**
 * @brief The Mesh class is a collection of Triangle objects.
 */
struct Mesh : Surface
{
    std::vector<Triangle> faces;
    Vec3f BV_min, BV_max;
    
    Mesh(Material* m, std::vector<Triangle> faces, Vec3f bv_min, Vec3f bv_max);


    bool hit(Ray ray, HitRecord* hr) const;

    ~Mesh() = default;
};

} // namespace rt

#endif // surface.h
