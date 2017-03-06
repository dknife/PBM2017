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
		particle[i].setPosition(i, 3, 0);
		particle[i].setVelocity(0,0,0);
		particle[i].setRadius(0.1);		
		particle[i].setMass(0.1);
	}
	
}

void CDynamicSimulator::doBeforeSimulation(double dt, double currentTime) {

}

void CDynamicSimulator::doSimulation(double dt, double currentTime) {
	
	glColor3f(0,0,0);
	glPointSize(3);

	// add force
	CVec3d gravity(0,-9.8,0);
	for(int i=0; i<NPARTICLES; i++) {
		particle[i].clearForce();
		particle[i].addAcc(gravity);		
	}

	CVec3d force = computeSpringForce(particle[0], particle[1]);
	particle[0].addForce(force);
	particle[1].addForce(-1.0 * force);
	

	// simulate
	for(int i=1; i<NPARTICLES; i++) {
		particle[i].simulate(dt, currentTime);
	}

	
	



}


void CDynamicSimulator::doAfterSimulation(double dt, double currentTime) {
	
	// collision with plane
	CVec3d c, v;
	double r;
	CVec3d colNorm(0,1,0);
	CVec3d vp, vt;
	for(int i=0; i<NPARTICLES; i++) {
		c = particle[i].getPosition();
		r = particle[i].getRadius();
		v = particle[i].getVelocity();
		// collision check
		double distance = c.len();
		double penetration = r - c[1];		
		if ( penetration > 0 ) {
			double alpha = v ^ colNorm;
			vp = alpha * colNorm;
			v = v - (1.0 + ELASTICITY) * vp;
			particle[i].setVelocity(v[0], v[1], v[2]);

			c = c + ((1.0 + ELASTICITY) * penetration )*colNorm;			
			particle[i].setPosition(c[0],c[1],c[2]);
		}
	}

	// draw

	for(int i=0; i<NPARTICLES; i++) {
		particle[i].drawWithGL();
	}

	glBegin(GL_LINE_STRIP);
	for(int i=0; i<NPARTICLES; i++) {
		particle[i].drawWithGL();
		c = particle[i].getPosition();
		glVertex3f(c[0],c[1],c[2]);
	}
	glEnd();


	
}

CVec3d CDynamicSimulator::computeSpringForce(
	CParticle &p1, CParticle &p2) {
	
		// collision detect
		CVec3d c1 = p1.getPosition();
		CVec3d c2 = p2.getPosition();
		CVec3d force = c2 - c1;
		double len = force.len();
		force.normalize();

		double springCoeff = 1.0;
		double magnitude = springCoeff * (len - 1.0);

		return magnitude * force;
}
