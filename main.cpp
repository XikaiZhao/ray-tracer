#define _USE_MATH_DEFINES
#include <cmath> 
#include <iostream>
#include "bmpHandler.h"
#include "light.h"
#include "viewPort.h"
#include "sceneObj.h"
#include "scene.h"
#include "raytracer.h"

using namespace std;

int main() {
  Point e(4,0,7);
  Point d(-3,0,-5.3);
  Point x_direc(0,1,0);
  int xPixels = 1920;
  int yPixels = 1080;
  ViewPort vp(e, d, x_direc, 2, xPixels*1.0/yPixels*2.0, 2.0, xPixels,yPixels);
//  cout << vp.pixelToRay(5,5).rayDirect() << endl;

  Scene scene;

  vector<Sphere> spheres(9);
  int r[3] = {255,0,255};
  int g[3] = {0,0,255};
  int b[3] = {0,255,0};
  double rad = .4;
  for (int i=0; i<9; i++) {
    double x = 1.7*cos(M_PI/2 + i*M_PI*2/9),
           y = 1.7*sin(M_PI/2 + i*M_PI*2/9);
    Point ct(x,y,0);
    Color c; c.init(r[i%3],g[i%3],b[i%3]);
    Sphere sp(ct, rad, c, .5,.2,.4,.4);
    spheres[i] = sp;
    scene.addObject(&spheres[i]);
  }

  Point ct2(-2,0,-10000);
  double radius2 = 10000;
  Color c2; c2.init(255,255,255);
  Sphere sp2(ct2, radius2, c2, .5,.0,.1,.4);
  scene.addObject(&sp2);
  
  Point ll(0,0,.3);
  Color cc; cc.init(255,255,255);
  SphericalLight light(ll,.3, cc);
  scene.addSphericalLight(&light);

  Triangle tri1(Point(-1,-1,0), Point(-1,1,0), Point(-1,0,1),
		Color(255,0,255));
  scene.addObject(&tri1);
//  Point ct(-2,1,1);
//  double radius = 1;
//  Color c; c.init(255,0,0);
//  Sphere sp1(ct, radius, c);
//  
//  Point ct3(-1,-1,1);
//  double radius3 = 1;
//  Color c3; c3.init(10,0,255);
//  Sphere sp3(ct3, radius3, c3);
//  
//  Point ct4(0,1,1);
//  double radius4 = 1;
//  Color c4; c4.init(250,255,0);
//  Sphere sp4(ct4, radius4, c4);
//  
//
  
//  Point ll2(-1,2,3);
//  Color cc2; cc2.init(200,200,255);
//  SphericalLight light2(ll2,0.2,cc2);

//  Scene scene;
//  scene.addObject(&sp1);
//  scene.addObject(&sp2);
//  scene.addObject(&sp3);
//  scene.addObject(&sp4);
//  scene.addSphericalLight(&light);
//  scene.addSphericalLight(&light2);

  Raytracer rt(scene,&vp);
  Color* col = rt.render();
  
  string filename = "test3.bmp";
  //string filename = "/mnt/c/Users/Ahmad/Dropbox/ray-tracer-master/test.bmp";
  saveBMP(filename, col, xPixels, yPixels);
  delete[] col;
  return 0;
}

void testBMP() {
  Color* colour = new Color[6];
  colour[0].init(255, 0, 0);
  colour[1].init(255, 0, 0);
  colour[2].init(0, 0, 255);
  colour[3].init(0, 255, 0);
  colour[4].init(0, 255, 0);
  colour[5].init(0, 255, 0);

  //string filepath = "/home/xikai/Dropbox/ray-tracer-master/test.bmp";
  string filepath = "/mnt/c/Users/Ahmad/Dropbox/ray-tracer-master/test.bmp";
  saveBMP(filepath, colour, 3, 2);
}
