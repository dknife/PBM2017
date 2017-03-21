#include "./GLUT/freeglut.h"
#include <math.h>
#include <stdio.h>
#pragma comment(lib, "freeglut.lib")

#include "KangGL.h"

class CMyWindow : public CKangGL {
public:
	CMyWindow() : CKangGL() {
		point = addPoint();
		addPlane(5, 5, 0.2);
		setCamera(5, 5, 5, 0, 0, 0, 0, 1, 0);
	}
	~CMyWindow() {
		removePoints();
	};

	CPoint *point;

	virtual void init(void) {

	};

	virtual void clean(void) {
		
	}
	
	virtual void doSimulation(double dt, double currentTime) { // time in seconds
		
		point->setLocation(cos(currentTime*6.28), 3, sin(currentTime*6.28));		
	}
};



int main(int argc, char **argv) {

	CMyWindow* mywin = new CMyWindow();
	GLSetupWith(mywin, &argc, argv, "my simple window");
}