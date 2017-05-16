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

#define NSPHERES 2

class CMyWindow : public CKangGL {
public:
	sphere *sphere[NSPHERES];
	

	float density;
	float dragCoeff;

	CMyWindow() : CKangGL() {
		for(int i=0;i<NSPHERES;i++) sphere[i] = addSphere();
		addPlane(50, 50, 5);
		setCamera(0, 5, 10, 0, 0, 0, 0, 1, 0);		
	}
	~CMyWindow() {
		removeSpheres();
	};

	virtual void init(void) {
		sphere[0]->setLocation(vec3d(-5, 0, 0));
		sphere[0]->setVelocity(vec3d(5, 0, 0));
		sphere[0]->setAcc(vec3d(0, 0, 0));
		sphere[0]->setRadius(1.0);

		sphere[1]->setLocation(vec3d(5, 0, 0));
		sphere[1]->setVelocity(vec3d(-5, 0, 0));
		sphere[1]->setAcc(vec3d(0, 0, 0));
		sphere[1]->setRadius(1.0);
		
	};

	virtual void clean(void) {

	}

	virtual void doSimulation(double dt, double currentTime) { // time in seconds
		for (int i = 0; i < NSPHERES; i++) {
			sphere[i]->simulate(dt);
			sphere[i]->initAcc();
		}
	}
};

int main(int argc, char **argv) {
	CMyWindow* mywin = new CMyWindow();
	GLSetupWith(mywin, &argc, argv, "my simple window");
}
