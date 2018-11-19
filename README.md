# simple-cpp-raytracer

This is a simple, MIT-licensed multi-threaded ray tracer written in C++14.

![An example](https://raw.githubusercontent.com/cagries/simple-cpp-raytracer/master/sample_scenes/sample_outputs/mirror_spheres.png)

## Requirements

`simple-cpp-raytracer` requires the CMake (version >= 3.0.2) build system. Head on to [cmake.org](https://cmake.org/download) to download it.

Additionally, the following libraries are downloaded and used while building the project:

* The [tinyxml2](https://github.com/leethomason/tinyxml2) library for parsing scene files.

* The [lodepng](https://github.com/lvandeve/lodepng) library for outputing PNG images.

* The header-only [cxxopts](https://github.com/jarro2783/cxxopts) library for parsing command line arguments.


# Quick Start

Download the repository and its submodules by running

```
$ git clone --recurse-submodules https://github.com/cagries/simple-cpp-raytracer.git
```


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

to generate output images for each camera defined in the given scene file.

An example set of scene files (in XML) can be found within the `scenes` directory. Currently, exporting to the PNG and PPM formats is possible. You can specify the output file name and extension with the `<ImageName></ImageName>` tag.

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

### Components

A minimal set of

* Cameras, image planes, 3-dimensional vectors

* Ambient lighting and point lights

* An extensible abstract `Surface` class, and basic derived `Sphere`, `Triangle` and `Mesh` classes.

* Shading models
    - Ambient shading
    - Diffuse shading
    - Blinn-Phong shading
    
* Shadows

* Reflective surfaces and ideal specular reflection

* Simple graphics data structures
    - Indexed triangle meshes
    - Basic bounding volume hierarchies

are provided by the base library. Feel free to extend it in any way that you desire.

## Contributing

Contributions are very welcome! Check out the issue tracker and open pull requests for your changes.
