#include "Hover.h"
#include "./GLUT/freeglut.h"
#pragma comment(lib, "freeglut.lib")

Hover::Hover() :
	loc(vec3d(0,0,0)),
	vel(vec3d(0,0,0)),
	acc(vec3d(0,0,0)),
	mass(1.0)
{


}
void Hover::simulate(float dt) {

}
void Hover::visualize() {
	glBegin(GL_QUADS);
	glVertex2f(-1, 1);
	glVertex2f(-1, -1);
	glVertex2f(1, -1);
	glVertex2f(1, 1);
	glEnd();
}