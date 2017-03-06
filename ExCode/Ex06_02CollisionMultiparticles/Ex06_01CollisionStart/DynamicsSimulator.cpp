//
//  KinematicsSimulator.cpp
//  GPcode01_01_xcode
//
//  Created by young-min kang on 3/27/15.
//  Copyright (c) 2015 young-min kang. All rights reserved.
//

#include "DynamicsSimulator.h"
#include "myUtil.h"

CDynamicSimulator::CDynamicSimulator() : CSimulator() {}


void CDynamicSimulator::init() {
	for(int i=0;i<NPARTICLES; i++) {
		particle[i].setPosition(rand(-3,3), 0, rand(-3,3));
		particle[i].setVelocity(rand(-3,3), 0, rand(-3,3));
		particle[i].setRadius(rand(0.1,0.2));		
		particle[i].setMass(particle[i].getRadius());
	}
	
}

void CDynamicSimulator::doBeforeSimulation(double dt, double currentTime) {

}

void CDynamicSimulator::doSimulation(double dt, double currentTime) {
	
	glColor3f(0,0,0);
	glPointSize(3);
	for(int i=0; i<NPARTICLES; i++) {
		particle[i].simulate(dt, currentTime);
	}

	for(int i=0; i<NPARTICLES; i++) {
		for(int j=i+1; j<NPARTICLES; j++) {
			collisionHandle(particle[i], particle[j]);
		}
	}
	// collision with boundary
	CVec3d c, v;
	double r;
	CVec3d colNorm;
	CVec3d vp, vt;
	for(int i=0; i<NPARTICLES; i++) {
		c = particle[i].getPosition();
		r = particle[i].getRadius();
		v = particle[i].getVelocity();
		// collision check
		double distance = c.len();
		if (distance > BoundaryRadius - r) {
			colNorm = -1.0 * c.getNormalized();
			double alpha = v ^ colNorm;
			vp = alpha * colNorm;
			v = v - (1.0 + ELASTICITY) * vp;
			particle[i].setVelocity(v[0], v[1], v[2]);
		}
	}



}


void CDynamicSimulator::doAfterSimulation(double dt, double currentTime) {
	// draw
	for(int i=0; i<NPARTICLES; i++) {
		particle[i].drawWithGL();
	}

	glBegin(GL_LINE_LOOP);
	for(int i=0;i<100;i++) {
		double angle = 2.0*3.14*(double(i)/100.0);
		glVertex3f(BoundaryRadius * cos(angle), 
			0, BoundaryRadius * sin(angle));
	}
	glEnd();
}

void CDynamicSimulator::collisionHandle(CParticle &p1, CParticle &p2) {

	// collision detect
    CVec3d c1 = p1.getPosition();
    CVec3d c2 = p2.getPosition();
    CVec3d N = c1 - c2;
    double dist = N.len();
    if(dist < p1.getRadius() + p2.getRadius()) {
        // collision detected
        N.normalize();
        CVec3d v1 = p1.getVelocity();
        CVec3d v2 = p2.getVelocity();
        double v1N = v1 ^ N;
        double v2N = v2 ^ N;
        double m1 = p1.getMass();
        double m2 = p2.getMass();
        // approaching ?
        if( v2N - v1N > 0 ) { // approaching
            double v1New = ( (m1-m2)*v1N + 2.0*m2*v2N ) / (m1+m2);
            double v2New = ( (m2-m1)*v2N + 2.0*m1*v1N ) / (m1+m2);
            v1 = v1 - v1N * N + ELASTICITY*v1New*N;
            v2 = v2 - v2N * N + ELASTICITY*v2New*N;
            p1.setVelocity(v1.x, v1.y, v1.z);
            p2.setVelocity(v2.x, v2.y, v2.z);
        }   
    }
}