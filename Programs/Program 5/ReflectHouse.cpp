#include<stdio.h>
#include<math.h>
#include<GL/glut.h>
#include<iostream>

GLfloat house[3][9] = { {100.0,100.0,250.0,250.0,175.0,150.0,150.0,200.0,200.0}, // x co ordinates for home
					   {100.0,300.0,300.0,100.0,400.0,100.0,150.0,150.0,100.0}, // y co ordinates for home
					   {1.0,  1.0,  1.0, 1.0, 1.0,  1.0,  1.0,  1.0,  1.0  } // extra because we we need homogenous co ordinates 
};

GLfloat result[3][9] = { {0}, {0}, {0} };

GLfloat theta, m, c;
GLfloat h = 100.0;
GLfloat k = 100.0;
GLfloat ref_mat[3][3] = { {0}, {0}, {0} };

void drawhouse()
{

	glColor3f(1.0, 0.0, 1.0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(house[0][0], house[1][0]);
	glVertex2f(house[0][1], house[1][1]);
	glVertex2f(house[0][2], house[1][2]);
	glVertex2f(house[0][3], house[1][3]);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex2f(house[0][5], house[1][5]);
	glVertex2f(house[0][6], house[1][6]);
	glVertex2f(house[0][7], house[1][7]);
	glVertex2f(house[0][8], house[1][8]);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex2f(house[0][1], house[1][1]);
	glVertex2f(house[0][4], house[1][4]);
	glVertex2f(house[0][2], house[1][2]);
	glEnd();
}

void drawReflectedHouse() {


	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(result[0][0], result[1][0]);
	glVertex2f(result[0][1], result[1][1]);
	glVertex2f(result[0][2], result[1][2]);
	glVertex2f(result[0][3], result[1][3]);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex2f(result[0][5], result[1][5]);
	glVertex2f(result[0][6], result[1][6]);
	glVertex2f(result[0][7], result[1][7]);
	glVertex2f(result[0][8], result[1][8]);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex2f(result[0][1], result[1][1]);
	glVertex2f(result[0][4], result[1][4]);
	glVertex2f(result[0][2], result[1][2]);
	glEnd();
}


void multiply()
{
	int i, j, l;
	for (i = 0; i < 3; i++) // 3 rows
	{
		for (j = 0; j < 9; j++) // 9 is the number of columns 
		{
			
			for (l = 0; l < 3; l++)
				result[i][j] = result[i][j] + ref_mat[i][l] * house[l][j];
			
		}
	}
}

void reflect() {
//  reflection matrix 
//  {   {cos(2*theta), sin(2 * theta), 0},
//	    {sin(2 * theta), -cos(2*theta), 0},
//	    {-c*sin(2 * theta), c*(1+cos(2 * theta), 1}
//	}
//    cos(2*theta) = cos^2(theta) - sin^2(theta)
//    sin2theta = 2*sin(theta)cos(theta)

	ref_mat[0][0] = cos(theta)*cos(theta) - sin(theta)*sin(theta);
	ref_mat[0][1] = 2 * sin(theta)*cos(theta);
	ref_mat[0][2] = 0;
	ref_mat[1][0] = 2 * sin(theta)*cos(theta);
	ref_mat[1][1] = sin(theta)*sin(theta) - cos(theta)*cos(theta);
	ref_mat[1][2] = 0;
	ref_mat[2][0] = (-c)* 2 * sin(theta)*cos(theta);
	ref_mat[2][1] = c * (1 + cos(theta)*cos(theta) - sin(theta)*sin(theta));
	ref_mat[2][2] = 1;

	
	multiply();


}
void display()
{
	
	float x1 = 0;
	float x2 = 500;
	float y1 = m * x1 + c;
	float y2 = m * x2 + c;
	glClear(GL_COLOR_BUFFER_BIT);

	drawhouse();
	reflect();
	drawReflectedHouse();

	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glEnd();

	glFlush();
}
void myinit()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glColor3f(1.0, 0.0, 0.0);
	glLineWidth(2.0); // similar to glPointSize(), 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-500.0, 500.0, -500.0, 500.0);
	
}
int main(int argc, char **argv)
{

	std::cout<< "enter the value of m(y=mx+c):";
	std::cin >> m;
	std::cout << "Enter the value of c:";
	std::cin >> c;

	theta = atan(m); // inverse tan, gives angle in radians

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("reflected house");
	glutDisplayFunc(display);
	myinit();
	glutMainLoop();
	return 0;
} 