#include "Particle.h"
#include "myUtil.h"

CParticle::CParticle() {
    radius = 0.1f;
    center.set(0.0, 0.0, 0.0);
}

void CParticle::init(void) {
	initPos.set(0,0,0);
	initVel.set(rand(-1,1), rand(0, 1), rand(-1,1));
	initVel.normalize();
	initVel = rand(5, 15) * initVel;
	

}

void CParticle::simulate(double dt, double curTime) {
	
	CVec3d gravity(0, -10,0);
    CVec3d curPos = initPos + initVel * curTime
		+ 0.5 * gravity * (curTime*curTime);
		
    setPosition(curPos[0], curPos[1], curPos[2]);
}
void CParticle::setPosition(double x, double y, double z) {
    center.set(x,y,z);
}

void CParticle::setRadius(double r) {
    radius = r;

}

void CParticle::drawWithGL(void) {
    glPushMatrix();
    glTranslated(center[0], center[1], center[2]);
    glutWireSphere(radius, 20, 20);
    glPopMatrix();
}