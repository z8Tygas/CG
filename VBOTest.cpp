#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>

#include <vector>

using namespace std;


// VARS GLOB
// Object draw mode
int mode = 1;
// Cam Motion
float camX = 10;
float camY = 10;
float camZ = 10;
float radius = sqrt(pow(camX, 2) + pow(camY, 2) + pow(camZ, 2));
float beta = asin(camY / radius);
float alpha = asin(camX / (radius * cos(beta)));
float cam_center_x = 0;
float cam_center_y = 0;
float cam_center_z = 0;
// Mouse Vars
int oldx = 0;
int oldy = 0;
// Cam Settings
int enable_rotate = 0;
int enable_trans = 0;
int invert_cam = 1;
int cam_sense = 250; //higher -> less sens
// VBOs
GLuint vertices, verticeCount;

void prepareData() {
	// Criar um vector com as coordenadas dos pontos
	vector<float> p;
	// Ponto 1
	p.push_back(0.0f);
	p.push_back(0.0f);
	p.push_back(0.0f);
	// Ponto 2
	p.push_back(0.0f);
	p.push_back(1.0f);
	p.push_back(0.0f);
	// Ponto 3
	p.push_back(0.0f);
	p.push_back(0.0f);
	p.push_back(1.0f);

	verticeCount = p.size() / 3;
	
	// Criar o VBO
	glGenBuffers(1, &vertices);
	
	// Copiar o vector para a memória gráfica
	glBindBuffer(GL_ARRAY_BUFFER, vertices);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * p.size(), p.data(), GL_STATIC_DRAW);
}


void spherical2Cartesian() {
	camX = radius * cos(beta) * sin(alpha);
	camZ = radius * cos(beta) * cos(alpha);
	camY = radius * sin(beta);
}

void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window with zero width).
	if (h == 0)
		h = 1;

	// compute window's aspect ratio 
	float ratio = w * 1.0 / h;

	// Set the projection matrix as current
	glMatrixMode(GL_PROJECTION);
	// Load Identity Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set perspective
	gluPerspective(45.0f, ratio, 1.0f, 1000.0f);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}

void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	gluLookAt(camX, camY, camZ,
		cam_center_x, cam_center_y, cam_center_z,
		0.0f, 1.0f, 0.0f);

	//axis
	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 100.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 100.0f, 0.0f);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(100.0f, 0.0f, 0.0f);
	glColor3f(1.0f, 1.0f, 1.0f);
	glEnd();

	// put drawing instructions here
	if (!mode)
		glPolygonMode(GL_FRONT, GL_FILL);
	else if (mode == 1)
		glPolygonMode(GL_FRONT, GL_LINE);
	else
		glPolygonMode(GL_FRONT, GL_POINT);

	

	// End of frame
	glutSwapBuffers();
}


// write function to process keyboard events

void interpTeclado(unsigned char key, int x, int y) {
	x = y; // to fix unused -Wall -Werror block
	y = x; // to fix unused -Wall -Werror block
	if (key == '+') {
		radius -= 0.1f;
		spherical2Cartesian();
	}
	else if (key == '-') {
		radius += 0.1f;
		spherical2Cartesian();
	}
	else if (key == 'f') {
		mode += 1;
		mode %= 3;
	}
	glutPostRedisplay();
}


void interp_rato_click(int button, int state, int x, int y) {
	//LMB Controls
	if (button == 0 && state == GLUT_DOWN) {
		enable_rotate = 1;
		oldx = x;
		oldy = y;
	}
	else if (button == 0 && state == GLUT_UP) {
		enable_rotate = 0;
	}
	//RMB Controls
	else if (button == 2 && state == GLUT_DOWN) {
		enable_trans = 1;
		oldx = x;
		oldy = y;
	}
	else if (button == 2 && state == GLUT_UP) {
		enable_trans = 0;
	}
}

void interp_rato_motion(int x, int y) {
	if (enable_rotate) {
		float varx = oldx - x;
		float vary = oldy - y;
		oldx = x;
		oldy = y;

		varx /= cam_sense;
		vary /= cam_sense;
		alpha += varx;
		if (invert_cam) {
			beta -= vary;
		}
		else {
			beta += vary;
		}

		spherical2Cartesian();

		glutPostRedisplay();
	}
	else if (enable_trans) {
		float varx = oldx - x;
		float varz = oldy - y;
		oldx = x;
		oldy = y;

		varx /= cam_sense;
		varz /= cam_sense;

		camX += varx;
		camZ += varz;
		cam_center_x += varx;
		cam_center_z += varz;

		glutPostRedisplay();
	}
}


void printInfo() {

	printf("Vendor: %s\n", glGetString(GL_VENDOR));
	printf("Renderer: %s\n", glGetString(GL_RENDERER));
	printf("Version: %s\n", glGetString(GL_VERSION));
}


int main(int argc, char** argv) {

	// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 800);
	glutCreateWindow("PROJETO CG");

	// Required callback registry 
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);


	// put here the registration of the keyboard callbacks
	glutKeyboardFunc(interpTeclado);
	glutMotionFunc(interp_rato_motion);
	glutMouseFunc(interp_rato_click);

	// init GLEW
#ifndef __APPLE__
	glewInit();
#endif


	//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnableClientState(GL_VERTEX_ARRAY);

	printInfo();
	prepareData();

	// enter GLUT's main cycle
	glutMainLoop();

	return 1;
}
