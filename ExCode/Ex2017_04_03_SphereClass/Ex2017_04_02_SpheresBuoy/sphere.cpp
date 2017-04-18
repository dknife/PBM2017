#include "sphere.h"

void sphere::setRadius(float _radius) {
	radius = _radius;
	mass = radius * radius * radius;
}

float sphere::getRadius(void) {
	return radius;
}

void sphere::setLocation(const vec3d& vec) {
	loc = vec;
}

vec3d sphere::getLocation(void) {
	return loc;
}

void sphere::setVelocity(const vec3d& vec) {
	vel = vec;
}

vec3d sphere::getVelocity(void) {
	return vel;
}

void sphere::setAcc(const vec3d& vec) {
	acc = vec;
}
vec3d sphere::getAcc(void) {
	return acc;
}

void sphere::addAcc(const vec3d& vec) {
	acc = acc + vec;
}

void sphere::initAcc(void) {
	acc.set(0, 0, 0);
}

void sphere::move(const vec3d& displacement) {
	loc = loc + displacement;	
}
// simulation
void sphere::simulate(float dt) {
	vel = vel + acc*dt;
	loc = loc + vel*dt;
}

void sphere::visualize(void) {
	glPushMatrix();
	glTranslatef(loc.x, loc.y, loc.z);
	glutWireSphere(radius, 20, 20);
	glPopMatrix();
}