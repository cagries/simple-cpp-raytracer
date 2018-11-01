/**
 * \file geometry.h
 * @brief Contains declarations for simple geometric definitions.
 *
 */
#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <cmath>



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

    /**
     * @brief A constructor.
     *
     * @param x
     * @param y
     * @param z
     *
     */
    constexpr Vec3f(float x ={}, float y ={}, float z ={})
        :x{x}, y{y}, z{z}
    {}

    /**
     * @brief Copy constructor.
     *
     * @param rhs
     */
    constexpr Vec3f(const Vec3f& rhs)
        :x{rhs.x}, y{rhs.y}, z{rhs.z}
    {}

    
    /**
     * @brief Move constructor. No need to invalidate rhs!
     *
     * @param rhs
     */
    explicit constexpr Vec3f(Vec3f&& rhs)
        :x{rhs.x}, y{rhs.y}, z{rhs.z}
    {}


    /**
     * @brief Copy assignment operator.
     *
     * @param rhs   Copied vector
     *
     * @return      *this
     */
    constexpr Vec3f& operator=(const Vec3f& rhs) {
        x = rhs.x;
        y = rhs.y;
        z = rhs.z;
        return *this;
    }

    /**
     * @brief Move assignment operator.
     *
     * @param rhs   Moved vector
     *
     * @return *this
     */
    constexpr Vec3f& operator=(Vec3f&& rhs) {
        x = rhs.x;
        y = rhs.y;
        z = rhs.z;
        return *this;
    }

    /**
     * @brief Returns the norm.
     *
     * @return The norm (length) of this vector.
     */
    constexpr float norm() const {
        return std::sqrt(x*x + y*y + z*z);
    }

    /**
     * @brief Returns a unit vector from this vector.
     *
     * @return A unit vector in the same direction as this.
     */
    constexpr Vec3f normalize() {
        float n = std::sqrt(x*x + y*y + z*z);
        return {x / n, y / n, z / n};
    }
    
    constexpr Vec3f& operator+=(const Vec3f& rhs) {
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;
        return *this;
    }

    constexpr Vec3f& operator-=(const Vec3f& rhs) {
        x -= rhs.x;
        y -= rhs.y;
        z -= rhs.z;
        return *this;
    }

    /**
     * @brief Returns the element-wise multiplication of this vector with \a rhs.
     *
     * @param rhs   A vector.
     *
     * @return The element-wise product of the two vectors.
     */
    constexpr Vec3f times(const Vec3f& rhs) const {
        return {x * rhs.x, y * rhs.y, z * rhs.z};
    }
};

constexpr Vec3f operator+(Vec3f lhs, Vec3f rhs) {
    return lhs += rhs;
}

constexpr Vec3f operator-(Vec3f lhs, Vec3f rhs) {
    return lhs -= rhs;
}

constexpr Vec3f operator-(Vec3f v) {
    return {-v.x, -v.y, -v.z};
}


/**
 * @brief Returns the dot product of the two vectors.
 *
 * @param lhs A vector.
 * @param rhs Another vector.
 *
 * @return The dot product (lhs . rhs).
 */
constexpr float operator*(Vec3f lhs, Vec3f rhs) {
    return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}


/**
 * @brief Scalar multiplication
 *
 * @param t     A scalar value.
 * @param rhs   A vector.
 *
 * @return      The product t(rhs).
 */
constexpr Vec3f operator*(float t, Vec3f rhs) {
    return {t * rhs.x, t * rhs.y, t * rhs.z};
}

constexpr Vec3f operator/(Vec3f lhs, float divisor) {
    return {lhs.x / divisor, lhs.y / divisor, lhs.z / divisor};
}

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
    constexpr Vec3f operator()(float t) {
        Vec3f v = t * d;
        return {e.x + v.x,
                e.y + v.y,
                e.z + v.z};
    }
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
constexpr Vec3f cross(Vec3f a, Vec3f b) {
    return {
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    };
}
 

} // namespace rt

#endif // geometry.h
