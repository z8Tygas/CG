//VARS GLOB
//cam motion
	float cam_x = 10;
	float cam_y = 10;
	float cam_z = 10;
	float dx = -1;
	float dy = 0;
	float dz = 0;
	float alpha = 3 * M_PI_2;
	float beta = 0;
//mouse vars
	int oldx = 0;
	int oldy = 0;
//cam
	int enable_rotate = 0;
	int invert_cam = 1;
	int cam_sense = 250; //higher -> less sens

void renderScene(void) {
	// set the camera
	glLoadIdentity();
	gluLookAt(cam_x, cam_y, cam_z,
	      	  cam_x + dx, cam_y + dy, cam_z + dz,
		  0.0f,1.0f,0.0f);
}


// write function to process keyboard events

void interp_teclado(unsigned char key, int x, int y) {
	if (key == 'a') {
		cam_x += sin(alpha + M_PI_2) / k;
		cam_z += cos(alpha + M_PI_2) / k;
	}
	else if (key == 'd') {
		cam_x += sin(alpha - M_PI_2) / k;
		cam_z += cos(alpha - M_PI_2) / k;
	}
	else if (key == 'w') {
		cam_x += sin(alpha) / k;
		cam_z += cos(alpha) / k;
	}
	else if (key == 's') {
		cam_x -= sin(alpha) / k;
		cam_z -= cos(alpha) / k;
	}
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
	
	//RMB Controls
	if (button == 2 && state == GLUT_DOWN) {
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
		if (beta + vary > M_PI_2) {
			beta = M_PI_2 - 0.001;
		}
		else if (beta + vary < -M_PI_2) {
			beta = 0.001 - M_PI_2;
		}
		else {
			if (invert_cam) {
				beta += vary;
			}
			else {
				beta -= vary;
			}
		}
		
		dx = cos(beta) * sin(alpha);
		dy = sin(beta);
		dz = cos(beta) * cos(alpha);

		glutPostRedisplay();
	}
}



int main(int argc, char **argv) {	
// put here the registration of the keyboard callbacks
	glutKeyboardFunc(interp_teclado);
	glutSpecialFunc(interp_spec_teclado);
	glutMotionFunc(interp_rato_motion);
	glutMouseFunc(interp_rato_click);
}
