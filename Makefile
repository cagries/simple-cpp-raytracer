CC = g++
IDIR = include
SDIR = src
ODIR = build

CFLAGS = -Wall -std=c++11 -Werror -g -I$(IDIR)
LDFLAGS = -lm

OBJS = geometry.o camera.o parser.o tinyxml2.o ppm.o sphere.o triangle.o light.o raytracer.o
INCLUDES = geometry.h parser.h surface.h light.h material.h ppm.h tinyxml2.h raytracer.h

DOXYGEN_CONFIG = Doxyfile
.PHONY:	clean docs all

TARGETS = main example tracer main_raytracer


main_raytracer:		$(patsubst %, $(ODIR)/%, $(OBJS) main_raytracer.o)
	$(CC) -o $@ $^ $(CFLAGS)

all: $(TARGETS)

# The main ray tracer program
main:	$(patsubst %, $(ODIR)/%, $(OBJS) main.o)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)
# The example program given in the student pack
example:	$(patsubst %, $(ODIR)/%, $(OBJS) example.o)
	$(CC) -o $@ $^ $(CFLAGS)

# Another example program
tracer:	$(patsubst %, $(ODIR)/%, $(OBJS) tracer.o)
	$(CC) -o $@ $^ $(CFLAGS)

# Recipes for object files
$(ODIR)/main.o:	$(patsubst %, $(IDIR)/%, parser.h camera.h ppm.h) $(SDIR)/main.cpp
	$(CC) -c -o $@ $(SDIR)/main.cpp $(CFLAGS)

$(ODIR)/tracer.o:	$(patsubst %, $(IDIR)/%, parser.h camera.h ppm.h) $(SDIR)/tracer.cpp
	$(CC) -c -o $@ $(SDIR)/tracer.cpp $(CFLAGS)

$(ODIR)/main_raytracer.o:	$(patsubst %, $(IDIR)/%, parser.h camera.h raytracer.h ppm.h) $(SDIR)/main_raytracer.cpp
	$(CC) -c -o $@ $(SDIR)/main_raytracer.cpp $(CFLAGS)

$(ODIR)/ppm.o:	$(IDIR)/ppm.h $(SDIR)/ppm.cpp
	$(CC) -c -o $@ $(SDIR)/ppm.cpp $(CFLAGS)

$(ODIR)/tinyxml2.o:	$(IDIR)/tinyxml2.h
	$(CC) -c -o $@ $(SDIR)/tinyxml2.cpp $(CFLAGS)

$(ODIR)/parser.o:	$(patsubst %, $(IDIR)/%, $(INCLUDES)) $(SDIR)/parser.cpp
	$(CC) -c -o $@ $(SDIR)/parser.cpp $(CFLAGS)

$(ODIR)/geometry.o:	$(IDIR)/geometry.h $(SDIR)/geometry.cpp
	$(CC) -c -o $@ $(SDIR)/geometry.cpp $(CFLAGS)

$(ODIR)/camera.o: $(IDIR)/camera.h $(IDIR)/geometry.h $(SDIR)/camera.cpp
	$(CC) -c -o $@ $(SDIR)/camera.cpp $(CFLAGS)

$(ODIR)/example.o:	$(IDIR)/parser.h $(IDIR)/ppm.h $(SDIR)/example.cpp
	$(CC) -c -o $@ $(SDIR)/example.cpp $(CFLAGS)

$(ODIR)/sphere.o:	 $(IDIR)/surface.h
	$(CC) -c -o $@ $(SDIR)/sphere.cpp $(CFLAGS)

$(ODIR)/triangle.o:	 $(IDIR)/surface.h
	$(CC) -c -o $@ $(SDIR)/triangle.cpp $(CFLAGS)

$(ODIR)/light.o:	 $(IDIR)/light.h $(IDIR)/geometry.h
	$(CC) -c -o $@ $(SDIR)/light.cpp $(CFLAGS)

$(ODIR)/raytracer.o:	 $(IDIR)/raytracer.h $(IDIR)/parser.h $(SDIR)/raytracer.cpp
	$(CC) -c -o $@ $(SDIR)/raytracer.cpp $(CFLAGS)


docs:
	doxygen doc/$(DOXYGEN_CONFIG)
clean:
	@rm -rf $(TARGETS) $(ODIR)/* doc/html/* doc/latex/*

