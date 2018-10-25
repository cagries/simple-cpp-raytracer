#include "camera.h"
#include "geometry.h"

#include <vector>
#include <string>

/**
 * @brief ImagePlane constructor.
 *
 * @param plane     Vec4f containing {l, r, b, t} values
 * @param width     Plane width
 * @param height    Plane height
 * @param name      Name of the image plane
 * @param distance  Distance from camera position
 */
ImagePlane::ImagePlane(Vec4f plane, int width, int height, std::string name, float distance)
    : bounds{plane}, width{width}, height{height}, image_name{name}, distance{distance}
{}


/**
 * @brief Camera constructor.
 *
 * @param pos       Position of the camera
 * @param gaze      Gaze vector (gaze = -w)
 * @param up        Up vector
 * @param plane     The camera's ImagePlane
 */
Camera::Camera(Vec3f pos, Vec3f gaze, Vec3f up, ImagePlane plane)
    : position{pos}, gaze{gaze}, up{up}, plane{plane}
{
    right = cross(gaze, up);
}


/**
 * @brief   Generates a ray from the camera's origin along the direction of the
 *          pixel with position (i,j).
 *
 * @param i Right coordinate
 * @param j Up coordinate
 *
 * @return 
 */
Ray Camera::generate_ray(int i, int j)
{
    double u = plane.bounds.l + (plane.bounds.r - plane.bounds.l) * (i + 0.5) / plane.width;
    double v = plane.bounds.b + (plane.bounds.t - plane.bounds.b) * (j + 0.5) / plane.height;

    Ray r;
    r.d = (plane.distance * gaze + u * right + v * up).normalize();
    r.e = position;
    return r;
}

