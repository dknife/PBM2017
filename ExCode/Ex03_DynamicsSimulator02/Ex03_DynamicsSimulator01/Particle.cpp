#include "Particle.h"
#include "myUtil.h"

CParticle::CParticle() {
    center.set(0.0, 0.0, 0.0);
	radius = mass = rand(0.01, 0.3);
}

void CParticle::init(void) {
	center.set(0,0,0);
	vel.set(rand(-1,-2), rand(0, 1), rand(-1,1));
	vel.normalize();
	vel = rand(3, 7) * vel;
}

void CParticle::simulate(double dt, double curTime) {
	CVec3d windForce(0.5,0,0);
	CVec3d gravity(0, -10,0);
	CVec3d acc = gravity + (1.0/mass)*windForce;
	
	// change velocity
	vel = vel + acc * dt;
	// change position
	center = center + vel * dt;    

	// is colliding on the floor?
	if (center[1]<0.0 ) {
		// handle this collision
		center.set(center[0], -0.9*center[1], center[2]);
		if(vel[1]<0) { // trying to move into the floor
			vel.set(vel[0], -0.9*vel[1], vel[2]);
		}
	}
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