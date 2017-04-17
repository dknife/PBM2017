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
	

	float density;
	float dragCoeff;

	CMyWindow() : CKangGL() {
		for(int i=0;i<NSPHERES;i++) sphere[i] = addSphere();
		addPlane(50, 50, 5);
		setCamera(100, 100, 100, 0, 0, 0, 0, 1, 0);
		density=3.0;
		dragCoeff = 3.5;
	}
	~CMyWindow() {
		removeSpheres();
	};

	virtual void init(void) {
		for (int i = 0; i < NSPHERES; i++) {
			sphere[i]->setLocation(vec3d(0, 10, 0));
			sphere[i]->setVelocity(vec3d(rand(-5,5), rand(0, -6), rand(-5,5)));
			sphere[i]->setAcc(vec3d(0, -10, 0));			
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
			if (sphere[i]->getLocation().y < 0) {
				buoy = - density * vec3d(0, -10, 0);
				drag = - dragCoeff * sphere[i]->getVelocity();
			}
			sphere[i]->setAcc(vec3d(0, -10, 0) + buoy + drag);
			sphere[i]->simulate(dt);
		}
		
	}

	void collisionHandling(int i) {

		float e = 0.75;
		float minY = -5;
		float penetration = sphere[i]->getRadius() + minY - sphere[i]->getLocation().y;
		if (penetration > 0) { // collision
			vec3d loc = sphere[i]->getLocation();
			vec3d vel = sphere[i]->getVelocity();
			sphere[i]->setVelocity(vec3d(loc[0], loc[1] + (1 + e)*penetration, loc[2]));
			if (vel.y < 0) sphere[i]->setVelocity(vec3d(vel[0], -e*vel[1], vel[2]));
		}
	}


};



int main(int argc, char **argv) {

	CMyWindow* mywin = new CMyWindow();
	GLSetupWith(mywin, &argc, argv, "my simple window");
}