#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>


//VARS GLOB
//object trans rotate e scale
float trans_x = 0;
float trans_z = 0;
float escala = 1;
int rotate = 0;
//object draw mode
int mode = 1;
//cam motion
float cam_x = 20;
float cam_y = 0;
float cam_z = 0;
float cam_center_x = 0;
float cam_center_y = 0;
float cam_center_z = 0;
float alpha = M_PI_2;
float beta = 0;
//mouse vars
int oldx = 0;
int oldy = 0;
//cam
int enable_rotate = 0;
int enable_trans = 0;
int invert_cam = 1;
int cam_sense = 250; //higher -> less sens

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
	gluLookAt(cam_x, cam_y, cam_z,
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
	glEnd();
	// put the geometric transformations here

	glTranslatef(trans_x, 0.0f, trans_z);
	glRotatef(rotate, 0.0f, 1.0f, 0.0f);
	glScalef(1.0f, escala, 1.0f);


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

void interp_teclado(unsigned char key, int x, int y) {
	if (key == '+') {
		escala += 0.1f;
	}
	else if (key == '-') {
		escala -= 0.1f;
	}
	else if (key == 'f') {
		mode += 1;
		mode %= 3;
	}
	else if (key == 'r') {
		rotate += 10;
		rotate %= 360;
	}
	glutPostRedisplay();
}

void interp_spec_teclado(int key, int x, int y) {
	if (key == GLUT_KEY_LEFT) {
		trans_x -= 0.5f;
	}
	else if (key == GLUT_KEY_RIGHT) {
		trans_x += 0.5f;
	}
	else if (key == GLUT_KEY_UP) {
		trans_z -= 0.5f;
	}
	else if (key == GLUT_KEY_DOWN) {
		trans_z += 0.5f;
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

		cam_x = 20 * cos(beta) * sin(alpha);
		cam_z = 20 * cos(beta) * cos(alpha);
		cam_y = 20 * sin(beta);

		glutPostRedisplay();
	}
	else if (enable_trans) {
		float varx = oldx - x;
		float varz = oldy - y;
		oldx = x;
		oldy = y;

		varx /= cam_sense;
		varz /= cam_sense;

		cam_x += varx;
		cam_z += varz;
		cam_center_x += varx;
		cam_center_z += varz;

		glutPostRedisplay();
	}
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
	glutKeyboardFunc(interp_teclado);
	glutSpecialFunc(interp_spec_teclado);
	glutMotionFunc(interp_rato_motion);
	glutMouseFunc(interp_rato_click);


	//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	// enter GLUT's main cycle
	glutMainLoop();

	return 1;
}
