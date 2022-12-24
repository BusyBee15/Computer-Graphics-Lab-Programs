#include <GL/glut.h>
#include <iostream>
#include <cstdlib>
#include <math.h>

#define WINDOW_WIDTH 500
#define WINDOW_HEIGHT 500

int xc, yc, r;
int p1_x, p2_x, p1_y, p2_y;
int point1_done = 0;

void draw_circle(int xc, int yc, int x, int y)
{
	//int one = rand() % 2, two = rand() % 2, three = rand() % 2;
	//glColor3f(one, two, three);
	glBegin(GL_POINTS);
	//why are we adding centre to every point?;

	//so that if the center is not the origin, this would fix it 
	//we are calculating x and y as though origin is the center so, adding xc, yc is must. 
	glVertex2i(xc + x, yc + y);
	glVertex2i(xc - x, yc + y);
	glVertex2i(xc + x, yc - y);
	glVertex2i(xc - x, yc - y);
	glVertex2i(xc + y, yc + x);
	glVertex2i(xc - y, yc + x);
	glVertex2i(xc + y, yc - x);
	glVertex2i(xc - y, yc - x);
	glEnd();
}

void circleBres()
{
	int one = rand() % 2, two = rand() % 2, three = rand() % 2;
	std::cout << one << " " << two << " " << three << "\n ";
	// Idk why, but this integer function was displaying just black color- all circles were in black
	// float gives correct answer - color color cirlces :)
	//glColor3i(one, two, three);
	glColor3f(one, two, three);
	int x = 0, y = r;
	int d = 3 - 2 * r;
	while (x <= y)
	{
		draw_circle(xc, yc, x, y);
		x++;
		if (d < 0)
			d = d + 4 * x + 6;
		else
		{
			y--;
			d = d + 4 * (x - y) + 10;
		}
		//draw_circle(xc, yc, x, y);
	}
	glFlush();
}
void mouseFuncCircle(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && point1_done == 0)
	{//why are we doing this
		std::cout << x << " " <<y << "\n";
		p1_x = x - 250;
		p1_y = 250 - y;
		point1_done = 1;
	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		float exp;
		p2_x = x - 250;
		p2_y = 250 - y;
		xc = p1_x;
		yc = p1_y;
		exp = (p2_x - p1_x) * (p2_x - p1_x) + (p2_y - p1_y) * (p2_y - p1_y);
		r = (int)(sqrt(exp));
		circleBres();
		point1_done = 0;
	}
}

void drawingCircle() {}

void myInit()
{
	glClearColor(0, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	// comment this out, try to pick random colors for different circles - 
	// so, i need to put this func in circlebres func and pass random values (0/1)
	// if you want points to be of random color(many colrs in single circle ,
	// put this func in draw pixel function
	//glColor3f(0.0, 1.0, 0.0);
	glPointSize(5.0);
	gluOrtho2D(-250, 250, -250, 250);
}

int main(int argc, char** argv)
{
	int choice;
	std::cout << "Enter 1 for keyboard, 2 for mouse\n";
	std::cin >> choice;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	switch (choice)
	{
	case 1:
		std::cout << "Enter coordinates of the center and radius : \n";
		std::cin >> xc >> yc >> r;
		glutCreateWindow("Circle Keyboard");
		glutDisplayFunc(circleBres);
		//myInit();
		break;
	case 2:
		glutCreateWindow("Circle Mouse");
		glutMouseFunc(mouseFuncCircle);
		glutDisplayFunc(drawingCircle);
		//myInit();
		break;
	default:
		std::cout << "Invalid choice\n";
	}
	myInit();
	glutMainLoop();
} 