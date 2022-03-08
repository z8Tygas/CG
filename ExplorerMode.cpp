#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>

//VARS GLOB
//object trans rotate e scale
	float transx = 0;
	float transz = 0;
	float escala = 1;
	int rotate = 0;
//cam motion
	float camx = 20;
	float camy = 0;
	float camz = 0;
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

void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	gluLookAt(camx, camy, camz,
		      0.0,0.0,0.0,
			  0.0f,1.0f,0.0f);
	
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

// write function to process keyboard events

void interp_teclado(unsigned char key, int x, int y) {
	if (key == 'a') {
		transx -= 0.5f;
	}
	else if (key == 'd') {
		transx += 0.5f;
	}
	else if (key == 'w') {
		transz -= 0.5f;
	}
	else if (key == 's') {
		transz += 0.5f;
	}
	glutPostRedisplay();
}

void interp_rato_click(int button, int state, int x, int y) {
	//LMB Controls
	if (button == 0 && state == GLUT_DOWN) {
		enable_trans = 1;
		oldx = x;
		oldy = y;
	}
	else if (button == 0 && state == GLUT_UP) {
		enable_trans = 0;
	}
	//RMB Controls
	else if (button == 2 && state == GLUT_DOWN) {
		enable_rotate = 1;
		oldx = x;
		oldy = y;
	}
	else if (button == 2 && state == GLUT_UP) {
		enable_rotate = 0;
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

		camx = 20 * cos(beta) * sin(alpha);
		camz = 20 * cos(beta) * cos(alpha);
		camy = 20 * sin(beta);

		glutPostRedisplay();
	}
	else if (enable_trans) {

	}
}



int main(int argc, char **argv) {

// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(800,800);
	glutCreateWindow("CG@DI-UM");
		
// Required callback registry 
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);

	
// put here the registration of the keyboard callbacks
	glutKeyboardFunc(interp_teclado);
	glutMotionFunc(interp_rato_motion);
	glutMouseFunc(interp_rato_click);


//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glClearColor(0.3f, 0.5f, 0.8f, 1);
	
// enter GLUT's main cycle
	glutMainLoop();
	
	return 1;
}
