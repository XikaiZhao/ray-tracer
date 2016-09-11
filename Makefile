CC = g++ -std=c++11
CFLAGS  = -Wall

all: raytracer

raytracer: main.o viewPort.o point.o
	$(CC) $(CFLAGS) -o raytracer main.o viewPort.o point.o

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp	

viewPort.o: viewPort.cpp
	$(CC) $(CFLAGS) -c viewPort.cpp

point.o:point.cpp
	$(CC) $(CFLAGS) -c point.cpp 

.PHONY:
clean:
	rm -rf *o raytracer 
