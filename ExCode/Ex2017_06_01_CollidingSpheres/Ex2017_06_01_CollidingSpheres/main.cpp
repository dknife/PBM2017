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
		sphere[1]->setVelocity(vec3d(-5000, 0, 0));
		sphere[1]->setAcc(vec3d(0, 0, 0));
		sphere[1]->setRadius(0.2);
		
	};

	virtual void clean(void) {

	}

	virtual void doSimulation(double dt, double currentTime) { // time in seconds
		dt = 0.0001;
		for (int iteration = 0; iteration < 10; iteration++) {

			for (int i = 0; i < NSPHERES; i++) {
				sphere[i]->simulate(dt);
					sphere[i]->initAcc();
			}

			// collision handling
			for (int i = 0; i < NSPHERES; i++) {
				for (int j = i + 1; j < NSPHERES; j++) {
					vec3d p1 = sphere[i]->getLocation();
					vec3d p2 = sphere[j]->getLocation();
					float distance = (p1 - p2).len();
					float r1 = sphere[i]->getRadius();
					float r2 = sphere[j]->getRadius();
					float m1 = sphere[i]->mass;
					float m2 = sphere[j]->mass;
					vec3d v1 = sphere[i]->getVelocity();
					vec3d v2 = sphere[j]->getVelocity();
					vec3d v1new;
					vec3d v2new;
					if (distance < r1 + r2) {
						v1new = (2 * m2*v2 + (m1 - m2)*v1) / (m1 + m2);
						v2new = (2 * m1*v1 + (m2 - m1)*v2) / (m1 + m2);
						sphere[i]->setVelocity(v1new);
						sphere[j]->setVelocity(v2new);
					}
				}
			}
		}
	}
};

int main(int argc, char **argv) {
	CMyWindow* mywin = new CMyWindow();
	GLSetupWith(mywin, &argc, argv, "my simple window");
}
