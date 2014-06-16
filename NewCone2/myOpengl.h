#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <GL/glut.h>
#include <time.h>
#include "myObject.h"
using namespace std;
//*******************************************************//
//*********************    OBJECT   *********************//
//*******************************************************//
extern vector <point3fv> g_Object3fPoints;  // all 3d points 
extern vector <point3fv> g_PartCone3ds;      // part cone points
extern vector <point3fv> g_PartCylinder3ds;  // part cylinder points
extern vector <point3fv> g_DevelopPartCylinder;	// transform part Cylinder, develop 3D to 2D 
extern vector <DATA> g_data;
extern vector <DATA> g_curvePoint;

extern vector <point3fv> g_PartTorus3ds;  // part torus
extern vector <point3fv> g_DevelopPartTorus;	// transform part Torus, develop 3D to 2D 


extern point3fv GL_UI_View ;
extern float GL_UI_ObjectPos[3] ;
extern float GL_UI_Scale ;   // object scale
extern float GL_UI_SphereRot[16] ;
extern int GL_UI_IsShowPointCloud ;   // show point cloud
extern int GL_UI_IsShowAxes ;  // show Axes
extern int GL_UI_IsObjLoaded ;   // object load fail
extern int GL_UI_IsShowLineAB ;  // show cone lineAB

//////////////////////////////////////////////////////////////////////
void GLUT_INITs(int argc, char **argv);
void idle();
//window1
void GLUT_INIT(int num);
void MY_INIT();
void GLUT_CALL_FUNC();
void GLUT_SET_MENU();
void myGlutDisplay(void);
void myGlutReshape(int w, int h);
void myGlutMouse(int button, int state, int x, int y);
void myGlutMotion(int x, int y);
void myGlutKeyboard(unsigned char key, int x, int y);
void menu(int val);
void sub_menu_1(int val);
void sub_menu_2(int val);
//window2
void GLUT_INIT2(int num);
void MY_INIT2();
void GLUT_CALL_FUNC2();
void myGlutDisplay2(void);
void myGlutReshape2(int w, int h);
void myGlutMouse2(int button, int state, int x, int y);
void myGlutKeyboard2(unsigned char key, int x, int y);
void myGlutMotion2(int x, int y);
void myGlutSpecialkey2(int key, int x, int y);

//window3
void GLUT_INIT3(int num);
void MY_INIT3();
void GLUT_CALL_FUNC3();
void myGlutDisplay3(void);
void myGlutReshape3(int w, int h);
void myGlutMouse3(int button, int state, int x, int y);
void myGlutMotion3(int x, int y);
void myGlutKeyboard3(unsigned char key, int x, int y);

//window4
void GLUT_INIT4(int num);
void MY_INIT4();
void GLUT_CALL_FUNC4();
void myGlutDisplay4(void);
void myGlutReshape4(int w, int h);
void myGlutKeyboard4(unsigned char key, int x, int y);

//window5
void GLUT_INIT5(int num);
void MY_INIT5();
void GLUT_CALL_FUNC5();
void myGlutDisplay5(void);
void myGlutReshape5(int w, int h);
void myGlutMouse5(int button, int state, int x, int y);
void myGlutKeyboard5(unsigned char key, int x, int y);
void myGlutMotion5(int x, int y);
void myGlutSpecialkey5(int key, int x, int y);


void drawAxes(); // draw coordinate
void drawPointCloud(vector <point3fv> points); // draw point cloud
void drawPointCloudColor(vector <point3fv> points); // draw point cloud with Color
void drawPointCloudColorWindow4(vector <point3fv> points, float Radius, float radius); // draw point cloud with Color in window4
void drawRectancleXOY(int height, int width);  //
void drawRectancleYOZ(int height, int width);  //
void drawLineAB(vector <point3fv> vetex);	// draw a line in 3D
void screen2dToWorld3d(int x, int y);  // screen point by mouse, transfy 2d to 3d
void drawLine(point3fv A, point3fv B);	// draw a line in 3D
void drawCircle(float cx, float cy, float r, int num_segments) ;
point3fv screen2dToWorld3d2(int x, int y);  // screen point by mouse, transfy 2d to 3d


/////////////////////////////
void myPick(int button, int state, int xPosition, int yPosition);
// mouse motion function
void myMouseMove(int xPosition, int yPosition);
void reshape(int w, int h);
void init();
void myDisplay();
void display2DControlPolyline();
void display2DControlPoints();

void draw2dControlPoints(vector <point3fv> points);// control points
void draw2dControlLines(vector <point3fv> points);//lines of  control points