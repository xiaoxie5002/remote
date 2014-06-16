#include "myOpengl.h"
#define N 4 // number of control points
#define D 2 // number of dimensions
#define T 100 // number of u subintervals


extern float GL_UI_RoateX ;
extern float GL_UI_RoateY;
//window
extern int winID[5]; // window id
int windowNum = 0;
char *windowName[] = {"window1", " window2", "window3", "window4", "window5"};
const char *developMode[] = {"Cone","Cylinder","Torus"};

// screen
const int screenWidth = 640;  //screen
const int screenHeight = 480;
bool isDeveloped = false;
//mouse, keyboard
bool mouseLeftDown = false;
bool mouseRightDown = false;
bool mouseMiddleDown= false;
int mouseX = 0, mouseY = 0;
double weight = 0.8;

//mouse2, keyboard2
bool mouseLeftDown2 = false;
bool mouseRightDown2 = false;
bool mouseMiddleDown2= false;
int mouseX2 = 0, mouseY2 = 0;
extern vector <point3fv> mouse3D2;
extern vector <point3fv> mouse2D2;
//mouse3, keyboard3
//int mouseX3 = 0, mouseY3 = 0; //mouseX3 == mouseX, mouseY3 == mouseX

//mouse5 keyboard5
int mouseX5 = 0, mouseY5 = 0;
bool mouseLeftDown5 = false;
bool mouseRightDown5 = false;
bool mouseMiddleDown5= false;
extern vector <point3fv> mouse3D5; 
//
int window2RoateZ = 0;
bool isRightLeftKey = false;
//vector <point3fv> mouse3D;
float MINR = 0.0, MAXR = 0.0;
///////////////*************************

static GLfloat ctrlPoints[N][3] = {{100, 100, 110}, {200, 350, 120}, {400,300, 30}, {480,100,40}};
int ww = 1000;
int wh = 800;
int pickRadius = 20;
// remember the moving control name
int MOVENAME = -1;
///////////////*************************

