/**
 * \file geometry.h
 * @brief Contains declarations for simple geometric definitions.
 *
 */
#ifndef GEOMETRY_H
#define GEOMETRY_H


namespace rt {

/**
 * @brief 
 *
 * The Vec3f struct defines a three-dimensional point or vector inside R^{3}.
 */
struct Vec3f {
    float x;
    float y;
    float z;

    Vec3f& operator+=(const Vec3f& rhs);

    Vec3f& operator-=(const Vec3f& rhs);

    Vec3f(const Vec3f& rhs);

    Vec3f(Vec3f&& rhs);

    Vec3f& operator=(const Vec3f& rhs);

    Vec3f& operator=(Vec3f&& rhs);

    Vec3f(float x ={}, float y ={}, float z ={});


    /**
     * @brief Returns a unit vector from this vector.
     *
     * @return A unit vector in the same direction as this.
     */
    Vec3f normalize() const;
    
    /**
     * @brief Returns the norm.
     *
     * @return The norm (length) of this vector.
     */
    float norm() const;


    /**
     * @brief Returns the element-wise multiplication of this vector with \a rhs.
     *
     * @param rhs   A vector.
     *
     * @return The element-wise product of the two vectors.
     */
    Vec3f times(const Vec3f& rhs) const;
};

Vec3f operator+(Vec3f lhs, Vec3f rhs);

Vec3f operator-(Vec3f lhs, Vec3f rhs);

Vec3f operator-(Vec3f v);


/**
 * @brief Returns the dot product of the two vectors.
 *
 * @param lhs A vector.
 * @param rhs Another vector.
 *
 * @return The dot product (lhs . rhs).
 */
float operator*(Vec3f lhs, Vec3f rhs);


/**
 * @brief Scalar multiplication
 *
 * @param t     A scalar value.
 * @param rhs   A vector.
 *
 * @return      The product t(rhs).
 */
Vec3f operator*(float t, Vec3f rhs);

Vec3f operator/(Vec3f lhs, float divisor);

/**
 * @brief The Ray function object.
 *
 * A Ray represents a directional parametric line equation in R^{3}.
 */
struct Ray {
    Vec3f e;    //! The origin of the ray

    Vec3f d;    //! The direction of the ray

    /**
     * @brief Computes the ray's location given the parameter \a t.
     *
     * @param t     The parameter.
     *
     * @return The ray's calculated position.
     */
    Vec3f operator()(float t) const;
};


/**
 * @brief A vector of four components.
 */
struct Vec4f {
    float l;
    float r;
    float b;
    float t;
};

/**
 * @brief   Returns the cross product of this vector with \a rhs.
 *
 * @param   rhs Another vector
 *
 * @return  The cross product (this x rhs). 
 */
Vec3f cross(Vec3f a, Vec3f b); 
} // namespace rt 

#endif // geometry.h
