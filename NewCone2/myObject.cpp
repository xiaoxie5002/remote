#include "myObject.h"
#define M_PI 3.1415926

float getRadiusCylinder(point3fv A, point3fv B)  //calculate cylinder`s radius
{
	float radius = 0.0;
	float tempA = 0.0;
	float tempB = 0.0;
	tempA = A.x*A.x + A.y*A.y;
	tempB = B.x*B.x + B.y*B.y;
	if(tempA > tempB)
		radius = sqrt(tempA);
	else
		radius = sqrt(tempB);
	return radius;
}
void savePartCylinderPoint(point3fv A, point3fv B,float radius)  //  save Project Cylinder Point, not all
{
	point3fv partCylinder;
	point3fv temp;
	unsigned int j = 0;
	for(unsigned int i = 0; i < g_Object3fPoints.size(); i++)
	{
		if((g_Object3fPoints[i].z >= B.z) && (g_Object3fPoints[i].z <= A.z))
		{
			partCylinder.x = g_Object3fPoints[i].x;
			partCylinder.y = g_Object3fPoints[i].y;
			partCylinder.z = g_Object3fPoints[i].z;

			temp.x = partCylinder.x/sqrt(partCylinder.x*partCylinder.x + partCylinder.y*partCylinder.y);
			temp.y = partCylinder.y/sqrt(partCylinder.x*partCylinder.x + partCylinder.y*partCylinder.y);
			temp.z = partCylinder.z;

			partCylinder.x = radius*temp.x;
			partCylinder.y = radius*temp.y;
			partCylinder.z = temp.z;
			g_PartCylinder3ds.push_back(partCylinder);
		}
	}
}
void transformCylinder3dTo2d(float radius, int angle)  //transform cyinder 3d -> 2d
{
	float length = 0.0;
	double alpha = 0.0;
	double beta = 0.0;
	double sinval = 0.0;
	double cosval = 0.0;
	point3fv tempA, tempB;
	length = 2*(float)pai*radius;  
	//cout<<"angle = "<<angle<<endl;
	for(unsigned int i = 0; i < g_PartCylinder3ds.size(); i++)
	{
		sinval = g_PartCylinder3ds[i].x/sqrt(g_PartCylinder3ds[i].x*g_PartCylinder3ds[i].x + g_PartCylinder3ds[i].y*g_PartCylinder3ds[i].y); // sin(alpha)
		cosval = g_PartCylinder3ds[i].y/sqrt(g_PartCylinder3ds[i].x*g_PartCylinder3ds[i].x + g_PartCylinder3ds[i].y*g_PartCylinder3ds[i].y); // cos(alpha)
		alpha = sincosToAngle(sinval, cosval);
		beta = angle/pai + alpha;
		tempA.x = 0.0;
		//tempA.x = radius - sqrt(g_PartCylinder3ds[i].x*g_PartCylinder3ds[i].x + g_PartCylinder3ds[i].y*g_PartCylinder3ds[i].y);
		if(alpha <= pai)
			tempA.y = (float)(alpha/(2*pai)*length);
		else
			tempA.y = (float)(-length + alpha/(2*pai)*length);
		tempA.z = g_PartCylinder3ds[i].z;

		if(beta <= pai)
			tempB.y = (float)(beta/(2*pai)*length);
		else
			tempB.y = (float)(-length + beta/(2*pai)*length);
		tempB.x = 0;
		tempB.y = tempB.y - tempA.y;
		tempB.z = tempA.z;
		if(angle == 0)
			g_DevelopPartCylinder.push_back(tempA);
		else
			g_DevelopPartCylinder.push_back(tempB);
	}
}


