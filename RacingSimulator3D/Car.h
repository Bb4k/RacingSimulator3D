#ifndef Car_H
#define Car_H

#include<GL/freeglut.h>

class Car {

public:
	float positionX;
	float positionY;
	float positionZ;
	float dimension;

	Car(float positionX, float positionY, float positionZ, float dimension) {
		this->positionX = positionX;
		this->positionY = positionY;
		this->positionZ = positionZ;
		this->dimension = dimension;
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
		float cabinBaseR = this->dimension / 2.82842712475f;
		float cabinTopR = this->dimension / 3.46410161514f;
		float cabinH = this->dimension / 4.0f;

		glTranslatef(this->positionX, this->positionY, this->positionZ);
		glRotatef(90, 0, 1, 0);

		
		// Draw Base
		glColor3f(1.0f, 0, 1.0f);
		glPushMatrix();
		glTranslated(0, wheelR + carH / 2, 0);
		glScaled(1.0, 0.2, 0.5);
		glutSolidCube(this->dimension);
		glPopMatrix();


		// Draw cabin
		glPushMatrix();
		glTranslated(0, wheelR + carH, 0);
		glScaled(1, 1, 1);
		GLUquadricObj* quadratic;
		quadratic = gluNewQuadric();
		glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
		glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
		glRotatef(45.0f, 0.0f, 0.0f, 1.0f);
		gluCylinder(quadratic, cabinBaseR, cabinTopR, cabinH, 4, 4);
		glPopMatrix();

		
		// Draw Spoiler
		glColor3f(0.0f, 0.0f, 0.0f);
		glPushMatrix();
		glTranslatef(-this->dimension / 2 + spoilerH / 2, wheelR + carH + spoilerPillarH, 0.0f);
		glScaled(1.3, spoilerPillarH, (carW / spoilerH) * 1.2);
		glutSolidCube(spoilerH);
		glPopMatrix();

		glColor3f(1.0f, 1.0f, 1.0f);
		glPushMatrix();
		glTranslatef(-this->dimension / 2 + spoilerH / 2, wheelR + carH + spoilerH / 2, carW / 4);
		glScaled(1, 1, spoilerPillarW);
		glutSolidCube(spoilerH);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-this->dimension / 2 + spoilerH / 2, wheelR + carH + spoilerH / 2, -carW / 4);
		glScaled(1, 1, spoilerPillarW);
		glutSolidCube(spoilerH);
		glPopMatrix();

		//Draw Wheels
		glColor3f(0.0f, 0.0f, 0.0f);
		glPushMatrix();
		glTranslatef(this->dimension / 4, wheelR, carW / 2.0f);
		glScaled(1, 1, 1.7);
		glutSolidTorus(wheelR / 2, wheelR / 2, 40, 20);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-this->dimension / 4, wheelR, carW / 2.0f);
		glScaled(1, 1, 1.7);
		glutSolidTorus(wheelR / 2, wheelR / 2, 40, 20);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(this->dimension / 4, wheelR, -carW / 2.0f);
		glScaled(1, 1, 1.7);
		glutSolidTorus(wheelR / 2, wheelR / 2, 40, 20);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-this->dimension / 4, wheelR, -carW / 2.0f);
		glScaled(1, 1, 1.7);
		glutSolidTorus(wheelR / 2, wheelR / 2, 40, 20);
		glPopMatrix();
	}


};

#endif