void GLUT_INITs(int argc, char **argv)
{
	    glutInit(&argc, argv);

		//window1
        GLUT_INIT(windowNum++);
		GLUT_CALL_FUNC();  
		GLUT_SET_MENU();
		MY_INIT();
        
		//window2
		 GLUT_INIT2(windowNum++);
		 GLUT_CALL_FUNC2();  
		 MY_INIT2();

		 //window3
		 GLUT_INIT3(windowNum++);
		 GLUT_CALL_FUNC3();  
		 MY_INIT3();

		 //window4
		 GLUT_INIT4(windowNum++);
		 GLUT_CALL_FUNC4();  
		 MY_INIT4();

		 //window5
		 GLUT_INIT5(windowNum++);
		 GLUT_CALL_FUNC5();  
		 MY_INIT5();
}
void idle()
{
	for(int loop = 0; loop < windowNum; ++loop)
	{
		glutSetWindow(winID[loop]);
		glutPostRedisplay();
	}
}
void GLUT_INIT(int num)
{
        glutInitDisplayMode(GLUT_RGB| GLUT_DOUBLE | GLUT_DEPTH);
        glutInitWindowSize(screenWidth, screenHeight);
		glutInitWindowPosition(0,0);
        winID[num] = glutCreateWindow(windowName[num]);
}
void MY_INIT()
{
	glClearColor(1.0, 1.0, 1.0, 0.0);  // set background color
	glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);    //enable z-bufferring
    glClearDepth(1.0f);         // 0 is near, 1 is far
    glDepthFunc(GL_LEQUAL);
}
void GLUT_CALL_FUNC()
{
	glutDisplayFunc(myGlutDisplay); 
	glutReshapeFunc(myGlutReshape); 
	glutMouseFunc(myGlutMouse);	
	glutMotionFunc(myGlutMotion);
	glutKeyboardFunc(myGlutKeyboard);
}
void myGlutDisplay(void) 
{
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();
		gluLookAt(GL_UI_View.x, GL_UI_View.y, GL_UI_View.z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
		glTranslatef( GL_UI_ObjectPos[0], GL_UI_ObjectPos[1], GL_UI_ObjectPos[2] ); 
		glScalef(GL_UI_Scale, GL_UI_Scale, GL_UI_Scale);

		glPushMatrix();
		//draw selected objects in show panel
		glMultMatrixf(GL_UI_SphereRot);//roate object
		if(GL_UI_IsShowAxes) 
		{
			drawAxes(); //draw Axes
		}
		glRotated(GL_UI_RoateX,1,0,0);
        glRotated(GL_UI_RoateY,0,1,0);

		if(GL_UI_IsShowPointCloud)	//show object point cloud
		{
			glColor3f(0.82, 0.41, 0.12);
			//drawPointCloud(g_Object3fPoints);
			drawPointCloudColor(g_Object3fPoints);
			//drawPointCloud(g_curvePoint);
		}

		glPopMatrix();
		glFlush();
        glutSwapBuffers();
}
void myGlutReshape(int w, int h)
{
        glViewport(0, 0, w, h);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(30.0, (double)w / (double)h, 1.0, 100.0);
        glMatrixMode(GL_MODELVIEW);
}
void myGlutMouse(int button, int state, int x, int y)
{
	mouseX = x;
	mouseY = y;
	/*
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
			mouseLeftDown = true;
			if(glutGetModifiers() == GLUT_ACTIVE_CTRL) // ctrl + mouseLeftDown; 
			{
					//
			}
	}
	else 
		mouseLeftDown = false;
	*/
}
void myGlutMotion(int x, int y)
{
	static int xdir,ydir;
	xdir = x - mouseX;
    ydir = y - mouseY;
	GL_UI_RoateX += xdir*weight;
	GL_UI_RoateY += ydir*weight;

	mouseX = x;
	mouseY = y;
	
	glutPostRedisplay();
}
void myGlutKeyboard(unsigned char key, int x, int y)
{
	switch(key)
	{
	case 'Q':
	case 'q':
		exit(0);
		break;
	case '+':
		GL_UI_Scale += 0.005;
		break;
	case '-':
		GL_UI_Scale -= 0.005;
		break;
	}
}

void GLUT_INIT2(int num)
{
        glutInitDisplayMode(GLUT_RGB| GLUT_DOUBLE | GLUT_DEPTH);
        glutInitWindowSize(screenWidth, screenHeight);
		glutInitWindowPosition(screenWidth,0);
        winID[num] = glutCreateWindow(windowName[num]);
}
void MY_INIT2()
{
	glClearColor(1.0, 1.0, 1.0, 0.0);  // set background color
	glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);    //enable z-bufferring
    glClearDepth(1.0f);         // 0 is near, 1 is far
    glDepthFunc(GL_LEQUAL);
}
void GLUT_CALL_FUNC2()
{
	glutDisplayFunc(myGlutDisplay2); 
	glutReshapeFunc(myGlutReshape2); 
	glutMouseFunc(myGlutMouse2);
	glutKeyboardFunc(myGlutKeyboard2);
	glutSpecialFunc(myGlutSpecialkey2);
	glutMotionFunc(myMouseMove);
}
void myGlutDisplay2(void) //yoz
{
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();
		gluLookAt(GL_UI_View.x, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);  //yoz
		glTranslatef( GL_UI_ObjectPos[0], GL_UI_ObjectPos[1], GL_UI_ObjectPos[2] ); 
		glScalef(GL_UI_Scale, GL_UI_Scale, GL_UI_Scale);
		glPushMatrix();
		glMultMatrixf(GL_UI_SphereRot);//roate object
		glRotated(window2RoateZ,0,0,1);  // Z axies roate

		if(GL_UI_IsShowPointCloud)	//show object point cloud
		{
			glColor3f(0.82, 0.41, 0.12);
			//drawPointCloud(g_Object3fPoints);
			drawPointCloudColor(g_Object3fPoints);
			glColor3f(1.0, 1.0, 0.5); //yellow
			drawRectancleYOZ(300,300);
			drawAxes(); //draw Axes
			draw2dControlPoints(mouse3D2);
			draw2dControlLines(mouse3D2);
		}
       glutSwapBuffers();
}
void myGlutReshape2(int w, int h)
{
        glViewport(0, 0, w, h);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(30.0, (double)w / (double)h, 1.0, 100.0);
        glMatrixMode(GL_MODELVIEW);
}
void myGlutMouse2(int button, int state, int x, int y)
{
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
			mouseX2 = x;
			mouseY2 = y;
			point3fv temp;
			mouseLeftDown2 = true;
			int choiceFound = 0;
			
			if(glutGetModifiers() == GLUT_ACTIVE_ALT) // alt + mouseLeftDown; 
			{
				temp.x = 0;
				temp.y = x;
				temp.z = y;
				mouse2D2.push_back(temp);
				temp = screen2dToWorld3d2(x,  y);//screen coordinate  -> 3D world coordinate 
				//cout<<"mouse X = "<<x<<" Y = "<<y<<endl;
				mouse3D2.push_back(temp);
			}
			if(glutGetModifiers() == GLUT_ACTIVE_CTRL) // ctrl + mouseLeftDown; 
			{

				for ( unsigned int i = 0; i < mouse2D2.size() && !choiceFound; i++)
				{
					// Use globally defined pickRadius
					if ((abs(mouse2D2[i].y - mouseX2) <= pickRadius) &&
						(abs(mouse2D2[i].z - mouseY2) <= pickRadius))
					{
						MOVENAME = i;
						choiceFound = 1;
						//printf("Control point %d was picked.\n",MOVENAME);
					}
				}
			}
	}
}
void myGlutKeyboard2(unsigned char key, int x, int y)
{
	switch(key)
	{
	case 'q':
		exit(0);
		break;
	case '+':
		GL_UI_Scale += 0.005;
		break;
	case '-':
		GL_UI_Scale -= 0.005;
		break;
	default:
		break;
	}
}
void myGlutSpecialkey2(int key, int x, int y)
{
	switch(key)
	{
	case GLUT_KEY_RIGHT:
		window2RoateZ = (window2RoateZ + 10)%180;
		isRightLeftKey = true;
		break;
	case GLUT_KEY_LEFT:
		window2RoateZ = (window2RoateZ - 10)%180;
		isRightLeftKey = true;
		break;
	default:
		break;
	}
}
void myMouseMove(int x, int y)
{
	if (MOVENAME > -1)
	{
	// printf("New control point %d location:\n", MOVENAME);
	 mouse2D2[MOVENAME].x = 0.0;
	 mouse2D2[MOVENAME].y = x;
	 mouse2D2[MOVENAME].z = y;

	 point3fv temp;
	 temp = screen2dToWorld3d2(x,  y);//screen coordinate  -> 3D world coordinate 
	 //cout<<"mouse X = "<<x<<" Y = "<<y<<endl;
	 mouse3D2[MOVENAME].x = temp.x;
	 mouse3D2[MOVENAME].y = temp.y;
	 mouse3D2[MOVENAME].z = temp.z;
	 MOVENAME = -1;
	glutPostRedisplay();
	}
}

