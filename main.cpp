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
//object draw mode
	int mode = 0;
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

void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window with zero width).
	if(h == 0)
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
	gluPerspective(45.0f ,ratio, 1.0f ,1000.0f);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}


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
// put the geometric transformations here

	glTranslatef(transx, 0.0f, transz);
	glRotatef(rotate, 0.0f, 1.0f, 0.0f);
	glScalef(1.0f, escala, 1.0f);


// put drawing instructions here
	if (!mode) 
		glPolygonMode(GL_FRONT, GL_FILL);
	else if (mode == 1)
		glPolygonMode(GL_FRONT, GL_LINE);
	else
		glPolygonMode(GL_FRONT, GL_POINT);

	glBegin(GL_TRIANGLES);
	//lados
	glColor3f(0.0f,0.3f,1.0f);
	glVertex3f(2.0f, 0.0f, 2.0f);
	glVertex3f(0.0f, 5.0f, 0.0f);
	glVertex3f(-2.0f, 0.0f, 2.0f);
	glColor3f(0.0f, 1.0f, 0.3f);
	glVertex3f(2.0f, 0.0f, -2.0f);
	glVertex3f(0.0f, 5.0f, 0.0f);
	glVertex3f(2.0f, 0.0f, 2.0f);;
	glColor3f(1.0f, 0.0f, 0.3f);
	glVertex3f(-2.0f, 0.0f, -2.0f);
	glVertex3f(0.0f, 5.0f, 0.0f);
	glVertex3f(2.0f, 0.0f, -2.0f);
	glColor3f(0.8f, 1.0f, 0.3f);
	glVertex3f(-2.0f, 0.0f, 2.0f);
	glVertex3f(0.0f, 5.0f, 0.0f);
	glVertex3f(-2.0f, 0.0f, -2.0f);
	//base
	glColor3f(0.4f, 0.4f, 0.4f);
	glVertex3f(-2.0f, 0.0f, 2.0f);
	glVertex3f(-2.0f, 0.0f, -2.0f);
	glVertex3f(2.0f, 0.0f, 2.0f);
	glVertex3f(-2.0f, 0.0f, -2.0f);
	glVertex3f(2.0f, 0.0f, -2.0f);
	glVertex3f(2.0f, 0.0f, 2.0f);
	glEnd();


	// End of frame
	glutSwapBuffers();
}



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
	else if (key == '+') {
		escala += 0.1f;
	}
	else if (key == '-') {
		escala -= 0.1f;
	}
	else if (key == 'f') {
		mode += 1;
		mode %= 3;
	}
	else if (key == 32) { // space bar
		rotate += 10;
		rotate %= 360;
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
