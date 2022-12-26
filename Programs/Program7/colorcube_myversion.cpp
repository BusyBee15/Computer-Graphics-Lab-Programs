#include <stdlib.h>
#include <GL/glut.h>
#include<Windows.h> //to use Sleep() func


GLfloat theta[] = { 0.0,0.0,0.0 };
GLint axis = 0;


void cube() {
	// 2 quads , 1 quad strip - didn't work
	// front
	glBegin(GL_POLYGON);
	glColor3f(0, 0, 1);  // blue
	glVertex3f(200, -200, 200);
	glVertex3f(200, 200, 200);
	glColor3f(0, 1, 0);   // green
	glVertex3f(-200, 200, 200);
	glVertex3f(-200, -200, 200);
	glEnd();

	//right
	glBegin(GL_POLYGON); 
	glColor3f(0, 1, 0);   // green
	glVertex3f(200, -200, -200);
	glVertex3f(200, 200, -200);
	glColor3f(1, 0, 0);   // red
	glVertex3f(200, 200, 200);
	glVertex3f(200, -200, 200);
	glEnd();

	// left
	glBegin(GL_POLYGON);
	glColor3f(1, 0, 0);   // red
	glVertex3f(-200, -200, 200);
	glVertex3f(-200, 200, 200);
	glColor3f(1, 1, 0);   // yellow
	glVertex3f(-200, 200, -200);
	glVertex3f(-200, -200, -200);
	glEnd();

	//top
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 0);   // yellow
	glVertex3f(-200, 200, 200);
	glVertex3f(-200, 200, -200);
	glColor3f(1, 0, 1); // pink
	glVertex3f(200, 200, -200);
	glVertex3f(200, 200, 200);
	glEnd();

	// bottom
	glBegin(GL_POLYGON);
	glColor3f(1, 0, 1); // pink
	glVertex3f(-200, 200, -200);
	glVertex3f(-200, 200, 200);
	glColor3f(0, 1, 1);  //cyan
	glVertex3f(200, 200, 200);
	glVertex3f(200, 200, -200);
	glEnd();

	// back
	glBegin(GL_POLYGON);
	glColor3f(0, 1, 1);  //cyan
	glVertex3f(200, -200, -200); 
	glVertex3f(200, 200, -200); 
	glColor3f(1, 1, 0);   // yellow
	glVertex3f(-200, 200, -200); 
	glVertex3f(-200, -200, -200);
	glEnd();
	glutSwapBuffers();
}

void display(void)
{
	   
		   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // working with 3D, we need depth buffer
		 
		   if (axis == 0) {
			   glRotatef(theta[0], 1.0, 0.0, 0.0); // along x axis
		   }
		   else if (axis == 0) {
			   glRotatef(theta[1], 0.0, 1.0, 0.0); // along y axis
		   }
		   else {
			   glRotatef(theta[2], 0.0, 0.0, 1.0); // along z axis
		   }
		   

		   cube();

		   glFlush();
		 
	   }

void spinCube()
{ 
	Sleep(500); 
	theta[axis] += 2.0;
	if (theta[axis] > 360.0) theta[axis] -= 360.0;
	glutPostRedisplay();
}

// changing the axis 
void mouse(int btn, int state, int x, int y)
{
	// mouse callback, selects an axis about which to rotate 

	if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN) axis = 0;
	if (btn == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) axis = 1;
	if (btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) axis = 2;
}

void myInit()
{
	glClearColor(1, 1, 1, 1);
	// be very careful, nothing displays if you give 2D projection matrix
	glOrtho(-500, 500, -500, 500, -500, 500);
}


void main(int argc, char **argv)
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // single buffer?
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(500, 500);
	glutCreateWindow("colorcube");
	glEnable(GL_DEPTH_TEST); // Enable hidden--surface--removal
	//glutReshapeFunc(myReshape); // how
	myInit();
	glutDisplayFunc(display);
	glutIdleFunc(spinCube);
	glutMouseFunc(mouse);
	 
	glutMainLoop();
} 