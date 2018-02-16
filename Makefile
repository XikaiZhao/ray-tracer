CC = g++ -std=c++11 -Ofast -march=native
CFLAGS  = -Wall
LIBS = -fopenmp

SOURCES = main.cpp raytracer.cpp scene.cpp sceneObj.cpp color.cpp viewPort.cpp point.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = raytracer

all: $(SOURCES) $(EXECUTABLE) 

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(LIBS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) -c $< $(LIBS) 

.PHONY:
clean:
	rm -rf *o raytracer 