void GLUT_INIT3(int num)
{
        glutInitDisplayMode(GLUT_RGB| GLUT_DOUBLE | GLUT_DEPTH);
        glutInitWindowSize(screenWidth, screenHeight);
		glutInitWindowPosition(0,screenHeight);
        winID[num] = glutCreateWindow(windowName[num]);
}
void MY_INIT3()
{
	glClearColor(1.0, 1.0, 1.0, 0.0);  // set background color
	glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);    //enable z-bufferring
    glClearDepth(1.0f);         // 0 is near, 1 is far
    glDepthFunc(GL_LEQUAL);
}
void GLUT_CALL_FUNC3()
{
	glutDisplayFunc(myGlutDisplay3); 
	glutReshapeFunc(myGlutReshape3); 
	glutMouseFunc(myGlutMouse3);	
	glutMotionFunc(myGlutMotion3);
	glutKeyboardFunc(myGlutKeyboard3);	
}
void myGlutDisplay3(void) 
{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();
		gluLookAt(GL_UI_View.x, GL_UI_View.y, GL_UI_View.z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
		glTranslatef( GL_UI_ObjectPos[0], GL_UI_ObjectPos[1], GL_UI_ObjectPos[2] ); 
		glScalef(GL_UI_Scale, GL_UI_Scale, GL_UI_Scale);

		glPushMatrix();
		//draw selected objects in show panel
		glMultMatrixf(GL_UI_SphereRot);//roate object
		if(GL_UI_IsShowAxes) 
		{
			drawAxes(); //draw Axes
		}
		glRotated(GL_UI_RoateX,1,0,0);
        glRotated(GL_UI_RoateY,0,1,0);
		if(GL_UI_IsShowPointCloud)	//show object point cloud
		{
			float numLine = mouse3D2.size()/2;
			int intNumLine = floor(numLine);	
			point3fv start, end;
			vector <point3fv> data;
			vector <point3fv> projectData;
			vector <point3fv> developData;
			if(intNumLine == 0)
				drawPointCloudColor(g_Object3fPoints);  // if not drawing point cloud, mouse3D2.size() does not updata.
			else
				for(int i = 0; i < intNumLine; i++)
				{
					start =	mouse3D2[i*2];
					end = mouse3D2[i*2+1];
					data = saveProjectConePoint(start, end);
					projectData = projectToCone(start, end, data);
					//developData = transformCone3dTo2d(start,end, projectData);
					//g_PartCone3ds = projectToCone(start, end, data);
					//drawPointCloudColor(data);
					drawPointCloudColor(projectData);
					//drawPointCloudColor(developData);
				}
		}
		glPopMatrix();
        glutSwapBuffers();
}
void myGlutReshape3(int w, int h)
{
        glViewport(0, 0, w, h);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(30.0, (double)w / (double)h, 1.0, 100.0);
        glMatrixMode(GL_MODELVIEW);
}
void myGlutMouse3(int button, int state, int x, int y)
{
	mouseX = x;
	mouseY = y;
	/*
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
			mouseLeftDown = true;
			if(glutGetModifiers() == GLUT_ACTIVE_CTRL) // ctrl + mouseLeftDown; 
			{
					//
			}
	}
	else 
		mouseLeftDown = false;
		*/
}
void myGlutMotion3(int x, int y)
{
	static int xdir,ydir;
	xdir = x - mouseX;
    ydir = y - mouseY;
	GL_UI_RoateX += xdir*weight;
	GL_UI_RoateY += ydir*weight;

	mouseX = x;
	mouseY = y;
	
	glutPostRedisplay();
}
void myGlutKeyboard3(unsigned char key, int x, int y)
{
	switch(key)
	{
	case 'Q':
	case 'q':
		exit(0);
		break;
	case '+':
		GL_UI_Scale += 0.005;
		break;
	case '-':
		GL_UI_Scale -= 0.005;
		break;
	}
}

void GLUT_INIT4(int num)
{
        glutInitDisplayMode(GLUT_RGB| GLUT_DOUBLE | GLUT_DEPTH);
        glutInitWindowSize(screenWidth, screenHeight);
		glutInitWindowPosition(screenWidth,screenHeight);
        winID[num] = glutCreateWindow(windowName[num]);
}
void MY_INIT4()
{
	glClearColor(1.0, 1.0, 1.0, 0.0);  // set background color
	glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);    //enable z-bufferring
    glClearDepth(1.0f);         // 0 is near, 1 is far
    glDepthFunc(GL_LEQUAL);
}
void GLUT_CALL_FUNC4()
{
	glutDisplayFunc(myGlutDisplay4); 
	glutReshapeFunc(myGlutReshape4); 
//	glutMotionFunc(myGlutMotion);
//	glutMouseFunc(myGlutMouse4);
	glutKeyboardFunc(myGlutKeyboard4);
}
void myGlutDisplay4(void) 
{
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();
		gluLookAt(GL_UI_View.x, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);  //yoz
		glTranslatef( GL_UI_ObjectPos[0], GL_UI_ObjectPos[1], GL_UI_ObjectPos[2] ); 
		glScalef(GL_UI_Scale, GL_UI_Scale, GL_UI_Scale);
		glPushMatrix();
		//draw selected objects in show panel
		glMultMatrixf(GL_UI_SphereRot);//roate object
		//glRotated(GL_UI_RoateX,1,0,0);
       // glRotated(GL_UI_RoateY,0,1,0);
		if(GL_UI_IsShowAxes) 
		{
			drawAxes(); //draw Axes
		}
		if(GL_UI_IsShowPointCloud)	//show object point cloud
		{
			float numLine = mouse3D2.size()/2;
			int intNumLine = floor(numLine);	
			point3fv start, end;
			vector <point3fv> developData;
			vector <point3fv> data;
			vector <point3fv> projectData;
			if(intNumLine == 0)
				drawPointCloudColor(g_Object3fPoints);
			else 
			{
				for(int i = 0; i < intNumLine; i++)
				{
					start =	mouse3D2[i*2];
					end = mouse3D2[i*2+1];
					data = saveProjectConePoint(start, end);
					projectData = projectToCone(start, end, data);
					developData = transformCone3dTo2d(start,end, projectData);
					//drawPointCloudColor(developData);
					drawPointCloudColor(developData);

					//start =	mouse3D2[i*2];
					//end = mouse3D2[i*2+1];
					//developData = transformCone3dTo2d(start,end, g_PartCone3ds);
					//drawPointCloudColor(developData);
				}
			}
		}
		glPopMatrix();
        glutSwapBuffers();
}
void myGlutReshape4(int w, int h)
{
        glViewport(0, 0, w, h);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(30.0, (double)w / (double)h, 1.0, 100.0);
        glMatrixMode(GL_MODELVIEW);
}
void myGlutKeyboard4(unsigned char key, int x, int y)
{
	switch(key)
	{
	case 'Q':
	case 'q':
		exit(0);
		break;
	case '+':
		GL_UI_Scale += 0.005;
		break;
	case '-':
		GL_UI_Scale -= 0.005;
		break;
	}
}

