#include <iostream>
#include "bmpHandler.h"
#include "light.h"
#include "viewPort.h"
#include "sceneObj.h"
#include "scene.h"
#include "raytracer.h"

using namespace std;

int main() {
  Point e(-7,0,6);
  Point d(3,0,-3.5);
  Point x_direc(0,-1,0);
  ViewPort vp(e, d, x_direc, 1, 8/6.*1., 1., 1600, 1200);
  cout << vp.pixelToRay(5,5).rayDirect() << endl;

  Point ct(-2,1,1);
  double radius = 1;
  Color c; c.init(255,0,0);
  Sphere sp1(ct, radius, c);
  
  Point ct3(-1,-1,1);
  double radius3 = 1;
  Color c3; c3.init(10,0,255);
  Sphere sp3(ct3, radius3, c3);
  
  Point ct4(0,1,1);
  double radius4 = 1;
  Color c4; c4.init(250,255,0);
  Sphere sp4(ct4, radius4, c4);
  

  Point ct2(-2,0,-10000);
  double radius2 = 10000;
  Color c2; c2.init(100,150,100);
  Sphere sp2(ct2, radius2, c2);
  
  Point ll(3,1,3);
  Color cc; cc.init(255,0,0);
  SphericalLight light(ll,.2, cc);
  
  Point ll2(-1,-3,3);
  Color cc2; cc2.init(255,0,0);
  SphericalLight light2(ll2,0.2,cc2);

  Scene scene;
  scene.addObject(&sp1);
  scene.addObject(&sp2);
  scene.addObject(&sp3);
  scene.addObject(&sp4);
  scene.addSphericalLight(light);
  scene.addSphericalLight(light2);

  Raytracer rt(scene,&vp);
  Color* col = rt.render();
  
  // string filepath = "/home/xikai/Dropbox/ray-tracer-master/test2.bmp";
  string filepath = "/mnt/c/Users/Ahmad/Dropbox/ray-tracer-master/test.bmp";
  saveBMP(filepath, col, 1600, 1200);
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
