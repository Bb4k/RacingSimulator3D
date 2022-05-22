//SURSA:  lighthouse3D:  http://www.lighthouse3d.com/tutorials/glut-tutorial/keyboard-example-moving-around-the-world/ 

#include<gl/freeglut.h>
#include <iostream>
#include<math.h>
#include "Car.h"
#include "Background.h"

// angle of rotation for the camera direction
float angle = 0.0f;
// actual vector representing the camera's direction
float lx = 20.0f, lz = -1.0f;
// XZ position of the camera
float x = 0.0f, z = 0.0f;

float street_lines_z = 100;

GLfloat xwMin = -30.0, ywMin = -30.0, xwMax = 30.0, ywMax = 30.0;

GLfloat dnear = 1.0, dfar = 40.0;

Car car(12, 1, 0, 5);
void changeSize(int w, int h)
{

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;
	float ratio = w * 1.0 / h;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}

float light_x = -45.0f;

void renderScene(void) {

	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	/*std::cout << light_x;
	if (light_x > 360.0f)
		light_x = -360.0f;
	else
		light_x+=1;*/

	glPushMatrix();
		light_x += 0.05;
		glRotatef(light_x, 0, 0, light_x);
	glPopMatrix();

	// Reset transformations
	glLoadIdentity();
	// Set the camera
	gluLookAt(	x, 7.0f, z,
				x + lx, 6.7f, z + lz,
				0, 0.1f, 0.0f);

	street_lines_z -= 0.2;
	if (street_lines_z < -100)
		street_lines_z = 100;

	Background bg;
		bg.drawSun();
		bg.drawGround(.3, .3, .3, 200, 0);
		bg.drawStreetLines(street_lines_z);
		bg.drawStreet(0.2, 0.2, 0.2, 24, 0.5, 400, 1);
	
	glPushMatrix();
		glRotatef(90, 0, 1, 0);
		car.drawCar();
	glPopMatrix();

	glutSwapBuffers();
}

void processNormalKeys(unsigned char key, int x, int y)
{

	switch (key) {
	case 'l':
		angle -= 0.01f;
		lx = sin(angle);
		lz = -cos(angle);
		break;

	}
	if (key == 27)
		exit(0);
}

void processSpecialKeys(int key, int xx, int yy) {

	float fraction = 0.1f;

	switch (key) {
	case GLUT_KEY_LEFT:
		angle -= 0.01f;
		lx = sin(angle);
		lz = -cos(angle);
		break;
	case GLUT_KEY_RIGHT:
		angle += 0.01f;
		lx = sin(angle);
		lz = -cos(angle);
		break;
	case GLUT_KEY_UP:
		x += lx * fraction;
		z += lz * fraction;
		break;
	case GLUT_KEY_DOWN:
		x -= lx * fraction;
		z -= lz * fraction;
		break;
	}
}




int main(int argc, char** argv) {

	// init GLUT and create window

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(1024, 768);
	glutCreateWindow("Scena 3D cu oameni de zapada");

	// register callbacks
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);

	// Draw purple sky
	glClearColor(0.454f, .177f, 0.873f, 0.1);

	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(processSpecialKeys);

	// OpenGL init
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);

	angle -= 0.00f;
	lx = sin(angle);
	lz = -cos(angle);
	
	// enter GLUT event processing cycle
	glutPostRedisplay();
	glutMainLoop();


	return 1;
}

