#include <iostream>
#include <vector>
#include <memory>

#include "gtest/gtest.h"

#include "surface.h"

/*
 * Assume a mesh structure of
 *
 *           __---* A
 *      D _--     /\
 *       *       /  \
 *      / \     /    \
 *     /   \   /      \
 *    /     \ /        \
 * E *-------*----------* C
 *           B
 *
 */
TEST(MeshBoxTest, Random) {

    rt::Vec3f a = {0.75, 1, -1};
    rt::Vec3f b = {0, 0, 0.0};
    rt::Vec3f c = {1.5, 0, 0.2};
    rt::Vec3f d = {-0.8, 1, -1.2};
    rt::Vec3f e = {-2, -0.1, 0.1};

    std::vector<rt::Triangle> vec;

    // First triangle
    rt::Triangle t1(nullptr, 
            &a,
            &b,
            &c);

    // Second triangle
    rt::Triangle t2(nullptr, 
            &d,
            &b,
            &a
    );

    // Third triangle
    rt::Triangle t3(nullptr, 
            &e,
            &b,
            &d
    );

    vec.push_back(t1);
    vec.push_back(t2);
    vec.push_back(t3);

    rt::Mesh m{nullptr, vec, rt::Vec3f{-2, -0.1, -1.2}, rt::Vec3f{1.5, 1.1, 0.2}};

    rt::Ray r{
        {0,0, -2}, // center
        (rt::Vec3f{-0.7, 0.4, 1}).normalize() // direction
    };

    rt::HitRecord hr;

    EXPECT_TRUE(m.hit(r, &hr));

    EXPECT_FLOAT_EQ(1.7315673, hr.t);
}


int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


