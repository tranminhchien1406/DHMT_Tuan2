// Lab_2.cpp : Lap phuong 3D
//

#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
void DisplayFunc(void)
{
	static float alpha = 0;
	//xoa buffer va matrix//
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	//
	glTranslatef(0, 0, -10);
	glRotatef(30, 1, 0, 0);
	glRotatef(alpha, 0, 1, 0);

	glBegin(GL_QUADS);
	glColor3f(0, 0, 0); glVertex3f(-1, -1, -1);
	glColor3f(0, 0, 1); glVertex3f(-1, -1, 1);
	glColor3f(0, 1, 1); glVertex3f(-1, 1, 1);
	glColor3f(0, 1, 0); glVertex3f(-1, 1, -1);

	glColor3f(1, 0, 0); glVertex3f(1, -1, -1);
	glColor3f(1, 0, 1); glVertex3f(1, -1, 1);
	glColor3f(1, 1, 1); glVertex3f(1, 1, 1);
	glColor3f(1, 1, 0); glVertex3f(1, 1, -1);

	glColor3f(0, 0, 0); glVertex3f(-1, -1, -1);
	glColor3f(0, 0, 1); glVertex3f(-1, -1, 1);
	glColor3f(1, 0, 1); glVertex3f(1, -1, 1);
	glColor3f(1, 0, 0); glVertex3f(1, -1, -1);

	glColor3f(0, 1, 0); glVertex3f(-1, 1, -1);
	glColor3f(0, 1, 1); glVertex3f(-1, 1, 1);
	glColor3f(1, 1, 1); glVertex3f(1, 1, 1);
	glColor3f(1, 1, 0); glVertex3f(1, 1, -1);

	glColor3f(0, 0, 0); glVertex3f(-1, -1, -1);
	glColor3f(0, 1, 0); glVertex3f(-1, 1, -1);
	glColor3f(1, 1, 0); glVertex3f(1, 1, -1);
	glColor3f(1, 0, 0); glVertex3f(1, -1, -1);

	glColor3f(0, 0, 1); glVertex3f(-1, -1, 1);
	glColor3f(0, 1, 1); glVertex3f(-1, 1, 1);
	glColor3f(1, 1, 1); glVertex3f(1, 1, 1);
	glColor3f(1, 0, 1); glVertex3f(1, -1, 1);

	glEnd();
	//xoay
	alpha = alpha + 0.1;
	//ngung
	glFlush();
	glutSwapBuffers();
	//update
	glutPostRedisplay();
}

//----------------------------------------------------//
//ham thay doi khi kich thuoc window thay doi
void ReshapeFunc(int width, int heigth)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(20, width / (float)heigth, 5, 15);
	glViewport(0, 0, width, heigth);

	glMatrixMode(GL_MODELVIEW);
	glutPostRedisplay();
}
//----------------------------------------------------------//
//ham thay doi khi key duoc bam
void KeyboardFunc(unsigned char key, int x, int y)
{
	int foo;
	foo = x + y;
	if ('q' == key || 'Q' == key || 27 == key);
	exit(0);
}
//------------------------------------------------------//
int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	
	glutCreateWindow("Spinning Cube");
	
	glClearColor(0, 0, 0, 0);
	glEnable(GL_DEPTH_TEST);

	glutDisplayFunc(&DisplayFunc);
	glutReshapeFunc(&ReshapeFunc);
	glutKeyboardFunc(&KeyboardFunc);

	glutMainLoop();
	return 0;
}


