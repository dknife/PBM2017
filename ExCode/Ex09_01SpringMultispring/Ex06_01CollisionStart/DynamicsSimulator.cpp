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
	springNet = new CSpringNet(4, 6);	
	springNet->SetParticle(0, CVec3d(0,3,0), CVec3d(0,0,0), 1);
	springNet->SetParticle(1, CVec3d(1,3,0), CVec3d(0,0,0), 1);
	springNet->SetParticle(2, CVec3d(0,2,0), CVec3d(0,0,0), 1);
	springNet->SetParticle(3, CVec3d(1,2,0), CVec3d(0,0,0), 1);
	springNet->SetSpring(0, 0,1, 1.0, 20.0);
	springNet->SetSpring(1, 1,3, 1.0, 20.0);
	springNet->SetSpring(2, 3,2, 1.0, 20.0);
	springNet->SetSpring(3, 0,2, 1.0, 20.0);
	springNet->SetSpring(4, 1,2, sqrt(2.0), 20.0);
	springNet->SetSpring(5, 0,3, sqrt(2.0), 20.0);
	
}

void CDynamicSimulator::doBeforeSimulation(double dt, double currentTime) {

}

void CDynamicSimulator::doSimulation(double dt, double currentTime) {
	
	glColor3f(0,0,0);
	glPointSize(3);

	// add force
	CVec3d gravity(0,-9.8,0);
	for(int i=0; i<springNet->nParticles; i++) {
		springNet->p[i].clearForce();
		springNet->p[i].addAcc(gravity);
	}
	
	springNet->ComputeSpringForce();

	// simulate
	for(int i=1; i<springNet->nParticles; i++) {
		springNet->p[i].simulate(dt, currentTime);
	}
	

	
	



}


void CDynamicSimulator::doAfterSimulation(double dt, double currentTime) {
	
	// collision with plane
	/*
	CVec3d c, v;
	double r;
	CVec3d colNorm(0,1,0);
	CVec3d vp, vt;
	for(int i=0; i<springNet->nParticles; i++) {
		c = springNet->p[i].getPosition();
		r = springNet->p[i].getRadius();
		v = springNet->p[i].getVelocity();
		// collision check
		double distance = c.len();
		double penetration = r - c[1];		
		if ( penetration > 0 ) {
			double alpha = v ^ colNorm;
			vp = alpha * colNorm;
			v = v - (1.0 + ELASTICITY) * vp;
			springNet->p[i].setVelocity(v[0], v[1], v[2]);

			c = c + ((1.0 + ELASTICITY) * penetration )*colNorm;			
			springNet->p[i].setPosition(c[0],c[1],c[2]);
		}
	}
	*/

	// draw

	for(int i=0; i<springNet->nParticles; i++) {
		springNet->p[i].drawWithGL();
	}

	
	
}

