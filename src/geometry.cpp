#include "../include/geometry.h"


Vec3f::Vec3f(float x, float y, float z)
    :x{x}, y{y}, z{z}
{}

Vec3f::Vec3f(const Vec3f& rhs) {
    x = rhs.x;
    y = rhs.y;
    z = rhs.z;
}

Vec3f Vec3f::operator+=(const Vec3f& rhs) {
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    return *this;
}
Vec3f Vec3f::operator-=(const Vec3f& rhs) {
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;
    return *this;
}

// Dot product 
Vec3f Vec3f::operator*=(const Vec3f& rhs) {
    x *= rhs.x;
    y *= rhs.y;
    z *= rhs.z;
}

Vec3f operator+(Vec3f lhs, Vec3f rhs) {
    return lhs += rhs;
}

Vec3f operator-(Vec3f lhs, Vec3f rhs) {
    return lhs -= rhs;
}
Vec3f operator-(Vec3f v) {
    return {-v.x, -v.y, -v.z};
}

Vec3f operator*(Vec3f lhs, Vec3f rhs) {
    return lhs *= rhs;
}

Vec3f operator*(float t, Vec3f rhs) {
    rhs.x *= t;
    rhs.y *= t;
    rhs.z *= t;
    return rhs;
}

Vec3f Ray::operator()(int t) {
        Vec3f v = t * d;
        return { e.x + v.x, e.y + v.y, e.z + v.z} ;
}

Vec3f cross(Vec3f a, Vec3f b) {
    return {
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    };
}


