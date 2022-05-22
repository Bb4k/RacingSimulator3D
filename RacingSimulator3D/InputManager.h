#ifndef InputManager_H
#define InputManager_H
#include<gl/freeglut.h>
#include<math.h>

class InputManager
{	

	float lx, lz, angle;
	float x, z;

public:

	InputManager(float lx, float lz, float angle, float x, float z) {
		this->lx = lx;
		this->lz = lz;
		this->angle = angle;
		this->x = angle;
		this->z = angle;
	}

	void* processNormalKeys(unsigned char key, int x, int y)
	{

		switch (key) {
		case 'l':
			this->angle -= 0.01f;
			this->lx = sin(angle);
			this->lz = -cos(angle);
			break;

		}
		if (key == 27)
			exit(0);
	}

	void* processSpecialKeys(int key, int xx, int yy) {

		float fraction = 0.1f;

		switch (key) {
		case GLUT_KEY_LEFT:
			this->angle -= 0.01f;
			this->lx = sin(angle);
			this->lz = -cos(angle);
			break;
		case GLUT_KEY_RIGHT:
			this->angle += 0.01f;
			this->lx = sin(angle);
			this->lz = -cos(angle);
			break;
		case GLUT_KEY_UP:
			this->x += lx * fraction;
			this->z += lz * fraction;
			break;
		case GLUT_KEY_DOWN:
			this->x -= lx * fraction;
			this->z -= lz * fraction;
			break;
		}
	}
	float get_lx() {
		return this->lx;
	}
	float get_lz() {
		return this->lz;
	}
	float get_angle() {
		return this->angle;
	}
	float get_x() {
		return this->x;
	}
	float get_y() {
		return this->z;
	}

	void process_norm_keys(InputManager im) {
		glutKeyboardFunc(&im->((void)processNormalKeys));
	}

};

#endif

