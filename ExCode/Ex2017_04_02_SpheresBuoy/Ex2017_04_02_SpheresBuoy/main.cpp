#include "./GLUT/freeglut.h"
#include <math.h>
#include <stdio.h>
#pragma comment(lib, "freeglut.lib")

#include "KangGL.h"
#include "vec3d.h"
#include "sphere.h"

double rand(double minV, double maxV) {
	double interval = maxV - minV;
	return minV + interval * ((rand() % 10001) / 10000.0);
}

#define NSPHERES 50

class CMyWindow : public CKangGL {
public:
	sphere *sphere[NSPHERES];
	vec3d loc[NSPHERES];
	vec3d vel[NSPHERES];
	vec3d acc[NSPHERES];

	float density;
	float dragCoeff;

	CMyWindow() : CKangGL() {
		for(int i=0;i<NSPHERES;i++) sphere[i] = addSphere();
		addPlane(50, 50, 5);
		setCamera(15, 0, 15, 0, 0, 0, 0, 1, 0);
		density=3.0;
		dragCoeff = 10.5;
	}
	~CMyWindow() {
		removeSpheres();
	};

	virtual void init(void) {
		for (int i = 0; i < NSPHERES; i++) {
			loc[i].set(0, 10, 0);
			vel[i].set(rand(-5,5), rand(0, -6), rand(-5,5));
			acc[i].set(0, -10, 0);

			sphere[i]->setLocation(vec3d(0, 0, 0));
			sphere[i]->setRadius(1.0);
		}
	};

	virtual void clean(void) {

	}

	virtual void doSimulation(double dt, double currentTime) { // time in seconds

		for (int i = 0; i < NSPHERES; i++) {
			collisionHandling(i);
			// buoyant and drag force 
			vec3d buoy(0, 0, 0);
			vec3d drag(0, 0, 0);
			if (loc[i].y < 0) {
				buoy = - density * vec3d(0, -10, 0);
				drag = - dragCoeff * vel[i];
			}
			acc[i] = vec3d(0, -10, 0) + buoy + drag;
			vel[i] = vel[i] + acc[i] * dt;
			loc[i] = loc[i] + vel[i] * dt;	

			
			sphere[i]->setLocation(vec3d(loc[i].x, loc[i].y, loc[i].z));
		}
		
	}

	void collisionHandling(int i) {

		float e = 0.75;
		float minY = -5;
		float penetration = sphere[i]->getRadius() + minY - loc[i].y;
		if (penetration > 0) { // collision
			loc[i].y += (1+e)*penetration;
			if (vel[i].y < 0) vel[i].y *= -e;
		}

		float minX = -10;
		float maxX = 10;
		float minZ = -10;
		float maxZ = 10;

		// minx
		penetration = sphere[i]->getRadius() + minX - loc[i].x;
		if (penetration > 0) {
			loc[i].x += (1 + e)*penetration;
			if (vel[i].x < 0) vel[i].x *= -e;
		}
		
		// maxx
		penetration = loc[i].x - (maxX - sphere[i]->getRadius());
		if (penetration > 0) {
			loc[i].x -= (1 + e)*penetration;
			if (vel[i].x > 0) vel[i].x *= -e;
		}

		// minz
		penetration = sphere[i]->getRadius() + minZ - loc[i].z;
		if (penetration > 0) {
			loc[i].z += (1 + e)*penetration;
			if (vel[i].z < 0) vel[i].z *= -e;
		}

		// maxz
		penetration = loc[i].z - (maxZ - sphere[i]->getRadius());
		if (penetration > 0) {
			loc[i].z -= (1 + e)*penetration;
			if (vel[i].z > 0) vel[i].z *= -e;
		}
	}
};



int main(int argc, char **argv) {

	CMyWindow* mywin = new CMyWindow();
	GLSetupWith(mywin, &argc, argv, "my simple window");
}