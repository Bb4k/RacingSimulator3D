#ifndef Car_H
#define Car_H

#include<GL/freeglut.h>

class Car {

public:
	float positionX;
	float positionY;
	GLfloat positionZ;
	float dimension;

	Car(float positionX, float positionY, float positionZ, float dimension) {
		this->positionX = positionX;
		this->positionY = positionY;
		this->positionZ = positionZ;
		this->dimension = dimension;
	}

	GLfloat get_pos_Z() {
		return this->positionZ;
	}
	void incr_posZ(GLfloat val) {
		this->positionZ += (GLfloat)val;
	}

	void change_lane(GLfloat direction) {
		this->incr_posZ(direction);
	}

	void incr_posX(GLfloat val) {
		this->positionX += (GLfloat)val;
	}

	void drawCar() {

		//float dimension = 3.0f;
		float carW = this->dimension / 2.0f;
		float carH = this->dimension / 5.0f;
		float wheelR = this->dimension / 10.0f;
		float wheelW = this->dimension / 8.0f;
		float spoilerH = this->dimension / 20.0f;
		float spoilerPillarW = spoilerH / 2.5f;
		float spoilerPillarH = spoilerH;


		glTranslatef(this->positionX, this->positionY, this->positionZ);
		glColor3f(1.0f, 0, 0);

		// Draw Base
		glPushMatrix();
		glTranslated(0, wheelR + carH / 2, 0);
		glScaled(1.0, 0.2, 0.5);
		glutWireCube(this->dimension);
		glPopMatrix();

		// Draw Spoiler
		glPushMatrix();
		glTranslatef(-this->dimension / 2 + spoilerH / 2, wheelR + carH + spoilerPillarH, 0.0f);
		glScaled(1.3, spoilerPillarH, (carW / spoilerH) * 1.2);
		glutWireCube(spoilerH);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-this->dimension / 2 + spoilerH / 2, wheelR + carH + spoilerH / 2, carW / 4);
		glScaled(1, 1, spoilerPillarW);
		glutWireCube(spoilerH);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-this->dimension / 2 + spoilerH / 2, wheelR + carH + spoilerH / 2, -carW / 4);
		glScaled(1, 1, spoilerPillarW);
		glutWireCube(spoilerH);
		glPopMatrix();

		//Draw Wheels
		glPushMatrix();
		glTranslatef(this->dimension / 4, wheelR, carW / 2.0f);
		glScaled(1, 1, 1.7);
		glutWireTorus(wheelR / 2, wheelR / 2, 40, 20);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-this->dimension / 4, wheelR, carW / 2.0f);
		glScaled(1, 1, 1.7);
		glutWireTorus(wheelR / 2, wheelR / 2, 40, 20);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(this->dimension / 4, wheelR, -carW / 2.0f);
		glScaled(1, 1, 1.7);
		glutWireTorus(wheelR / 2, wheelR / 2, 40, 20);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-this->dimension / 4, wheelR, -carW / 2.0f);
		glScaled(1, 1, 1.7);
		glutWireTorus(wheelR / 2, wheelR / 2, 40, 20);
		glPopMatrix();

	}


};

#endif