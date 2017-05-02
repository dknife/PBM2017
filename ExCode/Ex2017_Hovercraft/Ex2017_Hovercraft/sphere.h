#ifndef SPHERE_YMKANG
#define SPHERE_YMKANG

#include "./GLUT/freeglut.h"
#include "vec3d.h"

class sphere {
public:
	float radius;
	float mass;
	vec3d loc;
	vec3d vel;
	vec3d acc;
	vec3d pVel;
	vec3d pAcc;


	sphere() : mass(1), radius(1), 
		loc(vec3d(0,0,0)), vel(vec3d(0,0,0)), acc(vec3d(0,0,0)) {}
	sphere(const vec3d& _center, float _radius) : 
		loc(_center), radius(_radius), mass(_radius*_radius*_radius), 
		vel(vec3d(0, 0, 0)), acc(vec3d(0, 0, 0)) {}

	void setRadius(float _radius);
	float getRadius(void);

	void setLocation(const vec3d& vec);
	vec3d getLocation(void);
	void setVelocity(const vec3d& vec);
	vec3d getVelocity(void);
	void setAcc(const vec3d& vec);
	vec3d getAcc(void);
	void addAcc(const vec3d& vec);
	void initAcc(void);

	void move(const vec3d& displacement);

	// simulation
	void simulate(float dt);

	void visualize(void);
};

#endif