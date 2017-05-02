#include "Hover.h"
#include "./GLUT/freeglut.h"
#pragma comment(lib, "freeglut.lib")

Hover::Hover() :
	loc(vec3d(0,0,0)),
	vel(vec3d(0,0,0)),
	acc(vec3d(0,0,0)),
	mass(1.0), I(1.0),
	angle(3.14/4.0), aVel(0), aAcc(0)
{
	engine[0] = false; engine[1] = true;
	force[0] = vec3d(0, 1, 0);
	force[1] = vec3d(0, 1, 0);
}

vec3d Hover::localToGlobal(vec3d l) {
	float c = cos(angle);
	float s = sin(angle);

	vec3d res(0, 0, 0);
	res.x = c*l.x - s*l.y;
	res.y = s*l.x + c*l.y;
	return res;
}

void Hover::simulate(float dt) {
	acc.set(0, 0, 0);

	for (int i = 0; i < 2; i++) {
		vec3d f = localToGlobal(force[i]);
		if (engine[i]) acc = acc + f / mass;
	}
	vel = vel + acc*dt;
	loc = loc + vel*dt;
}

void Hover::visualize() {

	float degree = angle*180.0 / 3.14;
	glPushMatrix();
	glTranslatef(loc[0], loc[1], loc[2]);
	glRotatef(degree, 0, 0, 1);
	glBegin(GL_QUADS);
	glVertex2f(-1, 1);
	glVertex2f(-1, -1);
	glVertex2f(1, -1);
	glVertex2f(1, 1);
	glEnd();
	glPopMatrix();
}