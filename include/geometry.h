#ifndef GEOMETRY_H
#define GEOMETRY_H


struct Vec3f {
    float x;
    float y;
    float z;

    Vec3f operator+=(const Vec3f& rhs);

    Vec3f operator-=(const Vec3f& rhs);

    // Dot product 
    Vec3f operator*=(const Vec3f& rhs);

    Vec3f(const Vec3f& rhs);
    Vec3f(float x =0, float y =0, float z =0);
};

Vec3f operator+(Vec3f lhs, Vec3f rhs);

Vec3f operator-(Vec3f lhs, Vec3f rhs);

Vec3f operator-(Vec3f v);

Vec3f operator*(Vec3f lhs, Vec3f rhs);

Vec3f operator*(float t, Vec3f rhs);


struct Ray {
    Vec3f e;
    Vec3f d;

    Vec3f operator()(int t);
};

struct Vec4f {
    float x;
    float y;
    float z;
    float w;
};

Vec3f cross(Vec3f a, Vec3f b);

#endif // geometry.h