void  loadObjectFile(string fileName) // load data file
{
	string objName;
	objName.append(fileName);

	fstream foutVert;
	foutVert.clear();
	foutVert.open(fileName, fstream::in);

	/*************define vertex***********************/
	string getVertex;
	point3fv tmpVertex;
	tmpVertex.x = 0;
	tmpVertex.y = 0;
	tmpVertex.z = 0;
	/******************define face******************************/
	string getFace;
	face3iv tmpFace;
	tmpFace.v1 = 0;
	tmpFace.v2 = 0;
	tmpFace.v3 = 0;
	/******************define DATA******************************/
	DATA tempData;
	point3fv po;
	po.x = po.y = po.z = 0.0;
	double sinval ,cosval;
	/**************************read data vertex and face******************************/
	string lineInfo;
	while(!foutVert.eof())
	{
		getline(foutVert, lineInfo);
		if(!lineInfo.empty())
		{
			if(lineInfo[0] == 'v')
			{
				stringstream vLineInfo(stringstream::in | stringstream::out);
				vLineInfo<<lineInfo;
				vLineInfo>>getVertex>>tmpVertex.x >>tmpVertex.y >>tmpVertex.z;
				tmpVertex.x = tmpVertex.x- 5;
				g_Object3fPoints.push_back(tmpVertex);

				//init DATA
				tempData.v= tmpVertex;
				tempData.v.z = 0.0;   // make XOY plane
				tempData.dis = distancePoint(po,tmpVertex);  //distance in XOY plane
				sinval = tmpVertex.y/tempData.dis;
				cosval = tmpVertex.x/tempData.dis;
				tempData.alpha = sincosToAngle(sinval, cosval);
				//tempData.v.z = tmpVertex.z;
				
				g_data.push_back(tempData);
			}
			if(lineInfo[0] == 'f')
			{
				stringstream fLineInfo(stringstream::in | stringstream::out);
				fLineInfo<<lineInfo;
				fLineInfo>>getFace>>tmpFace.v1 >>tmpFace.v2  >>tmpFace.v3 ;
				g_Object3iFaces.push_back(tmpFace);
			}
		}
		else
		{
			break;
		}
	}
	foutVert.close();
	//cout<<"g_Object3fPoints.size() = "<<g_Object3fPoints.size()<<endl;
	//cout<<"g_Object3iFaces.size() = "<< g_Object3iFaces.size() <<endl;
}
void savePartTorus(float Radius, float radius)   //save project torus, not all
{
	point3fv origin = {0.0, 0.0, 0.0};
	point3fv temp;
	for(unsigned int i = 0; i < g_Object3fPoints.size(); i++)
	{
		float dist = distancePoint(origin, g_Object3fPoints[i]);
		if(dist >= (Radius - radius) && dist <= (Radius + radius))
		{
			temp.x = g_Object3fPoints[i].x;
			temp.y = g_Object3fPoints[i].y;
			temp.z = g_Object3fPoints[i].z;

			// vector M
			float cosU = temp.x/sqrt(temp.x*temp.x + temp.y*temp.y);
			float sinU = temp.y/sqrt(temp.x*temp.x + temp.y*temp.y);
			point3fv vecOM = {Radius*cosU, Radius*sinU, 0.0};

			float dist = distancePoint(temp, vecOM);  // distance point P between M
			point3fv vecMP = {radius*(temp.x - vecOM.x)/dist, radius*(temp.y - vecOM.y)/dist, radius*(temp.z - vecOM.z)/dist};

			point3fv vecOP = {vecOM.x + vecMP.x, vecOM.y + vecMP.y, vecOM.z + vecMP.z};
			//g_PartTorus3ds.push_back(g_Object3fPoints[i]); // delete useless point
			g_PartTorus3ds.push_back(vecOP);

		}
	}
}
// sinとcosの値から角度を求める
double sincosToAngle(double sinval, double cosval)
{
    double asinval = asin(sinval);
    double acosval = acos(cosval);
    if(asinval > 0.0) return acosval;
    else return 2*pai - acosval;
}
float distancePoint(point3fv first,point3fv last) // distance between two points
{
	float dx = first.x - last.x;
	float dy = first.y - last.y;
	float dz = first.z - last.z;
	float dist = sqrt(dx*dx + dy*dy + dz*dz);
	return dist;
}
void transformTorus3dTo2d(float Radius, float radius) //transform cyinder 3d -> 2d
{
	float lengthU = 2*(float)pai*(Radius + radius);
	//float lengthU = 2*(float)pai*Radius;
	float lengthV = 2*(float)pai*radius;
	double angleU = 0.0;
	double angleV = 0.0;
	double sinU = 0.0;
	double cosU = 0.0;
	point3fv temp, data;
	point3fv vecOM, vecMP;
	point3fv crossOMMP;
	point3fv normalOMMP;
	float dotOMMP, dot;
	float lengthOMMP;
	for(unsigned int i = 0; i < g_PartTorus3ds.size(); i++)
	{
		temp.x = g_PartTorus3ds[i].x;
		temp.y = g_PartTorus3ds[i].y;
		temp.z = g_PartTorus3ds[i].z;

		//data.x  ---> 0.0
		data.x = 0.0;
		//data.y  --->  U
		sinU = temp.y/sqrt(temp.x*temp.x + temp.y*temp.y);
		cosU = temp.x/sqrt(temp.x*temp.x + temp.y*temp.y);
		angleU = sincosToAngle(sinU, cosU);
		if(angleU <= pai) 
			data.y = (float)(angleU*(Radius + radius));
			//data.y = angleU/(2*pai)*lengthU;
		else
			data.y = (float)((angleU - 2*pai)*(Radius + radius));
			//data.y = -lengthU + angleU/(2*pai)*lengthU;
		//data.z ----> V
		vecOM.x = (float)(Radius*cosU);
		vecOM.y = (float)(Radius*sinU);
		vecOM.z = 0.0;
		vecMP.x = temp.x - vecOM.x;
		vecMP.y = temp.y - vecOM.y;
		vecMP.z = temp.z - vecOM.z;
		crossOMMP = crossProduct(vecOM, vecMP);
		dotOMMP = dotProduct(vecOM, vecMP);
		lengthOMMP = lengthVector(crossOMMP);
		normalOMMP.x = crossOMMP.x/lengthOMMP;
		normalOMMP.y = crossOMMP.y/lengthOMMP;
		normalOMMP.z = crossOMMP.z/lengthOMMP;
		dot = dotProduct(crossOMMP, normalOMMP);
		angleV = atan2(dot, dotOMMP);
		
		if(vecMP.z <= 0.0)    
		{
			data.z =(float)( -angleV/(2*pai)*lengthV);
		}
		else
		{
			data.z =  (float)(angleV/(2*pai)*lengthV);
			
		}
		g_DevelopPartTorus.push_back(data);
	}
}
point3fv crossProduct(point3fv begin, point3fv end)  // calculate cross product 
{
	point3fv vec;
	vec.x = begin.y*end.z - begin.z*end.y;
	vec.y = begin.z*end.x - begin.x*end.z;
	vec.z = begin.x*end.y - begin.y*end.x;
	return vec;
}
float dotProduct(point3fv vec1, point3fv vec2)      //calculate dot product
{
	float data;
	data = vec1.x*vec2.x + vec1.y*vec2.y + vec1.z*vec2.z;
	return data;
}
float lengthVector(point3fv vec) // length of vector
{
	float data;
	data = sqrt(vec.x*vec.x + vec.y*vec.y + vec.z*vec.z);
	return data;
}

