#include "Particle.h"
#include "myUtil.h"

CParticle::CParticle() {
    radius = 0.1f;
    center.set(0.0, 0.0, 0.0);
}

void CParticle::init(void) {
	center.set(0,0,0);
	vel.set(rand(-1,1), rand(0, 1), rand(-1,1));
	vel.normalize();
	vel = rand(5, 15) * vel;
	

}

void CParticle::simulate(double dt, double curTime) {
	CVec3d gravity(0, -10,0);
	// change velocity
	// dV = a * dt
	vel = vel + gravity * dt;
	// change position
	center = center + vel * dt;    
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