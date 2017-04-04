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

	CMyWindow() : CKangGL() {
		for(int i=0;i<NSPHERES;i++) sphere[i] = addSphere();
		addPlane(50, 50, 5);
		setCamera(15, 0, 10, 0, 0, 0, 0, 1, 0);
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
			vel[i] = vel[i] + acc[i] * dt;
			loc[i] = loc[i] + vel[i] * dt;		
			sphere[i]->setLocation(vec3d(loc[i].x, loc[i].y, loc[i].z));
		}
		
	}

	void collisionHandling(int i) {
		float e = 0.75;
		float penetration = sphere[i]->getRadius() - loc[i].y;
		if (penetration > 0) { // collision
			loc[i].y += (1+e)*penetration;
			if (vel[i].y < 0) vel[i].y *= -e;
		}
	}
};



int main(int argc, char **argv) {

	CMyWindow* mywin = new CMyWindow();
	GLSetupWith(mywin, &argc, argv, "my simple window");
}