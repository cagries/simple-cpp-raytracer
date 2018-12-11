
#include <iostream>

#include "gtest/gtest.h"

#include "surface.h"

class TriangleFixture : public ::testing::Test {
public:
    TriangleFixture() : tri{nullptr,
        new rt::Vec3f{0, 0, 0},
        new rt::Vec3f{0, 10, 0},
        new rt::Vec3f{10, 0, 0}
    } {
    }

    void SetUp() {
    }

    void TearDown() {

    }

    ~TriangleFixture() {
        delete tri.a;
        delete tri.b;
        delete tri.c;
    }

    float epsilon = 1e-4;

    rt::Triangle tri;
};


// Test overall methods of a Triangle
TEST_F(TriangleFixture, Test) {

    rt::Ray r1{
        {0, 0, 0},  // center
        {1, 1, 1}   // direction
    };

    rt::HitRecord hr;

    EXPECT_FLOAT_EQ(tri.normal.x, 0);
    EXPECT_FLOAT_EQ(tri.normal.y, 0);
    EXPECT_FLOAT_EQ(tri.normal.z, -1);

    rt::Ray r2 {
        {3, 2, -4},
        {0, 0.6, 0.8}
    };
    EXPECT_TRUE(tri.hit(r2, &hr));

    EXPECT_FLOAT_EQ(5, hr.t);

    EXPECT_FALSE(tri.hit(r1, &hr));
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
