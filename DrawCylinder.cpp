#define _USE_MATH_DEFINES
#include <math.h>
void drawCylinder(float radius, float height, int slices) {
	float a = 0;
	float angle = 2*M_PI / slices;
	//draw bottom base
	for (int i = 0; i < slices; i++) {
		glBegin(GL_TRIANGLES);
		glColor3f(i%2, i%2, i%2);
		glVertex3f(0, 0, 0);
		glVertex3f(radius * sin(a + angle * (i+1)), 0, radius * cos(a + angle * (i+1)));
		glVertex3f(radius * sin(a + angle * i), 0, radius * cos(a + angle * i));
		glEnd();
	}
	//draw top base
	a = angle / 2;
	for (int i = 0; i < slices; i++) {
		glBegin(GL_TRIANGLES);
		glColor3f(i % 2, i % 2, i % 2);
		glVertex3f(0, height, 0);
		glVertex3f(radius * sin(a + angle * i), height, radius * cos(a + angle * i));
		glVertex3f(radius * sin(a + angle * (i + 1)), height, radius * cos(a + angle * (i + 1)));
		glEnd();
	}
	//draw sides
	a = 0;
	for (int i = 0; i < slices; i++) {
		glBegin(GL_TRIANGLES);
		// Bottom Up
		glColor3f(i % 2, i % 2, i % 2);
		glVertex3f(radius * sin(a + angle * i),				0, radius * cos(a + angle * i));
		glVertex3f(radius * sin(a + angle * (i+1)),			0, radius * cos(a + angle * (i + 1)));
		glVertex3f(radius * sin((a + angle / 2) + angle * i),	   height, radius * cos((a + angle / 2) + angle * i));
		// Top Down
		glColor3f(i % 2, i % 2, i % 2);
		glVertex3f(radius * sin((a + angle / 2) + angle * (i+1)), height , radius * cos((a + angle / 2) + angle * (i + 1)));
		glVertex3f(radius * sin((a + angle / 2) + angle * i),	  height , radius * cos((a + angle / 2) + angle * i));
		glVertex3f(radius * sin(a + angle * (i+1)),			0, radius * cos(a + angle * (i+1)));
		glEnd();
	}
}
