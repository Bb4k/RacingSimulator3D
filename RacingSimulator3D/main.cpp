//SURSA:  lighthouse3D:  http://www.lighthouse3d.com/tutorials/glut-tutorial/keyboard-example-moving-around-the-world/ 



#include <math.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <tuple>

#include <GL/freeglut.h>

#include "Car.h"
#include "Background.h"

// angle of rotation for the camera direction
float angle = 0.0f;
// actual vector representing the camera's direction
float lx = 20.0f, lz = -1.0f;
// XZ position of the camera
float x = 0.0f, z = 0.0f;

float street_lines_z = 65;

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

//incoming car
int car_incoming_pos_val[3] = {
		GRID_LEFT,
		GRID_MID,
		GRID_RIGHT
};

std::vector<std::tuple<Car, Car>> incoming_cars[6];

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
		angle += 0.008;
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
		angle -= 0.008;
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

void player_car() {

	glPushMatrix();
	glRotatef(90 + car_rot, 0, 1, 0);
	car.drawCar();
	glPopMatrix();

	if (((car.get_pos_Z() != (GLfloat)GRID_LEFT) && (car.get_pos_Z() != (GLfloat)GRID_MID)) && contor_z == -1)
		go_left();

	if (((car.get_pos_Z() != (GLfloat)GRID_RIGHT) && (car.get_pos_Z() != (GLfloat)GRID_MID)) && contor_z == 1)
		go_right();

	if (car.get_pos_Z() == GRID_LEFT || car.get_pos_Z() == GRID_MID || car.get_pos_Z() == GRID_RIGHT) {
		car_rot = 0;
		if (car.get_pos_Z() == GRID_MID)
			contor_z = 0;
	}
}

std::tuple <Car, Car> generate_incoming_cars() {
	struct cars {
		Car car_1;
		Car car_2;
	};

	Car car_1((-(float)(rand() % 100 + 100)), (float)1, (float)car_incoming_pos_val[rand() % 3], (float)5);
	Car car_2((-(float)(rand() % 100 + 100)), (float)1, (float)car_incoming_pos_val[rand() % 3], (float)5);


	return { car_1, car_2 };
}

void incoming() {

	if (incoming_cars->empty()) {
		std::tuple<Car, Car> cars = generate_incoming_cars();
		incoming_cars->emplace_back(cars);
	}

	if (std::get<0>(incoming_cars->back()).get_pos_X() > -10 || std::get<1>(incoming_cars->back()).get_pos_X() > -10) {
		std::tuple<Car, Car> cars = generate_incoming_cars();
		incoming_cars->emplace_back(cars);
	}

	if (std::get<0>(incoming_cars->back()).get_pos_X() > 0 || std::get<1>(incoming_cars->back()).get_pos_X() > 0) {
		incoming_cars->pop_back();
	}


	for (int i = 0; i < incoming_cars->size(); ++i) {

		std::cout << i << " " << std::get<0>(incoming_cars->at(i)).get_pos_Z() << " " << std::get<1>(incoming_cars->at(0)).get_pos_Z();
		(std::get<1>(incoming_cars->at(i))).incr_posX(2);
		(std::get<0>(incoming_cars->at(i))).incr_posX(2);

		glPushMatrix();
		glRotatef(-90, 0, 1, 0);
		(std::get<0>(incoming_cars->at(i))).drawCar();
		glPopMatrix();

		glPushMatrix();
		glRotatef(-90, 0, 1, 0);
		(std::get<1>(incoming_cars->at(i))).drawCar();
		glPopMatrix();

	}



}

void draw_env() {


	Background bg;
	bg.drawSun();
	bg.drawGround(.7, .6, .6, 200, 0);
	bg.drawStreet(0.2, 0.2, 0.2, 24, 0.5, 400, 1);
	bg.drawStreetLines(street_lines_z);

}

void renderScene(void) {


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	//			x		y		z
	gluLookAt(x, 7.0f, z,			//eye
		x + lx, 6.7f, z + lz,		//center
		0, 0.1f, 0.0f);		//up



	draw_env();
	player_car();
	incoming();




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
	srand(time(NULL));
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(1024, 768);
	glutCreateWindow("Scena 3D cu oameni de zapada");

	// register callbacks
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);

	glClearColor(0.45f, .177f, 1.0f, 0.873);


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