void GLUT_INIT5(int num)
{
        glutInitDisplayMode(GLUT_RGB| GLUT_DOUBLE | GLUT_DEPTH);
        glutInitWindowSize(screenWidth, screenHeight);
		glutInitWindowPosition(screenWidth*2,0);
        winID[num] = glutCreateWindow(windowName[num]);
}
void MY_INIT5()
{
	glClearColor(1.0, 1.0, 1.0, 0.0);  // set background color
	glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);    //enable z-bufferring
    glClearDepth(1.0f);         // 0 is near, 1 is far
    glDepthFunc(GL_LEQUAL);
}
void GLUT_CALL_FUNC5()
{
	glutDisplayFunc(myGlutDisplay5); 
	glutReshapeFunc(myGlutReshape5); 
	glutMouseFunc(myGlutMouse5);
	glutKeyboardFunc(myGlutKeyboard5);
	glutSpecialFunc(myGlutSpecialkey5);
}
void myGlutDisplay5(void) //xoy
{
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();
		gluLookAt(0.0, 0.0, -GL_UI_View.z,  0.0, 0.0, 0.0, 1.0, 0.0, 0.0);  //xoy
		glTranslatef( GL_UI_ObjectPos[0], GL_UI_ObjectPos[1], GL_UI_ObjectPos[2] ); 
		glScalef(GL_UI_Scale, GL_UI_Scale, GL_UI_Scale);
		glPushMatrix();
		glMultMatrixf(GL_UI_SphereRot);//roate object
		glRotated(window2RoateZ,0,0,1);
		if(GL_UI_IsObjLoaded)
		{
			if(GL_UI_IsShowPointCloud)	//show object point cloud
			{
				glColor3f(0.82, 0.41, 0.12);
				//drawPointCloud(g_Object3fPoints);
				drawPointCloudColor(g_Object3fPoints);
				glColor3f(1.0, 1.0, 0.5); //yellow
				drawRectancleXOY(300,300);
				drawAxes(); //draw Axes
				if(mouse3D5.size() > 1)  // Get 4 points by mouse.
				{
					glColor3f(0.95f, 0.207f, 0.031f); // red
					drawLine(mouse3D5[0], mouse3D5[1]);  //print lineAB; AB is for computering cylinder radius 
					float len = distancePoint(mouse3D5[0], mouse3D5[1]);
					drawCircle(0.0, 0.0, len, 20);
					if(mouse3D5.size() > 3)  
					{
						glColor3f(0.0f, 1.0f, 0.0f); // green
						drawLine(mouse3D5[2], mouse3D5[3]); //print lineCD; CD is the range of devleloping area.
						float len2 = distancePoint(mouse3D5[2], mouse3D5[3]);
						drawCircle(0.0, 0.0, len2, 20);
						float majorRadius = (len2 + len)/2;  // distance from the center of the tube to the center of the torus,
						float minorRadius = (len2 - len)/2;  //the radius of the tube.
						MINR = minorRadius;
						MAXR = majorRadius;
						if(!isDeveloped)
						{
							isDeveloped = true;
							clock_t start, end;
							start = clock();
							savePartTorus(majorRadius,  minorRadius); // part torus
							transformTorus3dTo2d(majorRadius,  minorRadius); // develop
							//transformCylinder3dTo2d(radius, window2RoateZ);
							end = clock();
							cout<<"Develop point Cloud needs: "<<(double)(end - start)/CLOCKS_PER_SEC<<"seconds"<<endl;
						}
					}
				}
			}
		}	
		glPopMatrix();	
        glutSwapBuffers();
}
void myGlutReshape5(int w, int h)
{
        glViewport(0, 0, w, h);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(30.0, (double)w / (double)h, 1.0, 100.0);
        glMatrixMode(GL_MODELVIEW);
}
void myGlutMouse5(int button, int state, int x, int y)
{
	mouseX5 = x;
	mouseY5 = y;
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
			mouseLeftDown5 = true;
			if(glutGetModifiers() == GLUT_ACTIVE_ALT) // alt + mouseLeftDown; 
			{
				point3fv temp;
				temp = screen2dToWorld3d2(x,  y);//screen coordinate  -> 3D world coordinate 
				mouse3D5.push_back(temp);
				//cout<<"mouset 5>> x = "<<temp.x <<"y = "<<temp.y <<"z = "<<temp.z <<endl;
			}
	}
}
void myGlutKeyboard5(unsigned char key, int x, int y)
{
	switch(key)
	{
	case 'q':
		exit(0);
		break;
	case '+':
		GL_UI_Scale += 0.005;
		break;
	case '-':
		GL_UI_Scale -= 0.005;
		break;
	default:
		break;
	}
}
void myGlutSpecialkey5(int key, int x, int y)
{
	switch(key)
	{
	case GLUT_KEY_RIGHT:
		window2RoateZ = (window2RoateZ + 10)%180;
		isRightLeftKey = true;
		break;
	case GLUT_KEY_LEFT:
		window2RoateZ = (window2RoateZ - 10)%180;
		isRightLeftKey = true;
		break;
	default:
		break;
	}
}


