#include "./GLUT/freeglut.h"
#include <math.h>
#include <stdio.h>
#pragma comment(lib, "freeglut.lib")

#include "KangGL.h"
#include "vec3d.h"
#include "sphere.h"



class CMyWindow : public CKangGL {
public:
	CPoint *point;
	sphere *sphere;
	vec3d loc;
	vec3d vel;
	vec3d acc;

	CMyWindow() : CKangGL() {
		point = addPoint();
		sphere = addSphere();
		addPlane(5, 5, 0.2);
		setCamera(5, 5, 10, 0, 0, 0, 0, 1, 0);
	}
	~CMyWindow() {
		removePoints();
	};

	virtual void init(void) {
		loc.set(0, 0, 0);
		vel.set(5, 5, 0);
		acc.set(0, -10, 0);
		point->setLocation(loc.x, loc.y, loc.z);

		sphere->setLocation(vec3d(0, 0, 0));
		sphere->setRadius(1.0);
	};

	virtual void clean(void) {

	}

	virtual void doSimulation(double dt, double currentTime) { // time in seconds
		vel = vel + acc * dt;
		loc = loc + vel * dt;
		if (loc.y < 0) {
			loc.y *= -1.0;
			vel.y *= -1.0;
		}
		point->setLocation(loc.x, loc.y, loc.z);
		sphere->setLocation(vec3d(loc.x, loc.y, loc.z));
		
	}
};



int main(int argc, char **argv) {

	CMyWindow* mywin = new CMyWindow();
	GLSetupWith(mywin, &argc, argv, "my simple window");
}