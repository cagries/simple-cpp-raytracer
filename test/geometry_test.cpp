#include <iostream>

#include "gtest/gtest.h"

#include "geometry.h"

TEST(ConstructorTest, Default) {
    rt::Vec3f vec;
    ASSERT_FLOAT_EQ(0.0f, vec.x);
    ASSERT_FLOAT_EQ(0.0f, vec.y);
    ASSERT_FLOAT_EQ(0.0f, vec.z);
}

TEST(ConstructorTest, Random) {
    rt::Vec3f vec{-14, -0.38f, 22.0 / 7};
    EXPECT_FLOAT_EQ(-14.0f, vec.x);
    EXPECT_FLOAT_EQ(-0.38f, vec.y);
    EXPECT_FLOAT_EQ(3.1428571f, vec.z);
}

TEST(NormalizeTest, Random) {
    rt::Vec3f vec{243, -12, 4233};
    EXPECT_FLOAT_EQ(1.0f, vec.normalize().norm());
}

TEST(NormTest, Random) {
    rt::Vec3f vec{3.0f, -4.0f, 0.0f};
    EXPECT_FLOAT_EQ(5.0f, vec.norm());
}

TEST(CrossTest, Trivial) {
    rt::Vec3f v1{1, 0, 0};
    rt::Vec3f v2{0, 1, 0};

    auto v3 = cross(v1, v2);
    auto v4 = cross(v2, v1);

    EXPECT_FLOAT_EQ(0, v3.x);
    EXPECT_FLOAT_EQ(0, v3.y);
    EXPECT_FLOAT_EQ(1, v3.z);

    EXPECT_FLOAT_EQ(0, v4.x);
    EXPECT_FLOAT_EQ(0, v4.y);
    EXPECT_FLOAT_EQ(-1, v4.z);
}

TEST(CrossTest, Random) {
    rt::Vec3f v1{24, -12, 59};
    rt::Vec3f v2{-7, 0, 2};

    auto v3 = cross(v1, v2);

    EXPECT_FLOAT_EQ(-24, v3.x);
    EXPECT_FLOAT_EQ(-461, v3.y);
    EXPECT_FLOAT_EQ(-84, v3.z);
}

TEST(ElementwiseMultTest, Random) {
    rt::Vec3f v1{-12.1246f, 0.02f, -0.0024f};
    rt::Vec3f v2{-12.1245f, 15.25f, 924.01f};

    auto v3 = v1.times(v2);

    EXPECT_NEAR(147.00471f, v3.x, 0.001f);
    EXPECT_NEAR(0.305f, v3.y, 0.001f);
    EXPECT_NEAR(-2.217624f, v3.z, 0.001f);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
