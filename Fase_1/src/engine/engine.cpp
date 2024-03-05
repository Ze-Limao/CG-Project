#include <stdlib.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "math.h"
#include <iostream>

#include "../utils/figure.hpp"
#include "config.hpp"

#define RED 1.0f,0.0f,0.0f
#define GREEN 0.0f,1.0f,0.0f
#define BLUE 0.0f,0.0f,1.0f
#define YELLOW 1.0f, 1.0f, 0.0f
#define CYAN 0.0f, 1.0f, 1.0f
#define WHITE 1.0f, 1.0f, 1.0f

float alpha = PI / 4;
float beta_ = PI / 4;
float radius = 5.0f;
float camx = 5.0f;
float camy = 5.0f;
float camz = 5.0f;
float lookAtx = 0.0f;
float lookAty = 0.0f;
float lookAtz = 0.0f;
float upx = 0.0f;
float upy = 0.0f;
float upz = 0.0f;

int mode = GL_LINE;

std::vector<Figure*> figures;

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

void drawFiguras() {
	for (Figure* f : figures) {
		for (Point p : f->points) {
			glVertex3d(p.x, p.y, p.z);
		}
	}
}

void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	gluLookAt(radius * cos(beta_) * sin(alpha), radius * sin(beta_), radius * cos(beta_) * cos(alpha),
		lookAtx, lookAty, lookAtz,
		upx, upy, upz);

	// put drawing instructions here
	// linhas dos eixos
	glBegin(GL_LINES);
	// X axis in red
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-100.0f, 0.0f, 0.0f);
	glVertex3f(100.0f, 0.0f, 0.0f);
	// Y Axis in Green
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, -100.0f, 0.0f);
	glVertex3f(0.0f, 100.0f, 0.0f);
	// Z Axis in Blue
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, -100.0f);
	glVertex3f(0.0f, 0.0f, 100.0f);
	glEnd();

	glColor3f(1.0f, 1.0f, 1.0f);
	// put the geometric transformations here
	// ...
	//

	// figuras
	glPolygonMode(GL_FRONT_AND_BACK, mode);
	glBegin(GL_TRIANGLES);
	drawFiguras();
	glEnd();

	// End of frame
	glutSwapBuffers();
}

// altera a posição da camera, para debug.
void specKeyProc(int key_code, int x, int y) {
	x = y; y = x;
	switch (key_code) {
	case GLUT_KEY_UP: {
		radius -= 0.1f;
		break;
	}

	case GLUT_KEY_DOWN: {
		radius += 0.1f;
		break;
	}

	default:
		break;
	}
	glutPostRedisplay();
}

// altera a posição da camera, para debug, e altera os modes para GL_FILL, GL_LINES, GL_POINT
void keyProc(unsigned char key, int x, int y) {
	x = y; y = x;
	switch (key)
	{
	case 'a': { // left
		alpha -= 0.1f;
		break;
	}

	case 'd': { // right
		alpha += 0.1f;
		break;
	}

	case 'w': { // up 
		beta_ += beta_ <= 1.48f ? 0.1f : 0.0f;
		break;
	}

	case 's': { // down
		beta_ -= beta_ >= -1.48f ? 0.1f : 0.0f;
		break;
	}

	case('f'):
		mode = GL_FILL;
		break;

	case('l'):
		mode = GL_LINE;
		break;

	case('p'):
		mode = GL_POINT;
		break;

	default:
		break;
	}
	glutPostRedisplay();
}


int main(int argc, char* argv[]) {

	if (argc < 2) {
		std::cerr << "Usage: " << argv[0] << " <file_path>" << std::endl;
		return 1;
	}

	Config c = Config(argv[1]);

	for (unsigned int i = 0; i < c.models.size(); i++) {
		std::cout << c.models.at(i) << std::endl;
		Figure* f = Figure::from_file(c.models.at(i));
		std::cout << f->get_type() << std::endl;
		figures.push_back(f);
	}

	camx = c.get_x_pos_cam();
	camy = c.get_y_pos_cam();
	camz = c.get_z_pos_cam();

	radius = sqrt(camx * camx + camy * camy + camz * camz);

	lookAtx = c.get_x_look_at();
	lookAty = c.get_y_look_at();
	lookAtz = c.get_z_look_at();

	upx = c.get_x_up();
	upy = c.get_y_up();
	upz = c.get_z_up();

	alpha = acos(camz / sqrt(camx * camx + camz * camz));
	beta_ = asin(camy / radius);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 800);
	glutCreateWindow("Fase 1");

	// Required callback registry 
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);

	// put here the registration of the keyboard callbacks (por enquanto só mexem na camara como forma de debug)
	glutKeyboardFunc(keyProc);
	glutSpecialFunc(specKeyProc);

	// OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	// enter GLUT's main cycle
	glutMainLoop();

	for (auto& ptr : figures) {
		delete ptr;
	}
	figures.clear();

	return 1;
}