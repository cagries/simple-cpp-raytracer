#ifndef CAMERA_H
#define CAMERA_H

#include "geometry.h"
#include <string>
#include <vector>

namespace rt {

/**
 * @brief A rectangular plane of pixels.
 */
class ImagePlane {
public:
    Vec4f bounds;           //! The left, right, bottom and top boundaries
                            //! of the plane.

    int width, height;      //! Resolution of the plane.
    std::string image_name; //! The name of the image plane

    float distance;         //! Distance from the Camera


    /**
     * @brief Image plane constructor.
     *
     * @param Vec4f
     * @param int
     * @param int
     * @param std::string
     * @param float
     */
    ImagePlane(Vec4f, int, int, std::string, float);
};


/**
 * @brief The Camera class.
 */
class Camera {
public:
    
    /**
     * @brief       The Camera constructor.
     *
     * @param pos   Real world position of the camera.
     * @param gaze  The gaze vector 
     * @param up    The up vector
     * @param plane The camera's ImagePlane.
     */
    Camera(Vec3f pos, Vec3f gaze, Vec3f up, ImagePlane plane);

    /**
     * @brief Returns a Ray in the direction of the (i,j)th coordinate
     * of the Camera's ImagePlane.
     *
     * @param i
     * @param j
     *
     * @return The Ray passing through the camera and the (i,j)th pixel.
     */
    Ray generate_ray(int i, int j) const;

    Vec3f position, gaze, up;
    Vec3f right;                //! Calculated inside the Camera constructor.
    ImagePlane plane;
};

} // namespace rt

#endif // CAMERA_H
