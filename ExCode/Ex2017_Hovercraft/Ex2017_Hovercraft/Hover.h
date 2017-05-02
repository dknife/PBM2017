#ifndef _hover_ymkang
#define _hover_ymkang

#include "vec3d.h"

class Hover {
	vec3d loc;		float angle;
	vec3d vel;		float aVel;
	vec3d acc;		float aAcc;
	float mass;		float I;

	bool engine[2];
	vec3d force[2];

	vec3d localToGlobal(vec3d l);
public:
	Hover();
	void simulate(float dt);
	void visualize();
};

#endif