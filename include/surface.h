#ifndef SURFACE_H
#define SURFACE_H

#include "geometry.h"
#include <vector>

struct Surface {
    int material_id;
    virtual Vec3f normal() = 0;
};


struct Face {
    int v0_id, v1_id, v2_id;
};

struct Triangle : Surface {
    Face indices;

    Vec3f normal() {
        // TODO: do htis
        return {0, 0, 0};
    }
};

struct Sphere : Surface {
    int center_vertex_id;
    int radius;

    Vec3f normal() {
        // TODO: Do this also
        return {1,1,1};
    }
};


struct Mesh
{
    int material_id;
    std::vector<Face> faces;
};

#endif //surface.h

