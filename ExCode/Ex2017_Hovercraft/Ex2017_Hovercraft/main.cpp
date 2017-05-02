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

#define NSPHERES 200

class CMyWindow : public CKangGL {
public:
	
	Hover *pHover;
	CMyWindow() : CKangGL() {
		pHover = addHover();
		setCamera(0,0,50, 0, 0, 0, 0, 1, 0);		
	}
	~CMyWindow() {
		removeSpheres();
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
	GLSetupWith(mywin, &argc, argv, "my simple window");
}