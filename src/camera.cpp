#include "camera.h"
#include "geometry.h"

#include <vector>

void Camera::calculate_right()
{
    right = cross(gaze, up);
}

std::vector<Ray> Camera::generate_rays()
{
    std::vector<Ray> rays;
    for (int i = 0; i < image_width; i++) {
        for (int j = 0; j < image_height; j++) {
            double u = near_plane.x + (near_plane.y - near_plane.x) * (i + 0.5) / image_width;
            double v = near_plane.z + (near_plane.w - near_plane.z) * (i + 0.5) / image_height;

            Ray r;
            r.d = near_distance * gaze + u * up + v * right;
            r.e = position;
            rays.push_back(r);
        }
    }

    return rays;
}

