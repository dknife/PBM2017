#ifndef SPHERE_YMKANG
#define SPHERE_YMKANG

#include "./GLUT/freeglut.h"
#include "vec3d.h"

class sphere {
	float radius;
	vec3d center;
	vec3d velocity;
	vec3d acceleration;

	vec3d pVel;
	vec3d pAcc;

public:
	sphere() {}
	sphere(const vec3d& _center, float _radius) : center(_center), radius(_radius) {}

	void setRadius(float _radius);
	float getRadius(void);

	void setLocation(const vec3d& vec);
	vec3d getLocation(void);

	void setVelocity(const vec3d& vec);
	vec3d getVelocity(void);

	void setAcc(vec3d acc);
	void simulate(float dt);


	void visualize(void);
};
#endif