/////////////////////////////////////////
//////////////for curve fitting////////
/////////////////////////////////////////
vector <DATA> seleceCurvePoint(int N, vector <DATA> v)
{
	vector <DATA> data;
	DATA temp1;
	for(int i = 0; i < 2*N; i++)
	{
		int mark1 = 0;
		float max = 0.0;
		for(int j = 0; j < (int)v.size(); j++)
		{
			if( (v[j].alpha >= pai*i/N) && (v[j].alpha < pai*(i+1)/N))
			{
				if(v[j].dis >= max)
				{
					max = v[j].dis;
					mark1 = j;
				}
			}
		}
		if (mark1 != 0)
		{
			temp1.v = v[mark1].v;
			temp1.alpha = v[mark1].alpha;
			temp1.dis = v[mark1].dis;
			data.push_back(temp1);
		}
	}	
	return data;
}

float disAllCurve(vector <DATA> v)
{
	point3fv  v0;
	v0.x = v0.y = v0.z = 0.0;
	float disSum = 0.0;
	for(unsigned int i = 0; i < v.size(); i++)
	{
		disSum += distancePoint(v0,v[i].v);
	}
	return disSum;
}

int detectCone(point3fv start, point3fv end)   // detect a  upward cone or downward
{
	int upV = 0;
	if((end.z - start.z < 0) && (end.y - start.y > 0))
		return upV = 1;
	else if((end.z - start.z < 0) && (end.y - start.y < 0))
		return upV = 2;
	else if((end.z - start.z > 0) && (end.y - start.y > 0))
		return upV = 3;
	else if((end.z - start.z > 0) && (end.y - start.y < 0))
		return upV = 4;
	else 
		return 0;
}
vector <point3fv> saveProjectConePoint(point3fv start, point3fv end) //  save Project Cone Point, not all
{
	vector <point3fv> data;
	int upV = 0;
	upV =  detectCone(start, end);

	if((upV == 1) || (upV == 2)) 
		for(unsigned int i = 0; i < g_Object3fPoints.size(); i++)
		{
			if((g_Object3fPoints[i].z >= end.z) && (g_Object3fPoints[i].z <= start.z))
			{
				data.push_back(g_Object3fPoints[i]);
			}
		}
	else if((upV == 3)|| (upV == 4)) 
		for(unsigned int i = 0; i < g_Object3fPoints.size(); i++)
		{
			if((g_Object3fPoints[i].z >= start.z) && (g_Object3fPoints[i].z <= end.z))
			{
				data.push_back(g_Object3fPoints[i]);
			}
		}
    return data;
}
vector <point3fv> projectToCone(point3fv start, point3fv end, vector <point3fv> data)  //  project to Cone
{
	vector <point3fv> temp;
	float R = 0.0;
	float r = 0.0;
	double theta = 0.0;
	int mark =  detectCone(start,end);
	point3fv startA;
	point3fv endB;
	if(mark == 1 || mark == 4)
	{
		R = fabs(end.y);
		r = fabs(start.y);
		for(unsigned int i = 0; i < data.size(); i++)
		{
			startA.x = r*data[i].x/sqrt(data[i].x*data[i].x + data[i].y*data[i].y);
			startA.y = r*data[i].y/sqrt(data[i].x*data[i].x + data[i].y*data[i].y);
			startA.z = start.z;
			endB.x = R*data[i].x/sqrt(data[i].x*data[i].x + data[i].y*data[i].y);
			endB.y = R*data[i].y/sqrt(data[i].x*data[i].x + data[i].y*data[i].y);
			endB.z = end.z;
			temp.push_back(getFootOfPerpendicular(data[i], startA, endB));
		}
	}
	else if(mark == 2 || mark == 3)
	{
		R = fabs(start.y);
		r = fabs(end.y);
		for(unsigned int i = 0; i < data.size(); i++)
		{
			startA.x = R*data[i].x/sqrt(data[i].x*data[i].x + data[i].y*data[i].y);
			startA.y = R*data[i].y/sqrt(data[i].x*data[i].x + data[i].y*data[i].y);
			startA.z = start.z;
			endB.x = r*data[i].x/sqrt(data[i].x*data[i].x + data[i].y*data[i].y);
			endB.y = r*data[i].y/sqrt(data[i].x*data[i].x + data[i].y*data[i].y);
			endB.z = end.z;
			temp.push_back(getFootOfPerpendicular(data[i], startA, endB));
		}
	}
	return temp;
}
point3fv getFootOfPerpendicular(const point3fv &pt, const point3fv &begin, const point3fv &end)  // get foot of perpendicular 
{
	point3fv retVal;
	point3fv temp;
	temp.x = begin.x - end.x;
	temp.y = begin.y - end.y;
	temp.z = begin.z - end.z;
	if(abs(temp.x) < 0.00000001 && abs(temp.y) < 0.00000001 && abs(temp.z) < 0.00000001)
	{
		retVal = begin;
		return retVal;
	}
	float u = (pt.x - begin.x)*(begin.x - end.x) 
			+ (pt.y - begin.y)*(begin.y - end.y)
			+ (pt.z - begin.z)*(begin.z - end.z);  
    u = u/((temp.x*temp.x)+(temp.y*temp.y)+(temp.z*temp.z));  
  
	retVal.x = begin.x + u*temp.x;
    retVal.y = begin.y + u*temp.y;  
	retVal.z = begin.z + u*temp.z;
	return retVal;
}
vector <point3fv> transformCone3dTo2d(point3fv start, point3fv end, vector <point3fv> data)// 3D -> 2D
{
	double angle = 0.0f;
	float radius = 0.0f;   // di yuan radius
	float length = 0.0f;	// develop radius
	point3fv z = crossPoint(start, end);
	int mark =  detectCone(start,end);
	vector <point3fv> retData;
	point3fv temp;
	if(mark == 1 || mark == 4)
	{
		for(unsigned int i = 0; i < data.size(); i++)
		{
			radius = sqrt(data[i].x*data[i].x + data[i].y*data[i].y);
			length = sqrt(radius*radius + (z.z - data[i].z)*(z.z - data[i].z));
			angle = acos((2.0*radius*radius - data[i].x*data[i].x - (data[i].y -radius)*(data[i].y -radius))/(2.0*radius*radius)); 
			if(data[i].x < 0.0)
				angle = -angle;
			angle = radius/length*angle - M_PI*0.5;
			temp.x =  0.0 + z.x;
			temp.y = length*cos(angle) + z.y;
			temp.z = length*sin(angle) + z.z;
			retData.push_back(temp);
		}
	}
	else if(mark == 2 || mark == 3)
	{
		for(unsigned int i = 0; i < data.size(); i++)
		{
			radius = sqrt(data[i].x*data[i].x + data[i].y*data[i].y);
			length = sqrt(radius*radius + (z.z - data[i].z)*(z.z - data[i].z));
			angle = acos((2.0*radius*radius - data[i].x*data[i].x - (data[i].y -radius)*(data[i].y -radius))/(2.0*radius*radius)); 
			if(data[i].x < 0.0)
				angle = -angle;
			angle = radius/length*angle + M_PI*0.5;

			temp.x =  0.0 + z.x;
			temp.y = length*cos(angle) + z.y;
			temp.z = length*sin(angle) + z.z;
			retData.push_back(temp);
		}
	}
	return retData;
}
double getAngleAxesX(point3fv p)   // with X axes
{
	double angle = 0.0f; // 
	point3fv vec1,vec2;
	vec1.x = 1.0f;  //vector 1
	vec1.y = 0.0;
	vec1.z = 0.0;
	vec2.x =  p.x;  //vector 2
	vec2.y = p.y;
	vec2.z = 0.0;

	double productValue = (double)(vec1.x*vec2.x + vec1.y*vec2.y + vec1.z*vec2.z);
	double vec1Model = (double)sqrt(vec1.x*vec1.x + vec1.y*vec1.y + vec1.z*vec1.z);
	double vec2Model = (double)sqrt(vec2.x*vec2.x + vec2.y*vec2.y + vec2.z*vec2.z);
	double cosValue = productValue/(vec1Model*vec2Model);
	
	angle = acos(cosValue)*180/M_PI;
	return angle;
}
point3fv crossPoint(point3fv A, point3fv B)  // line  AB with Z axes cross in one point
{
	point3fv p1, p2;
	point3fv temp;
   
	p1.x = 0.0;
	p1.y = A.y;
	p1.z = A.z;
	p2.x = 0.0f;
	p2.y = B.y;
	p2.z = B.z;

	temp.x = 0.0f;
	temp.y = 0.0f;
	temp.z = p1.z - p1.y*(p2.z - p1.z)/(p2.y - p1.y);
	return temp;
}