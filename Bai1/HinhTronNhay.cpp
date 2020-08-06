// Lab_2.cpp : Hinh tron nay nguoc khi cham vao cac canh cua man hinh
//

#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include <math.h>
#define PI 3.14159265f

//--------Gia tri-----------//
char title[] = "Bouncing Ball (2D)"; //tieu de cua man hinh
int windowWidth = 640; //chieu dai cua cua so
int windowHeight = 480; //chieu cao cua cua so
int windowPosX = 50; //cua so tren trai goc x
int windowPosY= 50; //cua so tren trai goc y

GLfloat ballRadius = 0.5f;
GLfloat ballX = 0.0f;
GLfloat ballY = 0.0f;
GLfloat ballXMax, ballXMin, ballYMax, ballYMin;
GLfloat xSpeed = 0.02f;
GLfloat ySpeed = 0.007f;
int refreshMillis = 30;

//projection clipping area
GLdouble clipAreaXLeft, clipAreaXRight, clipAreaYBottom, clipAreaYTop ;

//---------Initialize OpenGL Graphics-----//
void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);//nen den
}
//--------Callback handler for window re-paint evvent-----/
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);//xoa mau buffer
	glMatrixMode(GL_MODELVIEW);//To operate on the model-view matrix
	glLoadIdentity();//Reset ma tran model-view 

	glTranslated(ballX, ballY, 0.0f);//Dich chuyen den (xPos, yPos)

	//su dung triangler de ve hinh tron
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0.0f, 0.0f, 1.0f);//mau xanh duong
	glVertex2f(0.0f, 0.0f);//chinh giua hinh tron
	int numSegments = 100;
	GLfloat angle;
	for (int i = 0; i <= numSegments; i++)//vertex cuoi phai giong vertex dau
	{
		angle = i * 2.0f * PI / numSegments;//360 do cho tat ca segment
		glVertex2f(cos(angle) * ballRadius, sin(angle) * ballRadius);
	}
	glEnd();
	glutSwapBuffers();//hoan doi buffer truoc va sau

	//Animation control//
	ballX += xSpeed;
	ballY += ySpeed;
	//kiem tra xem ball co ton tai
	if (ballX > ballXMax)
	{
		ballX = ballXMax;
		xSpeed = -xSpeed;
	}
	else if (ballX < ballXMin)
	{
		ballX = ballXMin;
		xSpeed = -xSpeed;
	}
	if (ballY > ballYMax)
	{
		ballY = ballYMax;
		ySpeed = -ySpeed;
	}
	else if (ballY < ballYMin)
	{
		ballY = ballYMin;
		ySpeed = -ySpeed;
	}
}

//------Goi lai neu window doi kich thuoc------//
void reshape(GLsizei width, GLsizei height)
{
	//may tinh thay doi toa do theo kich thuoc moi
	if (height == 0) height = 1;
	GLfloat aspect = (GLfloat)width / (GLfloat)height;

	//dat viewport cho kich thuoc cua so moi
	glViewport(0, 0, width, height);
	//dat toa do clipping area cho phu hop voi viewport
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (width >= height)
	{
		clipAreaXLeft = -1.0 * aspect;
		clipAreaXRight = 1.0 * aspect;
		clipAreaYBottom = -1.0;
		clipAreaYTop = 1.0;
	}
	else
	{
		clipAreaXLeft = -1.0 ;
		clipAreaXRight = 1.0;
		clipAreaYBottom = -1.0 / aspect;
		clipAreaYTop = 1.0 / aspect;
	}
	gluOrtho2D(clipAreaXLeft, clipAreaXRight, clipAreaYBottom, clipAreaYTop);
	ballXMin = clipAreaXLeft + ballRadius;
	ballXMax = clipAreaXRight - ballRadius;
	ballYMin = clipAreaYBottom + ballRadius;
	ballYMax = clipAreaYTop - ballRadius;
}

//-------Goi lai neu thoi gian het han----//
void Timer(int value)
{
	glutPostRedisplay();
	glutTimerFunc(refreshMillis, Timer, 0);
}
int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowSize(windowWidth, windowHeight);
	glutInitWindowPosition(windowPosX, windowPosY);
	glutCreateWindow(title);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutTimerFunc(0, Timer, 0);
	init();
	glutMainLoop();
	return 0;
}
