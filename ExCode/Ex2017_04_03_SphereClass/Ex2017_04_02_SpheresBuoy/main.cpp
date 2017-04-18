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
	sphere *sphere[NSPHERES];

	CMyWindow() : CKangGL() {
		for(int i=0;i<NSPHERES;i++) sphere[i] = addSphere();
		addPlane(50, 50, 5);
		setCamera(200,200,200, 0, 0, 0, 0, 1, 0);		
	}
	~CMyWindow() {
		removeSpheres();
	};

	virtual void init(void) {
		for (int i = 0; i < NSPHERES; i++) {
			sphere[i]->setLocation(vec3d(rand(-100,100), 0, rand(-100,100)));
			sphere[i]->setVelocity(vec3d(0,0,0));
			sphere[i]->setAcc(vec3d(0, 0, 0));
			sphere[i]->setRadius(rand(0.5, 3.0));
		}
	};

	virtual void clean(void) {

	}

	virtual void doSimulation(double dt, double currentTime) { // time in seconds

		float G = 10.0;
		for (int i = 0; i < NSPHERES; i++) {
			for (int j = i+1; j < NSPHERES; j++) {
				vec3d xi = sphere[i]->getLocation();
				vec3d xj = sphere[j]->getLocation();
				vec3d xij = xj - xi;
				float mi = sphere[i]->mass;
				float mj = sphere[j]->mass;
				float M = mi+mj;
				float len = xij.len();
				float ri = sphere[i]->getRadius();
				float rj = sphere[j]->getRadius();
				float R = ri + rj;
				xij.normalize();			
				// collision.....
				if (len < R) {
					len = R;
					float d = R - len;  // penetration
					sphere[i]->move(-(mj*d/M)*xij);
					sphere[j]->move( (mi*d/M)*xij);
					// is sphere i trying to approach?
					vec3d vi = sphere[i]->getVelocity();
					vec3d vj = sphere[j]->getVelocity();
					vec3d v_rel = vi - vj;
					float approaching = dot(v_rel, xij);
					if (approaching > 0) {
						vec3d appVel = approaching*xij;
						sphere[i]->setVelocity(vi - mj*appVel/M);
						sphere[j]->setVelocity(vj + mi*appVel/M);
					}
				}
				
				vec3d f = (G*mi*mj/(len*len))*xij;
				sphere[i]->addAcc(f/mi);
				sphere[j]->addAcc(f/(-mj));			
			}
		}

		// simulate
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