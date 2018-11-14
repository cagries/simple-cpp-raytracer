CC = g++
IDIR = include
SDIR = src
ODIR = build

CXXFLAGS = -Wall -std=c++14 -Werror -I$(IDIR) -O3
LDFLAGS = -lm -lpthread

OBJS = geometry.o camera.o parser.o tinyxml2.o ppm.o sphere.o triangle.o light.o raytracer.o mesh.o
INCLUDES = geometry.h parser.h surface.h light.h material.h ppm.h tinyxml2.h raytracer.h

DOXYGEN_CONFIG = Doxyfile
.PHONY:	clean docs all debug

TARGETS = raytracer example



raytracer:		$(patsubst %, $(ODIR)/%, $(OBJS) main_raytracer.o)
	$(CC) -o $@ $^ $(CXXFLAGS) $(LDFLAGS)

all: $(TARGETS)

# Recipes for object files
$(ODIR)/main.o:	$(patsubst %, $(IDIR)/%, parser.h camera.h ppm.h) $(SDIR)/main.cpp
	$(CC) -c -o $@ $(SDIR)/main.cpp $(CXXFLAGS)

$(ODIR)/tracer.o:	$(patsubst %, $(IDIR)/%, parser.h camera.h ppm.h) $(SDIR)/tracer.cpp
	$(CC) -c -o $@ $(SDIR)/tracer.cpp $(CXXFLAGS)

$(ODIR)/main_raytracer.o:	$(patsubst %, $(IDIR)/%, parser.h camera.h raytracer.h ppm.h) $(SDIR)/main_raytracer.cpp
	$(CC) -c -o $@ $(SDIR)/main_raytracer.cpp $(CXXFLAGS)

$(ODIR)/ppm.o:	$(IDIR)/ppm.h $(SDIR)/ppm.cpp
	$(CC) -c -o $@ $(SDIR)/ppm.cpp $(CXXFLAGS)

$(ODIR)/tinyxml2.o:	$(IDIR)/tinyxml2.h
	$(CC) -c -o $@ $(SDIR)/tinyxml2.cpp $(CXXFLAGS)

$(ODIR)/parser.o:	$(patsubst %, $(IDIR)/%, $(INCLUDES)) $(SDIR)/parser.cpp
	$(CC) -c -o $@ $(SDIR)/parser.cpp $(CXXFLAGS)

$(ODIR)/geometry.o:	$(IDIR)/geometry.h $(SDIR)/geometry.cpp
	$(CC) -c -o $@ $(SDIR)/geometry.cpp $(CXXFLAGS)

$(ODIR)/camera.o: $(IDIR)/camera.h $(IDIR)/geometry.h $(SDIR)/camera.cpp
	$(CC) -c -o $@ $(SDIR)/camera.cpp $(CXXFLAGS)

$(ODIR)/example.o:	$(IDIR)/parser.h $(IDIR)/ppm.h $(SDIR)/example.cpp
	$(CC) -c -o $@ $(SDIR)/example.cpp $(CXXFLAGS)

$(ODIR)/sphere.o:	 $(IDIR)/surface.h
	$(CC) -c -o $@ $(SDIR)/sphere.cpp $(CXXFLAGS)

$(ODIR)/triangle.o:	 $(IDIR)/surface.h
	$(CC) -c -o $@ $(SDIR)/triangle.cpp $(CXXFLAGS)

$(ODIR)/light.o:	 $(IDIR)/light.h $(IDIR)/geometry.h
	$(CC) -c -o $@ $(SDIR)/light.cpp $(CXXFLAGS)

$(ODIR)/mesh.o:	 $(IDIR)/surface.h $(SDIR)/mesh.cpp
	$(CC) -c -o $@ $(SDIR)/mesh.cpp $(CXXFLAGS)

$(ODIR)/raytracer.o:	 $(IDIR)/raytracer.h $(IDIR)/parser.h $(SDIR)/raytracer.cpp
	$(CC) -c -o $@ $(SDIR)/raytracer.cpp $(CXXFLAGS)


docs:
	@echo "Generating documentation..."
	doxygen doc/$(DOXYGEN_CONFIG)
clean:
	@rm -rf $(TARGETS) $(ODIR)/* doc/html/* doc/latex/*

