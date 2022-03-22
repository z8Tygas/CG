#define _USE_MATH_DEFINES
#include <math.h>
void drawCylinder(float radius, float height, int sides) {

	int i;
	float step;

	step = 360.0 / sides;

	glBegin(GL_TRIANGLES);

	// top
	for (i = 0; i < sides; i++) {
		glVertex3f(0, height * 0.5, 0);
		glVertex3f(cos(i * step * M_PI / 180.0) * radius, height * 0.5, -sin(i * step * M_PI / 180.0) * radius);
		glVertex3f(cos((i + 1) * step * M_PI / 180.0) * radius, height * 0.5, -sin((i + 1) * step * M_PI / 180.0) * radius);
	}

	// bottom
	for (i = 0; i < sides; i++) {
		glVertex3f(0, -height * 0.5, 0);
		glVertex3f(cos((i + 1) * step * M_PI / 180.0) * radius, -height * 0.5, -sin((i + 1) * step * M_PI / 180.0) * radius);
		glVertex3f(cos(i * step * M_PI / 180.0) * radius, -height * 0.5, -sin(i * step * M_PI / 180.0) * radius);
	}

	// body
	for (i = 0; i <= sides; i++) {

		glVertex3f(cos(i * step * M_PI / 180.0) * radius, height * 0.5, -sin(i * step * M_PI / 180.0) * radius);
		glVertex3f(cos(i * step * M_PI / 180.0) * radius, -height * 0.5, -sin(i * step * M_PI / 180.0) * radius);
		glVertex3f(cos((i + 1) * step * M_PI / 180.0) * radius, height * 0.5, -sin((i + 1) * step * M_PI / 180.0) * radius);

		glVertex3f(cos(i * step * M_PI / 180.0) * radius, -height * 0.5, -sin(i * step * M_PI / 180.0) * radius);
		glVertex3f(cos((i + 1) * step * M_PI / 180.0) * radius, -height * 0.5, -sin((i + 1) * step * M_PI / 180.0) * radius);
		glVertex3f(cos((i + 1) * step * M_PI / 180.0) * radius, height * 0.5, -sin((i + 1) * step * M_PI / 180.0) * radius);
	}
	glEnd();
}
