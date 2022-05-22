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
			glColor3f((GLfloat)0.6f, (GLfloat)0.6f, (GLfloat)0.6f);
			glTranslated(-scale_x/2-.99f, 0, 0);
			glScaled(1, scale_y+3, scale_z);
			glutSolidCube(1);
		glPopMatrix();

		glPushMatrix();
			glColor3f((GLfloat)0.6f, (GLfloat)0.6f, (GLfloat)0.6f);
			glTranslated(scale_x / 2 + .99f, 0, 0);
			glScaled(1, scale_y + 3, scale_z);
			glutSolidCube(1);
		glPopMatrix();

	}

	void drawStreetLines(float street_lines_z) {
	
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

	void drawSun() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		/* ------------------------------------------------------------- */
		float purple[] = { 0.454f, 0.177f, 0.873f, 1.0f };
		float pink[] = { 0.8f, 0.177f, 0.6f, 0.1f };
		float orange[] = { 0.812f, 0.523f, 0.245f };
		float white[] = { 0.6, 0.6, 0.6, 0.8 };
		float low_shininess[] = { 5.0f };
		/* ------------------------------------------------------------- */
		GLfloat ambient[] = { 0.0f, 0.0f, 0.0f, 0.8f };
		GLfloat diffuse[] = { 1.0f, 1.0f, 1.0f, 0.1f };
		GLfloat specular[] = { 0.1f, 0.1f, 0.1f, 0.1f };
		GLfloat position[] = { 0.0f, 40.0f, -40.0f, 1.0f };
		/* ------------------------------------------------------------- */
		glLightfv(GL_LIGHT0, GL_DIFFUSE, purple);
		glLightfv(GL_LIGHT0, GL_POSITION, position);

		GLfloat model_ambient[] = { 0.4f, 0.4f, 0.4f, 1.0f };
		int model_two_side = 1;
		int viewpoint = 0;

		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, purple);
		glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, viewpoint);
		glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 1);

		glEnable(GL_LIGHT0);
		glEnable(GL_LIGHTING);

		glPushMatrix();
		glMaterialfv(GL_FRONT, GL_EMISSION, orange);
		glTranslatef(10, 10, -110);
		glutSolidSphere(20, 50, 50);
		glMaterialfv(GL_FRONT, GL_EMISSION, new GLfloat[3]{ 0, 0, 0 });
		glPopMatrix();

		glPushMatrix();
		glMaterialfv(GL_FRONT, GL_EMISSION, pink);
		glTranslatef(10, 8, -60);
		glutSolidSphere(3, 50, 50);
		glMaterialfv(GL_FRONT, GL_EMISSION, new GLfloat[3]{ 0, 0, 0 });
		glPopMatrix();

		glFlush();
	}

};

#endif