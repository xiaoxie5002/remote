#include <iostream>
#include <vector>
#include<string>
#include "myObject.h"
#include "myOpengl.h"


using namespace std;

//*******************************************************//
//*********************    OBJECT   *********************//
//*******************************************************//
vector <point3fv> g_Object3fPoints;  // all 3d points 
vector <face3iv> g_Object3iFaces;    //all face
vector <point3fv> g_PartCone3ds;	// part cone point
vector <point3fv> g_PartCylinder3ds;    //part cylinder point
vector <point3fv> g_DevelopPartCylinder;	// transform part Cylinder, develop 3D to 2D 
vector <point3fv> g_PartTorus3ds;  // part torus
vector <point3fv> g_DevelopPartTorus;	// transform part Torus, develop 3D to 2D 
vector <point3fv> mouse3D2;  //window2, get mouse
vector <point3fv> mouse2D2; //window2
vector <point3fv> mouse3D5;  //window5, get mouse
vector <DATA> g_data;
vector <DATA> g_curvePoint;
//*******************************************************//
//*********************    OPENGL   *********************//
//*******************************************************//
point3fv GL_UI_View = {10.0f, 10.0f, 10.0f};
float GL_UI_ObjectPos[3] = { 0.0, 0.0, 0.0 };
float GL_UI_Scale = 0.02;   // object scale
float GL_UI_SphereRot[16] = { 1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1 };
float GL_UI_RoateX = 0.0;
float GL_UI_RoateY = 0.0;
int GL_UI_IsObjLoaded = 1;   // object load fail
int GL_UI_IsShowPointCloud = 1;   // show point cloud
int GL_UI_IsShowAxes = 1;  // show Axes
int GL_UI_IsShowLineAB = 0;  // show cone lineAB
//*******************************************************//

int winID[5]; // window id 
int main(int argc, char **argv)
{
	//****************************************//
	//***********   Load file      ***********//
	//****************************************//
	string fileName = "4_open.obj";
	loadObjectFile(fileName);


	//****************************************//
	//***********    openGL        ***********//
	//****************************************//

	GLUT_INITs(argc, argv);

	glutMainLoop();
	return 0;
}