void drawLine(point3fv A, point3fv B)	// draw a line in 3D
{
	glPushMatrix();
	glBegin(GL_LINES);
	glVertex3f(A.x, A.y, A.z);
	glVertex3f(B.x, B.y, B.z);
	glEnd();
	glPopMatrix();
}
void drawCircle(float cx, float cy, float r, int num_segments) 
{ 
	float theta = 2 * 3.1415926 / float(num_segments); 
	float c = cosf(theta);//precalculate the sine and cosine
	float s = sinf(theta);
	float t;

	float x = r;//we start at angle = 0 
	float y = 0; 
    
	glBegin(GL_LINE_LOOP); 
	for(int ii = 0; ii < num_segments; ii++) 
	{ 
		glVertex2f(x + cx, y + cy);//output vertex 
        
		//apply the rotation matrix
		t = x;
		x = c * x - s * y;
		y = s * t + c * y;
	} 
	glEnd(); 
}
void drawAxes() // draw coordinate
{
	glBegin(GL_LINES);
		glColor3f(1.0, 0.0, 0.0); //red X
		glVertex3d(0.0, 0.0,0.0 ); 
		glVertex3d(50.0, 0.0,0.0 ); 

		glColor3f(0.0, 1.0, 0.0); //green y
		glVertex3d(0.0,  0.0,0.0 ); 
		glVertex3d(0.0, 50.0,0.0 ); 

		glColor3f(0.0, 0.0, 1.0); //blue z
		glVertex3d(0.0, 0.0,0.0 ); 
		glVertex3d(0.0, 0.0,50.0 ); 
	glEnd();
}
void drawPointCloud(vector <point3fv> points)
{
	glPointSize(1.0);
	glBegin(GL_POINTS);
	for( unsigned int i = 0; i < points.size(); i++)
	{	
		if(points[i].y > 0.0)
			glColor3f(0.86, 0.08, 0.24);  // color Crimson
		else
			glColor3f(0.0, 0.0, 1.0);	// color blue
		glVertex3f((GLfloat)points[i].x, (GLfloat)points[i].y, (GLfloat)points[i].z);
	}
	glEnd();
	glutPostRedisplay();
}
void drawPointCloudColor(vector <point3fv> points) // draw point cloud with Color
{
	glPointSize(1.0);
	glBegin(GL_POINTS);
	if(points.size() > 0)
		for( unsigned int i = 0; i < points.size(); i++)
		{	
			double sinval = points[i].y/sqrt(points[i].x*points[i].x + points[i].y*points[i].y);
			double cosval = points[i].x/sqrt(points[i].x*points[i].x + points[i].y*points[i].y);
			double angle = sincosToAngle(sinval, cosval);
			if(angle < pai/4)
				glColor3f(0.0, 0.0, 0.0); // color black
			else if(angle < pai/2)
				glColor3f(0.0, 0.0, 1.0);// color blue
			else if(angle < pai*3/4)
				glColor3f(1.0, 1.0, 0.0);// color yellow
			else if(angle < pai)
				glColor3f(0.0, 1.0, 0.0); // color green
			else if(angle < pai*5/4)
				glColor3f(1.0, 0.0, 0.0); // color red 
			else if(angle < pai*6/4)
				glColor3f(0.0, 1.0, 1.0); // color cyan
			else if(angle < pai*7/4)
				glColor3f(1.0, 0.0, 1.0); //color  pinkish red
			else
				glColor3f(1.0, 0.0, 0.0); //white
			glVertex3f((GLfloat)points[i].x, (GLfloat)points[i].y, (GLfloat)points[i].z);
		}
	glEnd();
	glutPostRedisplay();
}
void drawPointCloudColorWindow4(vector <point3fv> points, float Radius, float radius) // draw point cloud with Color in window4
{
	glBegin(GL_POINTS);
	if(points.size() > 0)
		for( unsigned int i = 0; i < points.size(); i++)
		{	
			if(points[i].y >(Radius + radius)*pai*3/4)
				glColor3f(0.0, 1.0, 0.0); // color green
			else if(points[i].y > (Radius + radius)*pai*2/4)
				glColor3f(1.0, 1.0, 0.0);// color yellow
			else if(points[i].y > (Radius + radius)*pai*1/4)
				glColor3f(0.0, 0.0, 1.0);// color blue
			else if(points[i].y > 0.0)
				glColor3f(0.0, 0.0, 0.0); // color black
			else if(points[i].y > -(Radius + radius)*pai/4)
				glColor3f(1.0, 0.0, 0.0); // color red 
			else if(points[i].y > -(Radius + radius)*pai/2)
				glColor3f(1.0, 0.0, 1.0); //color  pinkish red
			else if(points[i].y > -(Radius + radius)*pai*3/4)
				glColor3f(0.0, 1.0, 1.0); // color cyan
			else
			glColor3f(1.0, 0.0, 0.0); //white
			glVertex3f((GLfloat)points[i].x, (GLfloat)points[i].y, (GLfloat)points[i].z);
		}
	glEnd();
	glutPostRedisplay();
}
void drawRectancleXOY(int height, int width)
{
		glPushMatrix();
		glBegin(GL_QUADS);
		glVertex3f(width, height, 0);
		glVertex3f(width, -height, 0);
		glVertex3f(-width, -height, 0);
		glVertex3f(-width, height, 0);
		glEnd();
		glPopMatrix();
}
void drawRectancleYOZ(int width, int height )
{
		glPushMatrix();
		glBegin(GL_QUADS);
		glVertex3f(0, height, width);
		glVertex3f(0, height, -width);
		glVertex3f(0, -height, -width);
		glVertex3f(0, -height, width);
		glEnd();
		glPopMatrix();
}
void screen2dToWorld3d(int x, int y)  //get screen coordinate by mouse -> 3D world coordinate 
{
	int viewport[4];
	double modelView[16], projection[16];
	double wx, wy, wz;
	float z;
	point3fv temp;
	glGetIntegerv(GL_VIEWPORT, viewport);  
	glGetDoublev(GL_MODELVIEW_MATRIX, modelView);
	glGetDoublev(GL_PROJECTION_MATRIX, projection);
	glReadPixels(x, glutGet(GLUT_WINDOW_HEIGHT) - y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &z);
	gluUnProject(x,glutGet(GLUT_WINDOW_HEIGHT) - y, z, modelView, projection, viewport, &wx, &wy, &wz);
	temp.x = wx;
	temp.y = wy;
	temp.z = wz;
	mouse3D2.push_back(temp);
	//cout<<"world coodinate at z , wx = "<<wx <<" wy = "<<wy <<" wz = "<<wz<<endl;
	//cout<<"mouse3D.size() = "<<mouse3D.size()<<endl;
}

