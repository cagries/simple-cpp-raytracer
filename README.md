# RayTracer
This is a basic, multi-threaded ray tracer written in C++. Currently ambient light, diffuse shading, Blinn-Phong shading, hard shadows and light reflections can be simulated. Sphere, triangles and triangle meshes are supported. Although it has to be further developed, basic bonding volume hierarchy has been implemented. Code has been compiler specific optimized.

## Quick start

You need CMake (minimum version 3.2) to build the project. Head on to [cmake.org](https://cmake.org/download) to download it.

To build the project, run the following commands from the project root directory:

```
$ cd build
$ cmake ..
$ make 
$ cd ../bin
```

This creates the `raytracer` executable inside the `bin` directory and switches to the `bin` directory.

After choosing a scene file, you can run

```
$ ./raytracer <scene_file.xml>
```

to generate `image_name.ppm`, where the image name is the name defined in the scene file. 

An example set of scene files (in XML) can be found within the `scenes` folder. Scene files include: 

- MaxRecursionDepth for limiting the number of reflections a view ray does

- BackgroundColor to calculate the color when view ray doesn't hit a surface 

- ShadowRayEpsilon for shifting the contact point when a ray hits a surface so that the reflecting/newly generated ray would not hit the same object. 

Apart from that, scene files include one or more camera data, ambient light and point light parameters, materials and their associated materialID's, and finally scene geometry information which are sphere and triangle data and indexed triangle mesh data. 
