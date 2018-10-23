CC = g++
IDIR = include
SDIR = src
ODIR = build

CFLAGS = -Wall -std=c++11 -Werror -g -I$(IDIR)

LDFLAGS = -lm

OBJS = geometry.o camera.o parser.o tinyxml2.o ppm.o sphere.o triangle.o

INCLUDES = geometry.h parser.h surface.h light.h material.h ppm.h tinyxml2.h

.PHONY:	clean

TARGETS = main example


# The main ray tracer program
main:	$(patsubst %, $(ODIR)/%, $(OBJS) main.o)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

# The example program given in the student pack
example:	$(patsubst %, $(ODIR)/%, $(OBJS) example.o)
	$(CC) -o $@ $^ $(CFLAGS)


# Recipes for object files
$(ODIR)/main.o:	$(patsubst %, $(IDIR)/%, parser.h camera.h ppm.h)
	$(CC) -c -o $@ $(SDIR)/main.cpp $(CFLAGS)

$(ODIR)/ppm.o:	$(IDIR)/ppm.h
	$(CC) -c -o $@ $(SDIR)/ppm.cpp $(CFLAGS)

$(ODIR)/tinyxml2.o:	$(IDIR)/tinyxml2.h
	$(CC) -c -o $@ $(SDIR)/tinyxml2.cpp $(CFLAGS)

$(ODIR)/parser.o:	$(patsubst %, $(IDIR)/%, $(INCLUDES))
	$(CC) -c -o $@ $(SDIR)/parser.cpp $(CFLAGS)

$(ODIR)/geometry.o:	$(IDIR)/geometry.h
	$(CC) -c -o $@ $(SDIR)/geometry.cpp $(CFLAGS)

$(ODIR)/camera.o: $(IDIR)/camera.h $(IDIR)/geometry.h	
	$(CC) -c -o $@ $(SDIR)/camera.cpp $(CFLAGS)

$(ODIR)/example.o:	$(IDIR)/parser.h $(IDIR)/ppm.h
	$(CC) -c -o $@ $(SDIR)/example.cpp $(CFLAGS)

$(ODIR)/sphere.o:	 $(IDIR)/surface.h
	$(CC) -c -o $@ $(SDIR)/sphere.cpp $(CFLAGS)

$(ODIR)/triangle.o:	 $(IDIR)/surface.h
	$(CC) -c -o $@ $(SDIR)/triangle.cpp $(CFLAGS)

clean:
	@rm -f $(TARGETS) main $(ODIR)/*
