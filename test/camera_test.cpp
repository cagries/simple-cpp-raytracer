#include <iostream>

#include "gtest/gtest.h"

#include "camera.h"

TEST(GenerateRayTest, Random) {
    rt::Vec4f bounds{-1, 1, -1, 1};

    float dist = 1;
    int width = 1024;
    int height = 768;

    rt::ImagePlane image{bounds, width, height, "test", dist};

    rt::Vec3f pos{0,0,0};
    rt::Vec3f up{0,1,0};
    rt::Vec3f right{1,0,0};
    rt::Vec3f gaze = rt::cross(up, right);

    ASSERT_FLOAT_EQ(-1, gaze.z);

    rt::Camera c{pos, gaze, up, image};
    rt::Ray r;
    r.d = rt::Vec3f{-0.5 + (1.0f/1024), 0.5f - (1.0f/768), -1}.normalize();

    rt::Ray r2 = c.generate_ray(256, 575);
    float eps = 1e-4;

    EXPECT_NEAR(r.d.x, r2.d.x, eps);
    EXPECT_NEAR(r.d.y, r2.d.y, eps);
    EXPECT_NEAR(r.d.z, r2.d.z, eps);
}


TEST(GenerateRayTest, Middle) {
    rt::Vec4f bounds{-1, 1, -1, 1};

    float dist = 1;
    int width = 1024;
    int height = 768;

    rt::ImagePlane image{bounds, width, height, "test", dist};

    rt::Vec3f pos{0,0,0};
    rt::Vec3f up{0,1,0};
    rt::Vec3f right{1,0,0};
    rt::Vec3f gaze = rt::cross(up, right);

    ASSERT_FLOAT_EQ(-1, gaze.z);

    rt::Camera c{pos, gaze, up, image};
    rt::Ray r;
    r.d = rt::Vec3f{1.0f/1024, 1.0f/768, -1}.normalize();

    rt::Ray r2 = c.generate_ray(width / 2, height / 2);
    float eps = 1e-4;

    EXPECT_NEAR(r.d.x, r2.d.x, eps);
    EXPECT_NEAR(r.d.y, r2.d.y, eps);
    EXPECT_NEAR(r.d.z, r2.d.z, eps);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


