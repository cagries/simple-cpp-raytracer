# RayTracer
This is a basic, single-threaded ray tracer written in C++. 

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
To generate additional documentation, run
```
$ make docs
```
from the top-level directory, and open `doc/html/index.html` in a browser.
