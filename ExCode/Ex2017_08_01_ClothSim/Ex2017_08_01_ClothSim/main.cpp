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


class CMyWindow : public CKangGL {
public:
	

	CMyWindow() : CKangGL() {		
		addPlane(50, 50, 5);
		setCamera(100, 100, 100, 0, 0, 0, 0, 1, 0);
	}
	~CMyWindow() {
		
	};

	virtual void init(void) {
		
	};

	virtual void clean(void) {

	}

	virtual void doSimulation(double dt, double currentTime) { // time in seconds

		
	
	}
	

};



int main(int argc, char **argv) {

	CMyWindow* mywin = new CMyWindow();
	GLSetupWith(mywin, &argc, argv, "Cloth Simulation");
}