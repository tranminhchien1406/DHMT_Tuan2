// Lab_2.cpp : Am tra 3D
//


#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include <math.h>
#include <iostream>
//-------cac ham thuc hien-------//
void initGlut(int argc, char **argv);
void displayFunc(void);
void idleFunc(void);
void reshapeFunc(int width, int height);
void mouseFunc(int button, int state, int x, int y);
void mouseMotionFunc(int x, int y);
void keyboardFunc(unsigned char key, int x, int y);
void specialFunc(int key, int x, int y);

//-----cac ham OpenGL khac------//
void countFrames(void);
void renderBitmapString(float x, float y, float z, void *font, char *string);


bool bUsePredefinedcamera = true;
bool bFullscreen = false;
int nWindowID;
//camera attributes//
float viewerPosition[3] = { 0.0, 0.0, -50.0 };
float viewerDirection[3] = { 0.0, 0.0, 0.0 };
float viewerUp[3] = { 0.0, 1.0, 0.0 };
//rolation values for navigation//
float navigationRolation[3] = { 0.0, 0.0, 0.0 };

//---------------------------//
//parameters for the framecounter
char pixelstring[30];
int cframe = 0;
int time = 0;
int timebase = 0;
//vi tri cua chuot khi nhan
int mousePressedX = 0, mousePressedY = 0;
float lastXOffset = 0.0, lastYOffset = 0.0, lastZOffset = 0.0;
//hanh dong cua chuot
int leftMouseButtonActive = 0, middleMouseButtonActive = 0, rightMouseButtonActive = 0;
//hanh dong cac nut khac
int shiftActive = 0, altActive = 0, ctrlActive = 0;

//-------------------------------//
bool init = false;

//-----------------------------//
void displayFunc(void)
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(50.0, 1.33, 1.0, 100000.0);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	GLfloat lightpos[4] = { 5.0, 15.0, 10.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, lightpos);

	glTranslatef(viewerPosition[0], viewerPosition[1], viewerPosition[2]);

	glRotatef(navigationRolation[0], 1.0f, 0.0f, 0.0f);
	glRotatef(navigationRolation[1], 0.0f, 1.0f, 0.0f);

	glutSolidTeapot(10.0);

	countFrames();

	glutSwapBuffers();
}
//------------------------------------------//
void initGlut(int argc, char **argv)
{
	//glut window initialization
	glutInit(&argc, argv);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(100, 100);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	nWindowID = glutCreateWindow("sipleGLUT");

	glutDisplayFunc(displayFunc);
	glutReshapeFunc(reshapeFunc);
	glutKeyboardFunc(keyboardFunc);
	glutSpecialFunc(specialFunc);
	glutMouseFunc(mouseFunc);
	glutMotionFunc(mouseMotionFunc);
	glutIdleFunc(idleFunc);
}
//-----------------------------------------//
void idleFunc(void) 
{
	glutPostRedisplay();
}
//--------------------------------//
void reshapeFunc(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(75.0, 1.33, 1.0, 1000.0);
	glMatrixMode(GL_MODELVIEW);
}
//------------------------------------------//
//mouse callback
void mouseFunc(int button, int state, int x, int y)
{
	//lay du lieu
	switch (glutGetModifiers())
	{
		case GLUT_ACTIVE_SHIFT:
			shiftActive = 1;
			break;
		case GLUT_ACTIVE_ALT:
			altActive = 1;
			break;
		case GLUT_ACTIVE_CTRL:
			ctrlActive = 1;
			break;
		default:
			shiftActive = 0;
			altActive = 0;
			ctrlActive = 0;
			break;
	}
	//lay nut chuot
	if (button == GLUT_LEFT_BUTTON)

		if (state == GLUT_DOWN)
		{
			leftMouseButtonActive += 1;
		}
		else
			leftMouseButtonActive -= 1;
	else if (button == GLUT_MIDDLE_BUTTON)
		if (state == GLUT_DOWN) {
			middleMouseButtonActive += 1;
			lastXOffset = 0.0;
			lastYOffset = 0.0;
		}
		else
			middleMouseButtonActive -= 1;
	else if (button == GLUT_RIGHT_BUTTON)
		if (state == GLUT_DOWN) {
			rightMouseButtonActive += 1;
			lastZOffset = 0.0;
		}
		else
			rightMouseButtonActive -= 1;
	mousePressedX = x;
	mousePressedY = y;
}

