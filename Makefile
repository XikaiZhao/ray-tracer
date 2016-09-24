CC = g++ -std=c++11
CFLAGS  = -Wall
LIBS = -fopenmp

all: raytracer

raytracer: main.o raytracer.o scene.o sceneObj.o color.o viewPort.o point.o
	$(CC) $(CFLAGS) $(LIBS) -O3 -o raytracer main.o raytracer.o scene.o sceneObj.o color.o viewPort.o point.o

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp $(LIBS)

raytracer.o: raytracer.cpp
	$(CC) $(CFLAGS) -c raytracer.cpp $(LIBS) 	

scene.o: scene.cpp
	$(CC) $(CFLAGS) -c scene.cpp $(LIBS)

sceneObj.o: sceneObj.cpp
	$(CC) $(CFLAGS) -c sceneObj.cpp $(LIBS)

color.o: color.cpp
	$(CC) $(CFLAGS) -c color.cpp $(LIBS)

viewPort.o: viewPort.cpp
	$(CC) $(CFLAGS) -c viewPort.cpp $(LIBS)

point.o: point.cpp
	$(CC) $(CFLAGS) -c point.cpp $(LIBS)

.PHONY:
clean:
	rm -rf *o raytracer 
