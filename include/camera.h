#ifndef CAMERA_H
#define CAMERA_H

#include "geometry.h"
#include <string>
#include <vector>

class ImagePlane {
public:
    Vec4f bounds;
    int width, height;
    std::string image_name;
    float distance;

    ImagePlane(Vec4f, int, int, std::string, float);
};

class Camera {
public:
    Camera(Vec3f pos, Vec3f gaze, Vec3f up, ImagePlane plane);
    Ray generate_ray(int i, int j);

    Vec3f position, gaze, up; // Provided as input
    Vec3f right; // Calculated using other variables, inside the constructor
    ImagePlane plane;
};


#endif // CAMERA_H
