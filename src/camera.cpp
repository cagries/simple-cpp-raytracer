#include "camera.h"
#include "geometry.h"

#include <vector>
#include <string>

/**
 * ImagePlane constructor.
 */
ImagePlane::ImagePlane(Vec4f plane, int width, int height, std::string name, float distance)
    : lrtb{plane}, width{width}, height{height}, image_name{name}, distance{distance}
{}


/**
 * Constructor for camera.
 */
Camera::Camera(Vec3f pos, Vec3f gaze, Vec3f up, ImagePlane plane)
    : position{pos}, gaze{gaze}, up{up}, plane{plane}
{
    right = cross(gaze, up);
}

Ray Camera::generate_ray(int i, int j)
{
    double u = plane.lrtb.x + (plane.lrtb.y - plane.lrtb.x) * (i + 0.5) / plane.width;
    double v = plane.lrtb.z + (plane.lrtb.w - plane.lrtb.z) * (j + 0.5) / plane.height;

    Ray r;
    r.d = plane.distance * gaze + u * up + v * right;
    r.e = position;
    return r;
}

