#include "sphere.h"

void sphere::setRadius(float _radius) {
	radius = _radius;
}

float sphere::getRadius(void) {
	return radius;
}

void sphere::setLocation(const vec3d& vec) {
	center = vec;
}

vec3d sphere::getLocation(void) {
	return vec3d(center.x, center.y, center.z);
}

void sphere::visualize(void) {
	glPushMatrix();
	glTranslatef(center.x, center.y, center.z);
	glutWireSphere(radius, 20, 20);
	glPopMatrix();
}