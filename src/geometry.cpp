#include "geometry.h"
#include <cmath>


namespace rt {

/*
 * constexpr Vec3f::Vec3f(float x, float y, float z)
    :x{x}, y{y}, z{z}
{}

constexpr Vec3f::Vec3f(const Vec3f& rhs) 
    :x{rhs.x}, y{rhs.y}, z{rhs.z}
{}

// No need to invalidate rhs
constexpr Vec3f::Vec3f(Vec3f&& rhs)
    :x{rhs.x}, y{rhs.y}, z{rhs.z}
{}
*/

/*
Vec3f& Vec3f::operator=(const Vec3f& rhs) {
    x = rhs.x;
    y = rhs.y;
    z = rhs.z;
    return *this;
}
*/

/*
Vec3f& Vec3f::operator+=(const Vec3f& rhs) {
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    return *this;
}

Vec3f& Vec3f::operator-=(const Vec3f& rhs) {
x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;
    return *this;
}

*/

/*
Vec3f operator+(Vec3f lhs, Vec3f rhs) {
    return lhs += rhs;
}

constexpr Vec3f operator-(Vec3f lhs, Vec3f rhs) {
    return lhs -= rhs;
}

constexpr Vec3f operator-(Vec3f v) {
    return {-v.x, -v.y, -v.z};
}


constexpr Vec3f operator*(float t, Vec3f rhs) {
    rhs.x *= t;
    rhs.y *= t;
    rhs.z *= t;
    return rhs;
}

constexpr float operator*(Vec3f lhs, Vec3f rhs) {
    return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}

constexpr Vec3f operator/(Vec3f lhs, float divisor) {
    return {lhs.x / divisor, lhs.y / divisor, lhs.z / divisor};
}

*/

/**
 * The ray equation.
 */
/*constexpr Vec3f Ray::operator()(float t) {
        Vec3f v = t * d;
        return {e.x + v.x, e.y + v.y, e.z + v.z};
}
*/

/**
 * Cross product of two three dimensional vectors.
 */
/*constexpr Vec3f cross(Vec3f a, Vec3f b) {
    return {
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    };
}
*/

/*
constexpr float Vec3f::norm() const {
    return std::sqrt(x * x + y * y + z * z);
}


// Returns a copy!
constexpr Vec3f Vec3f::normalize() {
    float size = std::sqrt(x * x + y * y + z * z);
    return {x / size, y / size, z / size};
}

constexpr Vec3f Vec3f::times(const Vec3f& rhs) const {
    return {x * rhs.x, y * rhs.y, z * rhs.z};
}
*/

} // namespace rt
