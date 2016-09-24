
#include <iostream>
#include <fstream>
#include "color.h"
#include <string>
#include <stdexcept>

using namespace std;

// helper function for saveBMP();
int outputInt(char buffer[], int index, int num, int arraySize) {
  if (index < 0 || index + 4 >= arraySize) {
    throw std::invalid_argument("Can't write int to buffer, buffer too small.");
  }
  for (int i=0; i<4; i++) {
    buffer[index++] = (char) (num%256);
    num = num >> 8;
  }
  return index; // return new index
}

/**
 * Save a grid of Colors to a BMP file.
 * @param  colour The two dimensional grid of Colors as a one dimensional array.
 *                (x,y) in the grid is colour[y*width + x].
 *
 */
void saveBMP(string filename, Color colour[], int width, int height) {
  try {
    int bufferSize = 4*width*height + 54;
    char* buffer = new char[bufferSize];
    int index = 0;
    buffer[index++] = 'B';
    buffer[index++] = 'M';

    index = outputInt(buffer, index, 54+width*height, bufferSize);
    index = outputInt(buffer, index, 0, bufferSize);
    index = outputInt(buffer, index, 54, bufferSize); // offset
    index = outputInt(buffer, index, 40, bufferSize); // windows v3 format
    index = outputInt(buffer, index, width, bufferSize);
    index = outputInt(buffer, index, height, bufferSize);
    buffer[index++] = (char)1;
    buffer[index++] = (char)0;
    buffer[index++] = (char)32;
    buffer[index++] = (char)0;
    index = outputInt(buffer, index, 0, bufferSize);
    index = outputInt(buffer, index, width*height, bufferSize);
    index = outputInt(buffer, index, width, bufferSize);
    index = outputInt(buffer, index, height, bufferSize);
    for (int i=0; i<2; i++) index = outputInt(buffer, index, 0, bufferSize);
    for (int y=height-1; y>=0; y--) {
    	for (int x=0; x<width; x++) {
	  buffer[index++] = (char)colour[y*width + x].getBlue();
    	  buffer[index++] = (char)colour[y*width + x].getGreen();
    	  buffer[index++] = (char)colour[y*width + x].getRed();
    	  buffer[index++] = (char)colour[y*width + x].getAlpha();
    	}	
    }
    ofstream outputBuffer;
    outputBuffer.open(filename, ios::out|ios::binary);
    outputBuffer.write(buffer, bufferSize);
    outputBuffer.close();

    delete [] buffer;
  } catch(std::exception& e) {
    std::cerr << e.what() << std::endl;
    exit(1);
  }
}
