#include "Particle.h"
#include "myUtil.h"

CParticle::CParticle() {
    center.set(0.0, 0.0, 0.0);
	mass = rand(0.1, 1);
	radius = 0.3;
}

void CParticle::init(void) {
	center.set(0, 10.0, 0);
	vel.set(rand(-20,20), -10.0, rand(-20,20));
}

void CParticle::simulate(double dt, double curTime) {
	if(dt>0.03) dt=0.03;

	CVec3d gravity(0, -10,0);
	CVec3d acc = gravity;
	
	// buoyancy
	// buoy = rho * gravity * volume;
	// acc +=  buoy/mass;
	float rho = 10.0;
	float dragCoeff = - 1.;
	CVec3d drag(0,0,0);
	float volume = 3.1415*(3.0/4.0)*radius*radius*radius;
	float pen = 5.0 + radius - center[1];
	float ratio;
	if(pen>0.0) { // in the water
		if(pen>2.0*radius) ratio=1.0;
		else ratio = pen/(2.0*radius);
		CVec3d buoy(0,rho*10.0*volume,0);
		drag = dragCoeff * (vel^vel)*vel.getNormalized(); 
		acc = acc + ratio*(1.0/mass)*(drag+buoy);
	}

	///////////////////


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

	glColor3f(0.0, 1.0-mass, 0.0);
    glPushMatrix();
    glTranslated(center[0], center[1], center[2]);
    glutWireSphere(radius, 10, 10);
    glPopMatrix();
}