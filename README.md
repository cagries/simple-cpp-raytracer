# RayTracer
This is a basic, multi-threaded ray tracer written in C++. Currently ambient light, diffuse shading, Blinn-Phong shading, hard shadows and light reflections can be simulated. Sphere, triangles and triangle meshes are supported. Although it has to be further developed, basic bonding volume hierarchy has been implemented. Code has been compiler specific optimized.

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

All scene_file.xml files can be found within /scenes folder. Scene files include: 

- MaxRecursionDepth for limiting the number of reflections a view ray does

- BackgroundColor to calculate the color when view ray doesn't hit a surface 

- ShadowRayEpsilon for shifting the contact point when a ray hits a surface so that the reflecting/newly generated ray would not hit the same object. 

Apart from that, scene files include one or more camera data, ambient light and point light parameters, materials and their associated materialID's, and finaly scene geometry information which are sphere and triangle data and indexed triangle mesh data. 
