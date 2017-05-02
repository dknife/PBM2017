#ifndef _hover_ymkang
#define _hover_ymkang

#include "vec3d.h"

class Hover {
	vec3d loc;
	vec3d vel;
	vec3d acc;
	float mass;

public:
	Hover();
	void simulate(float dt);
	void visualize();
};

#endif