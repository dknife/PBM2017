#include "./GLUT/freeglut.h"
#include <math.h>
#include <stdio.h>
#pragma comment(lib, "freeglut.lib")

#include "KangGL.h"

class CMyWindow : public CKangGL {
public:
	CMyWindow() : CKangGL() {}
	~CMyWindow() {};

	CPoint *point;

	virtual void init(void) {
		point = addPoint();
		addPlane(5, 5, 0.2);
		
	};

	virtual void clean(void) {
		removePoints();
	}
	
	virtual void doSimulation(double dt, double currentTime) { // time in seconds
		setCamera(sin(currentTime*6.28), 5, 5, 0, 0, 0, 0, 1, 0);
		point->setLocation(0, sin(currentTime*6.28), 0);		
	}
};



int main(int argc, char **argv) {

	CMyWindow* mywin = new CMyWindow();
	GLSetupWith(mywin, &argc, argv, "my simple window");
}