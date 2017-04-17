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

#define NSPHERES 100

class CMyWindow : public CKangGL {
public:
	sphere *sphere[NSPHERES];
	

	float density;
	float dragCoeff;

	CMyWindow() : CKangGL() {
		for(int i=0;i<NSPHERES;i++) sphere[i] = addSphere();
		addPlane(50, 50, 5);
		setCamera(100, 100, 100, 0, 0, 0, 0, 1, 0);
		density=3.0;
		dragCoeff = 3.5;
	}
	~CMyWindow() {
		removeSpheres();
	};

	virtual void init(void) {
		for (int i = 0; i < NSPHERES; i++) {
			sphere[i]->setLocation(vec3d(rand(-100, 100), rand(0, 0), rand(-100, 100)));
			sphere[i]->setVelocity(vec3d(0,0,0));
			sphere[i]->setAcc(vec3d(0, 0, 0));			
			sphere[i]->setRadius(rand(0.2, 3));
		}
	};

	virtual void clean(void) {

	}

	virtual void doSimulation(double dt, double currentTime) { // time in seconds

		float G = 100.1;
		
		
		/*
		vec3d centerMass(0,0,0);
		float totalMass=0.0;
		for (int i = 0; i < NSPHERES; i++) {
			centerMass = centerMass + sphere[i]->mass*sphere[i]->getLocation();
			totalMass = totalMass + sphere[i]->mass;
		}
		centerMass = centerMass / totalMass;

		for (int i = 0; i < NSPHERES; i++) {
			vec3d acc;
			vec3d cm = (1.0/(totalMass-sphere[i]->mass))*(totalMass*centerMass - sphere[i]->mass*sphere[i]->getLocation()); // *(float(NSPHERES) / float(NSPHERES - 1)) - sphere[i]->getLocation() / float(NSPHERES - 1);
			vec3d xij = cm - sphere[i]->getLocation();
			
			float lenSqr = xij.lenSquare();
			if (lenSqr < 10) lenSqr = 10.0;
			xij.normalize();
			acc = (G * (totalMass-sphere[i]->mass)/ lenSqr) * xij;
			sphere[i]->addAcc(acc);	
			sphere[i]->simulate(dt);
			sphere[i]->initAcc();
		}
		
		
		*/

		/*
		for (int i = 0; i < NSPHERES; i++) {
			for (int j = i+1; j < NSPHERES; j++) {
				vec3d acc_ij;
				vec3d xij = sphere[j]->getLocation() - sphere[i]->getLocation();
				float len = xij.len();
				if (len == 0) exit(0);
				xij.normalize();
				
				float r1 = sphere[i]->getRadius();
				float r2 = sphere[j]->getRadius();
				float m1 = sphere[i]->mass;
				float m2 = sphere[j]->mass;
				if (len < (r1 + r2)) {
					len = (r1 + r2);
					float d = (r1 + r2) - len;
					sphere[i]->moveLocation(-d*xij);
					sphere[j]->moveLocation( d*xij);
					vec3d collisionVel = dot(sphere[i]->velocity - sphere[j]->velocity,  xij) * xij;
					sphere[i]->velocity = sphere[i]->velocity - (m2/(m1+m2))*collisionVel;
					sphere[j]->velocity = sphere[j]->velocity + (m1/(m1+m2))*collisionVel;
				}
				acc_ij = (G / (len*len)) * xij;
				sphere[i]->addAcc(acc_ij * sphere[j]->mass);		
				sphere[j]->addAcc(-1.0*acc_ij * sphere[i]->mass);
			}
		}

		for (int i = 0; i < NSPHERES; i++) {
			sphere[i]->simulate(dt);
			sphere[i]->initAcc();
		}
		*/

		for (int i = 0; i < NSPHERES; i++) {
			for (int j = i + 1; j < NSPHERES; j++) {
				vec3d acc_ij;
				vec3d xi = sphere[i]->getLocation();
				vec3d xj = sphere[j]->getLocation();
				
				vec3d xij = xj - xi;
				float len = xij.len();
				if (len == 0) exit(0);
				xij.normalize();

				float r1 = sphere[i]->getRadius();
				float r2 = sphere[j]->getRadius();
				float m1 = sphere[i]->mass;
				float m2 = sphere[j]->mass;

				int big = -1;
				int small = -1;
				if (len < 0.65*(r1 + r2)) {

					int big = r1>r2 ? i : j;
					int small = r1>r2 ? j : i;
					
					sphere[big]->velocity = (m1*sphere[i]->velocity + m2*sphere[j]->velocity) / (m1 + m2);
					sphere[big]->setRadius(pow(m1 + m2, 1/3.0));
					sphere[big]->setLocation((m1*xi+m2*xj)/(m1+m2));

					sphere[small]->setLocation(vec3d(rand(-100, 100), rand(0, 0), rand(-100, 100)));
					vec3d newpos = sphere[small]->getLocation();
					newpos = 0.001*newpos;
					sphere[small]->setVelocity(vec3d(-newpos.x, -newpos.y, newpos.z));
					sphere[small]->setRadius(rand(0.3, 1));
				}
				else if (len < (r1 + r2)) {
					len = (r1 + r2);
					float d = (r1 + r2) - len;
					sphere[i]->moveLocation(-d*xij);
					sphere[j]->moveLocation(d*xij);
					vec3d collisionVel = dot(sphere[i]->velocity - sphere[j]->velocity, xij) * xij;
					sphere[i]->velocity = sphere[i]->velocity - 1.5*(m2/(m1+m2))*collisionVel;
					sphere[j]->velocity = sphere[j]->velocity + 1.5*(m1/(m1+m2))*collisionVel;
				}
				
				acc_ij = (G / (len*len)) * xij;
				if(i!=small) sphere[i]->addAcc(     acc_ij * sphere[j]->mass);
				if(j!=small) sphere[j]->addAcc(-1.0*acc_ij * sphere[i]->mass);
			}
		}

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