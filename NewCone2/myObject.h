#pragma once
#include <iostream>
#include<fstream>
#include<string>
#include <sstream>
#include <vector>
#include <math.h>
#define pai 3.1415927

using namespace std;

//*******************************************************//
//*************      ojbect struct    *******************//
//*******************************************************//
typedef struct
{
	float x;
	float y;
	float z;
}point3fv;
typedef struct
{
	int v1;
	int v2;
	int v3;
}face3iv;
typedef struct
{
	point3fv v;
	double alpha;
	float dis;
}DATA;
//*******************************************************//
//***************        ojbect       *******************//
//*******************************************************//
extern vector <point3fv> g_Object3fPoints;  // all 3d points 
extern vector <face3iv> g_Object3iFaces;    //all face
extern vector <point3fv> g_PartCone3ds;      // part cone points
extern vector <point3fv> g_PartCylinder3ds;  // part cylinder points
extern vector <point3fv> g_DevelopPartCylinder;	// transform part Cylinder, develop 3D to 2D 
extern vector <point3fv> g_PartTorus3ds;  // part torus
extern vector <point3fv> g_DevelopPartTorus;	// transform part Torus, develop 3D to 2D 
extern vector <DATA> g_data;
extern vector <DATA> g_curvePoint;

void loadObjectFile(string fileName);  // read object file
float getRadiusCylinder(point3fv A, point3fv B);  //calculate cylinder`s radius
void savePartCylinderPoint(point3fv A, point3fv B,float radius);  //  save Project Cylinder Point, not all
void transformCylinder3dTo2d(float radius, int angle); //transform cyinder 3d -> 2d

double sincosToAngle(double sinval, double cosval);
float distancePoint(point3fv first, point3fv last); // distance between two points
void savePartTorus(float Radius, float radius);   //save project torus, not all
void transformTorus3dTo2d(float Radius, float radius); //transform cyinder 3d -> 2d
point3fv crossProduct(point3fv begin, point3fv end);  // calculate cross product 
float dotProduct(point3fv vec1, point3fv vec2);      //calculate dot product
float lengthVector(point3fv vec);  // length of vectorq


/////////////////////////////////////////
//////////////for curve fitting////////
/////////////////////////////////////////
vector <DATA> seleceCurvePoint(int N, vector <DATA> v);
float disAllCurve(vector <DATA> v);




////////////////////////////////
int detectCone(point3fv start, point3fv end);    // detect a  upward cone or downward
vector <point3fv> saveProjectConePoint(point3fv start, point3fv end);  //  save Project Cone Point, not all
vector <point3fv> projectToCone(point3fv start, point3fv end, vector <point3fv> data);  //  project to Cone
point3fv getFootOfPerpendicular(const point3fv &pt, const point3fv &begin, const point3fv &end);  // get foot of perpendicular 
vector <point3fv> transformCone3dTo2d(point3fv start, point3fv end, vector <point3fv> data);// 3D -> 2D
double getAngleAxesX(point3fv p);   // with X axes
point3fv crossPoint(point3fv A, point3fv B);  // line  AB with Z axes cross in one point
