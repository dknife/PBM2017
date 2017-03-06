#ifndef _TONGMYONG_YMKANG_KINEMATIC_PARTICLE_2015_
#define _TONGMYONG_YMKANG_KINEMATIC_PARTICLE_2015_

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif

#include "Vec3d.h"

class CParticle {
    CVec3d center;
	CVec3d vel;
	//float mass;


    float radius;

public:
    CParticle();

	void init(void);
	void simulate(double dt, double currentTime);

    void setPosition(double x, double y, double z);
    void setRadius(double r);

    void drawWithGL(void);
};

#endif