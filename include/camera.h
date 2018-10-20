#ifndef CAMERA_H
#define CAMERA_H

#include "geometry.h"
#include <string>
#include <vector>


class Camera {
public:
    Vec3f position;
    Vec3f gaze;
    Vec3f up;
    Vec4f near_plane;
    float near_distance;
    int image_width, image_height;
    std::string image_name;
    Vec3f right; // calculate this after initialization
    void calculate_right();


    std::vector<Ray> generate_rays();
};


#endif
