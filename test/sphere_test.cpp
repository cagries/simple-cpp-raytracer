#include <iostream>

#include "gtest/gtest.h"

#include "surface.h"

class SphereFixture : public ::testing::Test {
public:
    SphereFixture() : center{rt::Vec3f{15, 16, 14}},
        radius{5.02f},
        sp{nullptr, center, radius} {
    }

    void SetUp() {
    }

    void TearDown() {

    }

    ~SphereFixture() {

    }

    float epsilon = 1e-4;
    rt::Vec3f center;
    float radius;

    rt::Sphere sp;
};


// Test overall methods of a Sphere
TEST_F(SphereFixture, Test) {
    rt::Ray r{
        {0, 0, 0},  // center
        {1, 1, 1}   // direction
    };

    rt::HitRecord hr;

    EXPECT_TRUE(sp.hit(r, &hr));

    EXPECT_NEAR(12.219, hr.t, epsilon);

    EXPECT_EQ(1.0f, sp.normal(r(hr.t)).norm());

    EXPECT_FALSE(sp.hit({r.e, -r.d}, &hr));
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
