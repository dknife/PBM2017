#include "./GLUT/freeglut.h"
#include <math.h>
#include <stdio.h>
#pragma comment(lib, "freeglut.lib")

#include "KangGL.h"


struct vec3d {
	double x;
	double y;
	double z;

public: 
	vec3d() : x(0), y(0), z(0) {}
	vec3d(double x, double y, double z) { this->x = x; this->y = y; this->z = z; }
	void set(double x, double y, double z) { this->x = x; this->y = y; this->z = z; }	
};

inline vec3d operator*(float t, const vec3d& v) {
	return vec3d(t*v.x, t*v.y, t*v.z);
}
inline vec3d operator*(const vec3d& v, float t) {
	return vec3d(t*v.x, t*v.y, t*v.z);
}
inline vec3d operator+(const vec3d& v1, const vec3d& v2) {
	return vec3d(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}
inline vec3d operator-(const vec3d& v1, const vec3d& v2) {
	return vec3d(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

class CMyWindow : public CKangGL {
public:
	CPoint *point;
	vec3d loc;
	vec3d vel;
	vec3d acc;

	CMyWindow() : CKangGL() {
		point = addPoint();
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
		
	}
};



int main(int argc, char **argv) {

	CMyWindow* mywin = new CMyWindow();
	GLSetupWith(mywin, &argc, argv, "my simple window");
}