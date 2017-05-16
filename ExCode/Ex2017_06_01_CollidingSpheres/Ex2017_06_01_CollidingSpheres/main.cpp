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
		setCamera(0, 15, 0, 0, 0, 0, 0, 0, 1);		
	}
	~CMyWindow() {
		removeSpheres();
	};

	virtual void init(void) {
		/*for (int i = 0; i < NSPHERES; i++) {
			vec3d p(rand(-15, 15), 0, rand(-15, 15));
			sphere[i]->setLocation(p);
			sphere[i]->setVelocity(-p);
			sphere[i]->setAcc(vec3d(0, 0, 0));
			sphere[i]->setRadius(rand(0.5,1.0));
		}*/
		sphere[0]->setLocation(vec3d(-5,0,1.75));
		sphere[0]->setVelocity(vec3d(5,0,0));
		sphere[0]->setAcc(vec3d(0, 0, 0));
		sphere[0]->setRadius(1.0);

		sphere[1]->setLocation(vec3d(5, 0, 0));
		sphere[1]->setVelocity(vec3d(-5, 0, 0));
		sphere[1]->setAcc(vec3d(0, 0, 0));
		sphere[1]->setRadius(0.8);
		
	};

	virtual void clean(void) {

	}

	virtual void doSimulation(double dt, double currentTime) { // time in seconds
		dt = 0.001;
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
					vec3d N = (p1-p2).getNormalized();
					float distance = (p1 - p2).len();
					float r1 = sphere[i]->getRadius();
					float r2 = sphere[j]->getRadius();
					float m1 = sphere[i]->mass;
					float m2 = sphere[j]->mass;
					float v1 = dot(sphere[i]->getVelocity(), N);
					float v2 = dot(sphere[j]->getVelocity(), N);
					float v1new;
					float v2new;
					if (distance < r1 + r2) {
						v1new = (2 * m2*v2 + (m1 - m2)*v1) / (m1 + m2);
						v2new = (2 * m1*v1 + (m2 - m1)*v2) / (m1 + m2);
						sphere[i]->setVelocity(
							sphere[i]->getVelocity() + (v1new-v1)*N);
						sphere[j]->setVelocity(
							sphere[j]->getVelocity() + (v2new-v2)*N);
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
