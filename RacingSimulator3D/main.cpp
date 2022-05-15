//SURSA:  lighthouse3D:  http://www.lighthouse3d.com/tutorials/glut-tutorial/keyboard-example-moving-around-the-world/ 

#include<gl/freeglut.h>
#include<math.h>
#include "Car.h"
// angle of rotation for the camera direction
float angle = 0.0f;
// actual vector representing the camera's direction
float lx = 20.0f, lz = -1.0f;
// XZ position of the camera
float x = 0.0f, z = 0.0f;

float street_lines_z = 100;

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



void draw_street_lines(float z) {

	street_lines_z -= .1;

	if (street_lines_z < -100)
		street_lines_z = 100;
	glColor3f(0.9f, 0.9f, 0.9f);

	glPushMatrix();
	glTranslatef(-4.f, 0, -z);
	glScaled(1, 0.7, 8);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(4.f, 0, -z);
	glScaled(1, 0.7, 8);
	glutSolidCube(1);
	glPopMatrix();

}

void renderScene(void) {


	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset transformations
	glLoadIdentity();

	// Set the camera
	gluLookAt(x, 7.0f, z,
		x + lx, 6.7f, z + lz,
		0, 0.1f, 0.0f);

	// Draw ground
	glColor3f(0.3f, 0.7f, 0.3f);
	glBegin(GL_QUADS);
	glVertex3f(-200.0f, 0.0f, -200.0f);
	glVertex3f(-200.0f, 0.0f, 200.0f);
	glVertex3f(200.0f, 0.0f, 200.0f);
	glVertex3f(200.0f, 0.0f, -200.0f);
	glEnd();

	//draw street
	glColor3f(0.2f, 0.2f, 0.2f);
	glPushMatrix();
	glScaled(24, 0.5, 400);
	glutSolidCube(1);
	glPopMatrix();


	// draw street lines

	draw_street_lines(street_lines_z);
	draw_street_lines(street_lines_z + 100);


	Car car(0, 0, 0, 3);
	car.drawCar();
	
	//glPushMatrix();
	//	glTranslatef(x, 1, z-10);
	//	drawSnowMan();
	//glPopMatrix();

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

	glClearColor(0.2f, 0.f, 1.0f, 0.7);


	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(processSpecialKeys);

	// OpenGL init
	glEnable(GL_DEPTH_TEST);

	angle -= 0.00f;
	lx = sin(angle);
	lz = -cos(angle);
	// enter GLUT event processing cycle
	glutMainLoop();


	return 1;
}

