#include <algorithm> //sort function
#include <iostream>  // to take inputs 
#include <Windows.h>  //sleep function
#include <gl/glut.h>

// not related to program
/* stdlib - This header defines several general purpose functions,
including dynamic memory management, random number generation, etc
simply don't include all the header files, kow what is for what*/

int m, n;
int wx = 500, wy = 500;
static float intx[10] = { 0 }; // why this - array to hold the x corodinate list 
float x[100], y[100];

void drawLine(float x1, float y1, float x2, float y2)
{
	Sleep(1000); // so that we can see how filling is happening, one line at once 
	glColor3f(0, 0, 1);
	glBegin(GL_LINES);
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glEnd();
	glFlush(); // tried placing it in display, didn't work
}

void edgeDetect(float x1, float y1, float x2, float y2, int scanline)
{
	float temp;
	
	if (y2 < y1)
	{  // swap x1 and x2
		temp = x1;
		x1 = x2;
		x2 = temp;
	  // swap y1 and y2
		temp = y1;
		y1 = y2;
		y2 = temp;
	}
	// because y=s1 can only intersect if this is the case(no equal to - write why; understood but idk how to explain)
	if (scanline > y1 && scanline < y2)
		intx[m++] = x1 + (scanline - y1) * (x2 - x1) / (y2 - y1);
	// we're just finding the x cordinate of intersection and adding it to the out list 
	// line eqn . (x-x1) = m*(y-y1)  of polygon line  
}

void scanFill(float x[], float y[])
{
	for (int s1 = 0; s1 <= wy; s1++)
	{
		m = 0;
		for (int i = 0; i < n; i++)
			// pass coordinates of polygon line and scanline(eqn, y = s1 )
			edgeDetect(x[i], y[i], x[(i + 1) % n], y[(i + 1) % n], s1);
		std::sort(intx, (intx + m)); // void sort(firstpos, lastpos, comp(optional)), deafult-ascending order
		// intx gives starting address of that array, +m gives last element address (for godsake learn c n c++)
		if (m >= 2)
		{   //one scan line x coordinates list 
			for (int i = 0; i < m; i = i + 2)
				// y stays same (y=s1), take 2 vertices at a time, draw line
				drawLine(intx[i], s1, intx[i + 1], s1);
		}
	}
}

void displayFilledPolygon()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glLineWidth(2);
	glBegin(GL_LINE_LOOP); // construct polygon with the given vertices , end, 
	for (int i = 0; i < n; i++)
		glVertex2f(x[i], y[i]);
	glEnd();
	//then fill it
	scanFill(x, y);
	
}

void myInit()
{
	glClearColor(1, 1, 1, 1);
	glColor3f(1, 0, 0);
	gluOrtho2D(0, wx, 0, wy);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	std::cout << "Enter the number of sides : ";
	std::cin >> n;
	std::cout << "Enter the coordinates of vertices : \n";
	for (int i = 0; i < n; i++) 
	{
		std::cin >> x[i] >> y[i];
	}
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutCreateWindow("ScanLine fill polygon");
	glutDisplayFunc(displayFilledPolygon);
	myInit();
	glutMainLoop();
}
