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
 * @brief Simple 3D vector class
 *
 * The Vec3f struct defines a three-dimensional point or vector inside R^{3}.
 */
struct Vec3f {
    float x;
    float y;
    float z;

    /**
     * @brief Addition of one vector to another vector.
     *
     * @param rhs Another vector
     *
     * @return The sum vector
     */
    constexpr Vec3f& operator+=(const Vec3f& rhs) {
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;
        return *this;
    }

    /**
     * @brief Subtraction of one vector from another
     *
     * @param rhs Another vector
     *
     * @return The difference vector
     */
    constexpr Vec3f& operator-=(const Vec3f& rhs) {
        x -= rhs.x;
        y -= rhs.y;
        z -= rhs.z;
        return *this;
    }

    /**
     * @brief Copy constructor
     *
     * @param rhs Copied vector
     */
    constexpr Vec3f(const Vec3f& rhs)
        :x{rhs.x}, y{rhs.y}, z{rhs.z}
    {}

    /**
     * @brief Move constructor
     *
     * @param rhs Moved vector
     */
    constexpr Vec3f(Vec3f&& rhs)
        :x{rhs.x}, y{rhs.y}, z{rhs.z}
    {}

    /**
     * @brief Copy assignment operator
     *
     * @param rhs Copied vector
     *
     * @return This vector
     */
    constexpr Vec3f& operator=(const Vec3f& rhs) {
        x = rhs.x;
        y = rhs.y;
        z = rhs.z;
        return *this;
    }

    /**
     * @brief Move assignment operator
     *
     * @param rhs Moved vector
     *
     * @return This vector
     */
    constexpr Vec3f& operator=(Vec3f&& rhs) {
        x = rhs.x;
        y = rhs.y;
        z = rhs.z;
        return *this;
    }

    
    /**
     * @brief Default constructor
     *
     */
    constexpr Vec3f() 
        :x{}, y{}, z{}
    {}

    /**
     * @brief Constructor
     *
     * @param x x coordinate
     * @param y y coordinate
     * @param z z coordinate
     *
     */
    constexpr Vec3f(float x, float y, float z)
        :x{x}, y{y}, z{z}
    {}


    /**
     * @brief Returns a unit vector from this vector.
     *
     * @return A unit vector in the same direction as this.
     */
    Vec3f normalize() const {
        float size = norm();
        return  {x / size, y / size, z / size};
    }
    
    /**
     * @brief Returns the norm.
     *
     * @return The norm (length) of this vector.
     *
     * @note std::sqrt() is not constexpr in the standard, so
     * this may fail.
     *
     */
    float norm() const {
        return std::sqrt(x*x + y*y + z*z);
    }


    /**
     * @brief Returns the element-wise multiplication of this vector with \a rhs.
     *
     * @param rhs   A vector.
     *
     * @return The element-wise product of the two vectors.
     */
    constexpr Vec3f times(const Vec3f& rhs) const {
        return {x*rhs.x, y*rhs.y, z*rhs.z};
    }
};

/**
 * @brief Adds two vectors.
 *
 * @param lhs A vector.
 * @param rhs Another vector.
 *
 * @return The sum vector.
 */
constexpr Vec3f operator+(Vec3f lhs, Vec3f rhs) {
    return lhs += rhs;
}

/**
 * @brief Subtracts two vectors.
 *
 * @param lhs A vector.
 * @param rhs Another vector.
 *
 * @return The difference vector.
 */
constexpr Vec3f operator-(Vec3f lhs, Vec3f rhs) {
    return lhs -= rhs;
}

/**
 * @brief Unary negation operator.
 *
 * @param v A vector
 *
 * @return -v
 */
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
    return lhs.x*rhs.x + lhs.y*rhs.y + lhs.z*rhs.z;
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

/**
 * @brief Scalar division
 *
 * @param lhs A vector.
 * @param divisor A scalar value
 *
 * @return lhs / divisor
 */
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
     * @brief Default constuctor
     *
     */
    constexpr Ray() = default;

    /**
     * @brief Constructor.
     *
     * @param e The origin point.
     * @param d The direction vector.
     *
     */
    constexpr Ray(Vec3f e, Vec3f d)
        :e{e}, d{d}
    {}

    /**
     * @brief Computes the ray's location given the parameter \a t.
     *
     * @param t     The parameter.
     *
     * @return The ray's calculated position.
     */
    constexpr Vec3f operator()(float t) const {
        return e + t * d; 
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
