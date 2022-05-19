//SURSA:  lighthouse3D:  http://www.lighthouse3d.com/tutorials/glut-tutorial/keyboard-example-moving-around-the-world/ 

#include<gl/freeglut.h>
#include<math.h>
#include <iostream>

#include "Car.h"
#include "Background.h"

// angle of rotation for the camera direction
float angle = 0.0f;
// actual vector representing the camera's direction
float lx = 20.0f, lz = -1.0f;
// XZ position of the camera
float x = 0.0f, z = 0.0f;

float street_lines_z = 100;

//grid lines for lanes
#define GRID_LEFT -8.0f
#define GRID_MID 0.0f
#define GRID_RIGHT 8.0f


//car instance
Car car(15, 1, 0, 5);
int contor_z = 0;
int car_nfs_slowmo_ = 0;
GLfloat car_rot = 0.0;
GLfloat car_rot_max = 0.0;

Car car_left_lane(-50, 1, -8, 5);
Car car_mid_lane(-50, 1, 0, 5);
Car car_right_lane(-50, 1, 8, 5);

void changeSize(int w, int h)
{

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;
	float ratio = (float)(w * 1.0f / h);

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

void go_left(void) {
	if ((float)car.get_pos_Z() > GRID_LEFT) {
		std::cout << (GLfloat)car.get_pos_Z() << " " << GRID_LEFT << std::endl;
		car.change_lane((GLfloat)(-.5f) - (GLfloat)0.05 * (GLfloat)car_nfs_slowmo_);
		angle += 0.005;
		lx = sin(angle);
		lz = -cos(angle);
		x -= 0.5f;
		if (car.get_pos_Z() > GRID_LEFT / 2 && car.get_pos_Z() < GRID_MID)
			car_rot -= contor_z;

		if (car.get_pos_Z() < GRID_LEFT / 2)
			car_rot += contor_z;

		if (car.get_pos_Z() > GRID_MID && car.get_pos_Z() < GRID_RIGHT / 2)
			car_rot += contor_z;

		if (car.get_pos_Z() > GRID_RIGHT / 2)
			car_rot -= contor_z;
	}
	glutPostRedisplay();
}

void go_right(void) {
	if ((float)car.get_pos_Z() < GRID_RIGHT) {
		std::cout << (float)car.get_pos_Z() << " " << GRID_RIGHT << std::endl;
		car.change_lane((GLfloat)(.5f) - (GLfloat)0.05 * (GLfloat)car_nfs_slowmo_);
		angle -= 0.005;
		lx = sin(angle);
		lz = -cos(angle);
		x += 0.5f;
		if (car.get_pos_Z() > GRID_LEFT / 2 && car.get_pos_Z() < GRID_MID)
			car_rot += contor_z;

		if (car.get_pos_Z() < GRID_LEFT / 2)
			car_rot -= contor_z;

		if (car.get_pos_Z() > GRID_MID && car.get_pos_Z() < GRID_RIGHT / 2)
			car_rot -= contor_z;

		if (car.get_pos_Z() > GRID_RIGHT / 2)
			car_rot += contor_z;
	}
	glutPostRedisplay();
}

void renderScene(void) {


	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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
		bg.drawGround(.7, .6, .6, 200, 0);
		bg.drawStreet(0.2, 0.2, 0.2, 24, 0.5, 400, 1);
		bg.drawStreetLines(street_lines_z);

		std::cout << "DIFF LEFT MID: " << abs(car.get_pos_Z() - GRID_MID) << " " << std::numeric_limits<float>::epsilon() << std::endl;

		
		if (((car.get_pos_Z() != (GLfloat)GRID_LEFT) && (car.get_pos_Z() != (GLfloat)GRID_MID)) && contor_z == -1) 
			go_left();
	
		if (((car.get_pos_Z() != (GLfloat)GRID_RIGHT) && (car.get_pos_Z() != (GLfloat)GRID_MID)) && contor_z == 1) 
			go_right();
		
		if (car.get_pos_Z() == GRID_LEFT || car.get_pos_Z() == GRID_MID || car.get_pos_Z() == GRID_RIGHT) {
			car_rot = 0;
			if (car.get_pos_Z() == GRID_MID)
				contor_z = 0;
		}




	glPushMatrix();
		glRotatef(90+car_rot, 0, 1, 0);
		car.drawCar();
	glPopMatrix();

	glPushMatrix();
		glRotatef(-90, 0, 1, 0);
		car_left_lane.drawCar();
		car_left_lane.incr_posX(.1f);
	glPopMatrix();

	glPushMatrix();
	glRotatef(-90, 0, 1, 0);
		car_mid_lane.drawCar();
		car_mid_lane.incr_posX(.1f);
	glPopMatrix();

	glPushMatrix();
	glRotatef(-90, 0, 1, 0);
		car_right_lane.drawCar();
		car_right_lane.incr_posX(.1f);
	glPopMatrix();
	 
	//glPushMatrix();
	//	glTranslatef(x, 1, z-10);
	//	drawSnowMan();
	//glPopMatrix();
	glutPostRedisplay();
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
	glutPostRedisplay();
}



void processSpecialKeys(int key, int xx, int yy) {

	float fraction = 0.1f;

	switch (key) {
	/*case GLUT_KEY_CTRL_R:
		car_nfs_slowmo_ = 1;*/
	case GLUT_KEY_LEFT:
		if (contor_z == 0 || contor_z == 1) {
			
		}
		contor_z = -1;
		go_left();
		
		break;
	case GLUT_KEY_RIGHT:
		if (contor_z == 0 || contor_z == -1) {
			
		}
		contor_z = 1;
		go_right();
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
	glutPostRedisplay();
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

	glClearColor(0.2f, .8f, 1.0f, 0.7);


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

