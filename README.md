# RayTracer
This is a basic, multi-threaded ray tracer written in C++. Ambient light, diffuse shading, Blinn-Phong shading, hard shadows and light reflections can be simulated. Sphere, triangles and triangle meshes are supported. Although it has to be further developed, basic bonding volume hierarchy has been implemented. Code has been compiler specific optimized.

## Quick start

To compile the `raytracer` executable, run
```
$ make
```
at the command line. After defining your own scene file, you can run

```
$ ./raytracer <scene_file.xml>
```
to generate `image_name.ppm`, where the image name is the name defined in the scene file.
