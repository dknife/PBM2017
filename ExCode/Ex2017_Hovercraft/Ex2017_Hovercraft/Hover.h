#ifndef _hover_ymkang
#define _hover_ymkang

#include "vec3d.h"

#define NENGINES 4

class Hover {
	vec3d loc;		float angle;
	vec3d vel;		float aVel;
	vec3d acc;		float aAcc;
	float mass;		float I;

	bool engine[NENGINES];
	vec3d force[NENGINES];
	vec3d r[NENGINES];

	vec3d localToGlobal(vec3d l);
public:
	Hover();
	void switchEngine(int engineNumber);
	void simulate(float dt);
	void visualize();
};

#endif