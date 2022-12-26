#include<stdio.h>
#include<stdlib.h>
#include<GL/glut.h>
#include<math.h>


GLfloat spin = 0.0;  // initial rotation degree 
int singleb, doubleb;


void spindisplay()
{
	spin = spin + 0.0000005;
	if (spin > 360) spin -= 360;

	// we can't see the square spinning without this 
	// we have changed the animation parameter - redisplay the content 
	// thus func sets the falg which says display callback to be called in next iteration
	glutPostRedisplay();

}

void mouse(int btn, int state, int x, int y)
{
	if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		glutIdleFunc(spindisplay); // to continually increment animation parameter - degree 
	if (btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
		glutIdleFunc(NULL); // to stop the rotation
}

void square()
{
	glBegin(GL_QUADS);
	glColor3f(1, 0, 0);  // red for one corner 
	glVertex2f(-100, 50);
	glColor3f(0, 1, 0);  // green for one corner 
	glVertex2f(100, 50);
	glColor3f(0, 0, 1);  // blue for another 
	glVertex2f(100, -50);
	glColor3f(1, 0, 1);  // some other color for final vertex
	glVertex2f(-100, -50);
	glEnd();

}

void singleb_display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	square();
	glFlush();
}

void doubleb_display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glRotatef(spin, 0, 0, 1);
	square();
	glutSwapBuffers();
}

void myinit()
{
	glClearColor(1, 1, 1, 1);
	gluOrtho2D(-200, 200, -200, 200);

}

int main(int argc, char** argv)
{

	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // GLUT_SINGLE for single buffer 
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	singleb = glutCreateWindow("single buffer");
	myinit();
	glutDisplayFunc(singleb_display);



	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // GLUT_DOUBLE for double buffer 
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(500, 00);
	doubleb = glutCreateWindow("double buffer");
	myinit();
	glutDisplayFunc(doubleb_display);
	glutMouseFunc(mouse);

	glutMainLoop();
}