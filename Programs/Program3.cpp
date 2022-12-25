#include<stdlib.h>
#include<gl/glut.h>
#include<iostream>

int x1, x2, y_1, y2, flag = 0;

// function to draw a pixel
void drawPixel(int x, int y)
{

	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
	glFlush();
}

// function to draw line using Bresenham's line drawing algorithm
void drawLine() {
	
	int one = rand() % 2, two = rand() % 2, three = rand() % 2;
	glColor3f(one, two, three);

	int dx, dy;
	dx = x2 - x1, dy = y2 - y_1;
	int d = 2 * dy - dx;
	int x = x1, y = y_1;
	while (x != x2 && y != y2) {
		drawPixel(x, y);

		if (d < 0) {
			d = d + 2 * dy;
			x = x + 1;
		}
		else {
			d = d + 2 * (dy - dx);
			x = x + 1;
			y = y + 1;
		}
	}
	glFlush();
}

void myInit()
{ 
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(3);
	gluOrtho2D(-250, 250, -250, 250);
}

void mouseFunc(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (flag == 0)
		{
			std::cout << "x1, y1 : ";
			x1 = x - 250;
			y_1 = 250 - y;
			flag++;
			std::cout << x1 << " " << y_1 << " \n";
		}
		else
		{
			std::cout << "x2, y2 : ";
			x2 = x - 250;
			y2 = 250 - y;
			flag = 0;
			std::cout << x2 << " " << y2 << " \n";
			drawLine();
		}
	}
}

void display() {}

int main(int argc, char** argv)
{
	int choice;
	std::cout << "Enter 1 for keyboard and 2 for mouse \n";
	std::cin >> choice;
	if (choice == 1)
	{
		std::cout << "Enter x1 : ";
		std::cin >> x1;
		std::cout << "Enter y1 : ";
		std::cin >> y_1;
		std::cout << "Enter x2 : ";
		std::cin >> x2;
		std::cout << "Enter y2 : ";
		std::cin >> y2;
	}
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Line Drawing");
	if (choice == 2)
	{
		glutMouseFunc(mouseFunc);
		glutDisplayFunc(display);
		myInit();
	}
	else
	{
		glutDisplayFunc(drawLine);
		myInit();
	}
	glutMainLoop();
} 