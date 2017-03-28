#include "./GLUT/freeglut.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#pragma comment(lib, "freeglut.lib")

#include "KangGL.h"

#define NPOINTS 1000
bool bExploded = false;
double ExplosionHeight = 3.0;
double explosionV = 5.0;
double rand(double minV, double maxV) {
	double interval = maxV - minV;
	return minV + interval * ((rand() % 10001) / 10000.0);
}

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
	CPoint *point[NPOINTS];
	vec3d loc[NPOINTS];
	vec3d vel[NPOINTS];
	vec3d acc;

	CMyWindow() : CKangGL() {
		for(int i=0;i<NPOINTS;i++)
			point[i] = addPoint();
		addPlane(5, 5, 0.2);
		setCamera(10, 10, 30, 0, 0, 0, 0, 1, 0);
	}
	~CMyWindow() {
		removePoints();
	}

	virtual void init(void) {
		for (int i = 0; i < NPOINTS; i++) {
			loc[i].set(0, 0, 0);
			vel[i].set(0, 15, 0);
			point[i]->setLocation(loc[i].x, loc[i].y, loc[i].z);
		}
		acc.set(0, -10, 0);
		bExploded = false;
		
	};

	virtual void clean(void) {

	}

	virtual void doSimulation(double dt, double currentTime) { // time in seconds
		if (!bExploded && loc[0].y > ExplosionHeight) {
			bExploded = true;
			for (int i = 0; i < NPOINTS; i++) {
				vec3d v(rand(-explosionV, explosionV), 
					rand(-explosionV, explosionV),
					rand(-explosionV, explosionV));
				vel[i] = vel[i] + v;
			}
		}
		
		for (int i = 0; i < NPOINTS; i++) {
			vel[i] = vel[i] + acc * dt;
			loc[i] = loc[i] + vel[i] * dt;
			
			
			point[i]->setLocation(loc[i].x, loc[i].y, loc[i].z);
		}
		
	}
};



int main(int argc, char **argv) {

	CMyWindow* mywin = new CMyWindow();
	GLSetupWith(mywin, &argc, argv, "my simple window");
}