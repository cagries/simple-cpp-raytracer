# basic-cpp-raytracer

This is a basic, multi-threaded ray tracer written in C++14. Currently ambient light, diffuse shading, Blinn-Phong shading, hard shadows and light reflections can be simulated. Sphere, triangles and triangle meshes are supported. Although it has to be further developed, basic bonding volume hierarchy has been implemented. Code has been compiler specific optimized.

## Quick start

You need CMake (minimum version 3.2) to build the project. Head on to [cmake.org](https://cmake.org/download) to download it.

To build the project, run the following commands from the project root directory:

```
$ cd build
$ cmake ..
$ make 
```

This creates the `raytracer` executable inside the `bin` directory.

After choosing a scene file, you can run

```
$ cd ../bin/
$ ./raytracer <scene_file.xml>
```

to generate `image_name.ppm`, where the image name is the name defined in the scene file. 

An example set of scene files (in XML) can be found within the `scenes` folder. Scene files include: 

- MaxRecursionDepth for limiting the number of reflections a view ray does

- BackgroundColor to calculate the color when view ray doesn't hit a surface 

- ShadowRayEpsilon for shifting the contact point when a ray hits a surface so that the reflecting/newly generated ray would not hit the same object. 

Apart from that, scene files include one or more camera data, ambient light and point light parameters, materials and their associated materialID's, and finally scene geometry information which are sphere and triangle data and indexed triangle mesh data. 

## Testing

`simple-cpp-raytracer` uses the [Google Test](https://github.com/google/googletest/blob/master/) framework for testing. Setting the `RT_BUILD_TESTS` flag while using CMake will download it while configuring the build.

If you want to build the tests and execute them locally, run the following (from the project root directory):

```
$ cd build/
$ cmake -DRT_BUILD_TESTS=1 ../
$ make
$ make test
```

# Installation

To install the `raytracer` executable, `libRaytracer.a` static library and header files, run:

```
$ cd build/
$ cmake ../
$ make
$ sudo make install
```


The last step command assumes you are installing to a restricted directory. Assuming the default installation prefix of `/usr/local/` (which you can change using the `-DCMAKE_INSTALL_PREFIX=/your/target/directory/` option), the targets will be installed to:

* `raytracer` -> `/usr/local/bin/raytracer`

* `libRaytracer.a` -> `/usr/local/lib/raytracer/libRaytracer.a`

* Public header files -> inside `/usr/local/include/raytracer/`

