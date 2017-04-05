#ifndef SPHERE_YMKANG
#define SPHERE_YMKANG

#include "./GLUT/freeglut.h"
#include "vec3d.h"

class sphere {
	float radius;
	vec3d center;

public:
	sphere() {}
	sphere(const vec3d& _center, float _radius) : center(_center), radius(_radius) {}

	void setRadius(float _radius);
	float getRadius(void);
	void setLocation(const vec3d& vec);
	vec3d getLocation(void);

	void visualize(void);
};
#endif