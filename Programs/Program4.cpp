#include<stdlib.h>
#include<gl/glut.h>
#include<iostream>

// create own datatype : an array of 3 floats
typedef GLfloat point[3];

int iter;
point tetra[4] = { // 3rd value is for z co-ordinate, except for the extra point, 
	                  // keep them same in other places (here i have taken 0)
	                {0,250,0},
                    {0,0,250}, // extra point 
                    {250,-250,0},
                    {-250,-250,0} 
               };


void drawTriangle(point p1, point p2, point p3) {
	glBegin(GL_TRIANGLES);
	glVertex3fv(p1);
	glVertex3fv(p2);
	glVertex3fv(p3);
	glEnd();
}

void drawTetrahedron(point p1, point p2, point p3, point p4) {

	// tetrahedron is combining 4 traingles , so the below code 
	glColor3f(1.0, 1.0, 0.0);
	drawTriangle(p1, p2, p3);
	glColor3f(0.0, 1.0, 1.0);
	drawTriangle(p1, p3, p4);
	glColor3f(1.0, 0.0, 1.0);
	drawTriangle(p1, p4, p2);
	// we only see 3 traingles in the tetrahedron, 
	// 4th trinagle is base - that we can't see , so even if we don't
	// include these two lines - we get to see same output - since it is 2D surface, 3D - must include all 4 triangles
	glColor3f(0.0, 0.0, 1.0);
	drawTriangle(p2, p3, p4);
}

void divideTetrahedron(point p1, point p2, point p3, point p4, int iter) {
	point mid[6];
	int j;

	if (iter > 0) {
		for (j = 0; j < 3; j++)mid[0][j] = (p1[j] + p2[j]) / 2;
		for (j = 0; j < 3; j++)mid[1][j] = (p1[j] + p3[j]) / 2;
		for (j = 0; j < 3; j++)mid[2][j] = (p1[j] + p4[j]) / 2;
		for (j = 0; j < 3; j++)mid[3][j] = (p2[j] + p3[j]) / 2;
		for (j = 0; j < 3; j++)mid[4][j] = (p2[j] + p4[j]) / 2;
		for (j = 0; j < 3; j++)mid[5][j] = (p3[j] + p4[j]) / 2;

		// arguments - take one vertex, say p1, take other three points(mid points as calculated above)
		// on the line which originates from chosen vertex
		divideTetrahedron(p1, mid[0], mid[1], mid[2], iter - 1);
		divideTetrahedron(mid[0], p2, mid[3], mid[4], iter - 1);
		divideTetrahedron(mid[1], mid[3],  mid[5], p3, iter - 1);
		divideTetrahedron(mid[2], mid[5], p4, mid[4], iter - 1);
	}
	else
		drawTetrahedron(p1, p2, p3, p4);
}


void display() {
	// since we're working with 3d, clear depth buffer as well
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	divideTetrahedron(tetra[0], tetra[1], tetra[2], tetra[3], iter);
	glFlush();
}

void myInit() {
	glClearColor(1, 1, 1, 1);
	// volume subdivision
	glOrtho(-300.0, 300.0, -300.0, 300.0, -300.0, 300.0);
	// This below line is for surface  subdivision, just comment out above line and
	//uncomment below line, everything else stays the same 
	//gluOrtho2D(-300.0, 300.0, -300.0, 300);
}

void main(int argc, char **argv) {
	std::cout<<("Ënter the number of Subdivisions\n");
	std::cin >> iter;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(600, 600);
	glutCreateWindow("Sierpenski Gasket");
	glutDisplayFunc(display);
	glEnable(GL_DEPTH_TEST);
	myInit();
	glutMainLoop();
}