//--------------------------------------------------//
void mouseMotionFunc(int x, int y)
{
	float xOffset = 0.0, yOffset = 0.0, zOffset = 0.0;
	if (leftMouseButtonActive) {
		navigationRolation[0] += ((mousePressedY - y) * 180.0f) / 200.0f;
		navigationRolation[1] += ((mousePressedX - x) * 180.0f) / 200.0f;
		mousePressedY = y;
		mousePressedX = x;
	}
	//paining
	else if(middleMouseButtonActive){
		xOffset = (mousePressedX + x);
		if (!lastXOffset == 0.0) {
			viewerPosition[0] -= (xOffset - lastXOffset) / 8.0;
			viewerDirection[0] -= (xOffset - lastXOffset) / 8.0;
		}
		lastXOffset = xOffset;

		yOffset = (mousePressedY + y);
		if (!lastYOffset == 0.0) {
			viewerPosition[1] -= (yOffset - lastYOffset) / 8.0;
			viewerDirection[1] -= (yOffset - lastYOffset) / 8.0;
		}
		lastYOffset = yOffset;
	}
	//depth movement
	else if(rightMouseButtonActive){
		zOffset = (mousePressedX + x);
		if (!lastZOffset == 0.0) {
			viewerPosition[2] -= (zOffset - lastZOffset) / 8.0;
			viewerDirection[2] -= (zOffset - lastZOffset) / 8.0;
		}
		lastZOffset = zOffset;
	}
}
//------------------------------------//
//keyboard func
void keyboardFunc(unsigned char key, int x, int y)
{
	switch (key) {
		#ifdef WIN32
			case '\033':
				exit(0);
				break;
		#endif
			case 'f':
				bFullscreen = !bFullscreen;
				if (bFullscreen)
					glutFullScreen();
				else {
					glutSetWindow(nWindowID);
					glutPositionWindow(100, 100);
					glutReshapeWindow(640, 480);
				}
				break;
	}

}
//---------------------------------------------//
//special func
void specialFunc(int key, int x, int y)
{
}
//-------------------------------------------//
//count frames
void countFrames(void)
{
	time = glutGet(GLUT_ELAPSED_TIME);
	cframe++;
	if (time - timebase > 50) {
		printf(pixelstring, "fps: %4.2f", cframe*1000.0 / (time - timebase));
		timebase = time;
		cframe = 0;
	}
	glPushMatrix();
	glLoadIdentity();
	glDisable(GL_LIGHTING);
	glColor4f(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, 200, 0, 200);
	glMatrixMode(GL_MODELVIEW);

	renderBitmapString(5, 5, 0.0, GLUT_BITMAP_HELVETICA_10, pixelstring);

	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}
//-------------------------------------------------//
void renderBitmapString(float x, float y, float z, void *font, char *string)
{
	char *c;
	glRasterPos3f(x, y, z);
	for (c = string; *c != '\0'; c++) {
		glutBitmapCharacter(font, *c);
	}
}
//-----------------------------------------------//
void main(int argc, char **argv)
{
	printf("simpleGLUT\n\tGordon Wetzstein [gordon.wetzstein@medien.uniweimar.de]\n\n");
	printf("keys:\n\tf\t- toggle fullsreen\n\tesc\t- exit\n\n");
	printf("mouse:\n\tleft button\t- rolation\n\tmidddle button\t- paining\n\tright button\t- zoom in and out\n");
	glutMainLoop();
}