point3fv screen2dToWorld3d2(int x, int y)  // screen point by mouse, transfy 2d to 3d
{
	int viewport[4];
	double modelView[16], projection[16];
	double wx, wy, wz;
	float z;
	point3fv temp;
	glGetIntegerv(GL_VIEWPORT, viewport);  
	glGetDoublev(GL_MODELVIEW_MATRIX, modelView);
	glGetDoublev(GL_PROJECTION_MATRIX, projection);
	glReadPixels(x, glutGet(GLUT_WINDOW_HEIGHT) - y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &z);
	gluUnProject(x,glutGet(GLUT_WINDOW_HEIGHT) - y, z, modelView, projection, viewport, &wx, &wy, &wz);
	temp.x = wx;
	temp.y = wy;
	temp.z = wz;
	return temp;
}

void GLUT_SET_MENU()
{
	 int MENU_ID[2];

        //サブメニュー１
        MENU_ID[0] = glutCreateMenu(sub_menu_1);
        glutAddMenuEntry("sub 1_1", 1);
        glutAddMenuEntry("sub 1_2", 2);

        //サブメニュー2
        MENU_ID[1] = glutCreateMenu(sub_menu_2);
        glutAddMenuEntry("sub 2_1", 1);
        glutAddMenuEntry("sub 2_2", 2);

        //ここから、メインメニューの並び
        glutCreateMenu(menu);
        glutAddSubMenu( "Sub menu part 1", MENU_ID[0] );//サブメニューとして設定
        glutAddMenuEntry("name 1", 1);
        glutAddMenuEntry("name 2", 2);
        glutAddMenuEntry("name 3", 3);
        glutAddSubMenu( "Sub menu part 2", MENU_ID[1] );//サブメニューとして設定

        glutAttachMenu(GLUT_RIGHT_BUTTON);
}
//------------- ここから各種コールバック -----------------//
void display()
{
        glClear(GL_COLOR_BUFFER_BIT);
        glFlush();
}

