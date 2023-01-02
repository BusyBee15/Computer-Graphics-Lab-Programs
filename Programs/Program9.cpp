#include<gl/glut.h>
#include<math.h>

void sphere()
{
	double c = 3.142 / 180, phi, phir, phir2, theta, thetar, x, y, z, c80, xc, yc, r; 
	// converting to radians
	// to get longitudes
	for (phi = -80.0; phi <= 80.0; phi += 10.0) // why only -80 to 80 = (160)
	{	//(rest 10(on both sides) for triangle fan)
	        // latitudes only top pole to bottom pole - half rotation , 180 deg 
		
		phir = c * phi;  //  in radians – for the 1st point
		phir2 = c * (phi + 10);  // for the 2nd point
		
		// to get latitudes - full rotation, so -180 to 180
		glBegin(GL_QUAD_STRIP);
		for (theta = -180.0; theta <= 180.0; theta += 10.0) 
		{ //theta angle b/w to longitudes , phi angle b/w two latitudes - change theta and phi in for loop (incr) to observe 
			thetar = c * theta;  // deg to radian

			x = sin(thetar) * cos(phir);
			y = cos(thetar) * cos(phir);
			z = sin(phir);
			glVertex3d(x, y, z); // 1st point

	
			x = sin(thetar) * cos(phir2);
			y = cos(thetar) * cos(phir2);
			z = sin(phir2);
			glVertex3d(x, y, z); // 2nd point
		}
		glEnd();
	}

	// now generate two trinagle fans for top and bottom poles part of sphere 

	//1st pole 
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1.0, 0.0, 0.0); // both triangle colors are affected by this
	glVertex3d(0.0, 0.0, 1.0);   // top pole  - got it , 

	// to generate triangle fan, we fix one point(poles), then keep generating points at fixed z
	// imagination is all this takes 

	c80 = c * 80.0;  // why 80? - that is till where we want to generate triangle fan
	z = sin(c80); // why z is fixed - ok got it 
	//- imagine a sphere whose center is at 0,0,0 and top pole is at 0,0,1 and bottom pole - 0,0,-1
	// first, z axis is perpendicular to you, then imagine things 

	for (theta = -180.0; theta <= 180.0; theta += 10.0)
	{    // incr deg should be same as angle b/w longitudes
		thetar = c * theta;
		x = sin(thetar) * cos(c80);
		y = cos(thetar) * cos(c80);
		glVertex3d(x, y, z);
	}
	glEnd();

	//2nd pole 
	glBegin(GL_TRIANGLE_FAN);
	glVertex3d(0.0, 0.0, -1.0); // bottom pole
	z = -sin(c80);
	for (theta = -180.0; theta <= 180.0; theta += 10.0)
	{
		thetar = c * theta;
		x = sin(thetar) * cos(c80);
		y = cos(thetar) * cos(c80);
		glVertex3d(x, y, z);
	}
	glEnd();

}
void display()
{
	int j;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);// also depth buffer bit,for tetrahedron
	//i didn't get the output, but here I got output without using this ? why?
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // the quad doesn't get filled up and only 
	//boundary appears

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -1); // why is this used? - without this, hidden surface was also visible
	// change the below parameter to control the viewing angle
	glRotatef(40.0, 0.0, 1.0, 0.0); // rotate by how much angle and about which axis (angle,x,y,z)

	sphere();


	glFlush();
}
void myinit()
{
	glClearColor(1.0, 1.0, 1.0, 0);
	glColor3f(0, 0, 1.0);
	glPointSize(1.0);
	glOrtho(-1, 1, -1, 1, -1, 1);  // idk how , but even if we use gluOrtho2D, no differnece in output
	// i mean, this is 3D, na , how can the output be same even if we use 2D projection function?
	//gluOrtho2D(-1, 1, -1, 1);
}
void main(int argc, char* argv[])
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Sphere Display");
	glutDisplayFunc(display);
	myinit();
	glutMainLoop();
} 
