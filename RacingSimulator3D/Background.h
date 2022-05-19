#ifndef Background_H
#define Background_H

#include<GL/freeglut.h>


class Background {

public:

	void drawGround(GLfloat r, GLfloat g, GLfloat b, GLfloat size, GLfloat y) {

		glColor3f(r, g, b);
		glBegin(GL_QUADS);
			glVertex3f(-size, 0.0f, -size);
			glVertex3f(-size, 0.0f, size);
			glVertex3f(size, 0.0f, size);
			glVertex3f(size, 0.0f, -size);
		glEnd();

		
	}

	void drawStreet(GLfloat r, GLfloat g, GLfloat b, GLfloat scale_x, GLfloat scale_y, GLfloat scale_z, double size) {

		//draw street
		glColor3f(r, g, b);
		glPushMatrix();
			glScaled(scale_x, scale_y, scale_z);
			glutSolidCube(size);
		glPopMatrix();

		glPushMatrix();
			glColor3f(0.6, 0.6, 0.6);
			glTranslated(-scale_x/2-.99f, 0, 0);
			glScaled(1, scale_y+3, scale_z);
			glutSolidCube(1);
		glPopMatrix();

		glPushMatrix();
			glColor3f(0.6, 0.6, 0.6);
			glTranslated(scale_x / 2 + .99f, 0, 0);
			glScaled(1, scale_y + 3, scale_z);
			glutSolidCube(1);
		glPopMatrix();

	}

	void drawStreetLines(float street_lines_z) {
		street_lines_z -= .1;

		if (street_lines_z < -100)
			street_lines_z = 100;
		glColor3f(0.9f, 0.9f, 0.9f);

		glPushMatrix();
		glTranslatef(-4.f, 0, -street_lines_z);
		glScaled(1, 0.7, 8);
		glutSolidCube(1);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(4.f, 0, -street_lines_z);
		glScaled(1, 0.7, 8);
		glutSolidCube(1);
		glPopMatrix();
	}

};

#endif