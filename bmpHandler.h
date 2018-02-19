#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <vector>
#include "color.h"

using namespace std;

// helper function for saveBMP();
int outputInt(char buffer[], int index, int num, int arraySize) {
  if (index < 0 || index + 4 >= arraySize) {
    throw invalid_argument("Can't write int to buffer, buffer too small.");
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
  } catch(exception& e) {
    cerr << e.what() << endl;
    exit(1);
  }
}

int inputInt(ifstream& fis) {
  int num = 0;
  for (int i=0; i<4; i++) {
    num = num + (fis.get()<<8*i);
  }
  return num;
}

int inputInt_2bytes(ifstream& fis) {
  int num = 0;
  for (int i=0; i<2; i++) {
    num = num + (fis.get()<<8*i);
  }
  return num;
}

vector<vector<Color> > toColourArray(char contents[], int horiz, int vert, int channels) {
  int pad = 0; // bmp pads rows to multiples of 4
  if ((channels*horiz) % 4 != 0) pad = 4 - ((channels*horiz) % 4); 
  
  vector<vector<Color> > cols(vert);
  for (int y=vert-1; y>=0; y--) {
    cols[y].resize(horiz);
    for (int x=0; x<horiz; x++) {
      int index = (vert-y-1)*(channels*horiz+pad) + channels*x;
      int blue = (int)contents[index], 
          green = (int)contents[index+1],
          red = (int)contents[index+2]; 
          //alpha=(int)contents[index+channels];
      if (blue < 0) blue = blue + 256;
      if (green < 0) green = green + 256;
      if (red < 0) red = red + 256;
      //if (alpha < 0) alpha = alpha + 256;
      cols[y][x] = Color(red, green, blue);
    }
  }
  return cols;
}

vector<vector<Color> > readBMP(string filename) {
  try {
    ifstream fis(filename, ios::binary);
    fis.ignore(10);
    int offset = inputInt(fis);
    fis.ignore(4);
    int horiz = inputInt(fis), vert = inputInt(fis);
    fis.ignore(2);

    int bitsPerPixel = inputInt_2bytes(fis);
    int channels = bitsPerPixel/8;
    fis.ignore(offset - 30);
    int pad = 0; // bmp pads rows to multiples of 4
    if ((channels*horiz) % 4 != 0) pad = 4 - ((channels*horiz) % 4); 
    char* contents = new char[(channels*horiz+pad)*vert];
    fis.read(contents, (channels*horiz+pad)*vert);
    vector<vector<Color> > cols = toColourArray(contents, horiz, vert, channels);
    fis.close();
    return cols;
  } catch(exception& e) {
    cerr << e.what() << endl;
    exit(1);
  }
}