//ここからメニュー関係
void menu(int val)
{
        std::cout <<"name "<< val <<" click!\n";
}
//サブメニュー1関係
void sub_menu_1(int val)
{
        std::cout <<"sub menu 1_" <<val<<"\n";
}

//サブメニュー2関係
void sub_menu_2(int val)
{
        std::cout <<"sub menu 2_"<< val<<"\n";
}
/////////////////////////////////////////////////////////////////////
void myPick(int button, int state, int xPosition, int yPosition)
{
	// left mouse button down
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		GLuint newX = xPosition;
		GLuint newY = wh - yPosition;
		printf("Pick location: x = %d   y = %d\n", newX, newY);

	// determine which control point is picked

	int choiceFound = 0;

	for (int i = 0; i < N && !choiceFound; i++)
	{
		// Use globally defined pickRadius

		if ((abs(ctrlPoints[i][0] - newX) <= pickRadius) &&
		    (abs(ctrlPoints[i][1] - newY) <= pickRadius))
		{
			MOVENAME = i;
			choiceFound = 1;
			printf("Control point %d was picked.\n",MOVENAME);
		}
	}
	}

	// left mouse button up
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		MOVENAME = -1;
	}
	glutPostRedisplay();
}

// mouse motion function


void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
	ww = w;
	wh = h;
}
void init()
{
   glClearColor(0.0, 0.0, 1.0, 0.0);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluOrtho2D(0.0, ww, 0.0, wh);
}
void display2DControlPolyline()
{
	glLineWidth(2.0);
	glColor3f(1.0f, 0.0f, 0.0f);
  
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < N; i++)
	{
      glVertex2i(ctrlPoints[i][0],ctrlPoints[i][1]);
	}
    glEnd();
    glFlush();
}

void display2DControlPoints()
{
	glPointSize(3.0);
	glColor3f(0.0f, 1.0f, 0.0f);

	glBegin(GL_POINTS);
	for (int i = 0; i < N; i++)
	{
      glVertex2i(ctrlPoints[i][0],ctrlPoints[i][1]);
	}
    glEnd();
    glFlush();
}

void draw2dControlPoints(vector <point3fv> points)// control points
{
	glPointSize(5.0);
	glColor3f(0.0f, 1.0f, 0.0f);

	glBegin(GL_POINTS);
	if(points.size() > 0)
		for ( unsigned int i = 0; i < points.size(); i++)
		{
			 glVertex3f(points[i].x, points[i].y,points[i].z);
		}
    glEnd();
    glFlush();
}
void draw2dControlLines(vector <point3fv> points)//lines of  control points
{
	glLineWidth(2.0);
	glColor3f(0.0f, 1.0f, 1.0f);
  
	glBegin(GL_LINES);
	if(points.size() > 1)
		for ( unsigned int i = 0; i <  points.size(); i++)
		{
		  glVertex3f(points[i].x, points[i].y,points[i].z);
		}
    glEnd();
    glFlush();
}



