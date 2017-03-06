//
//  KinematicsSimulator.cpp
//  GPcode01_01_xcode
//
//  Created by young-min kang on 3/27/15.
//  Copyright (c) 2015 young-min kang. All rights reserved.
//

#include "DynamicsSimulator.h"

CDynamicSimulator::CDynamicSimulator() : CSimulator() {}


void CDynamicSimulator::init() {
	particle[0].setPosition(1,0,0);
	particle[1].setPosition(-1,0,0);
	particle[0].setVelocity(-1,0,0);
	particle[1].setVelocity( 1,0,0);
	particle[0].setRadius(0.2);
	particle[1].setRadius(0.1);
	particle[0].setMass(0.1);
	particle[1].setMass(0.1);
}

void CDynamicSimulator::doBeforeSimulation(double dt, double currentTime) {

}

void CDynamicSimulator::doSimulation(double dt, double currentTime) {
	
	glColor3f(0,0,0);
	glPointSize(3);
	for(int i=0; i<NPARTICLES; i++) {
		particle[i].simulate(dt, currentTime);
	}
	// collision handling
	CVec3d x0 = particle[0].getPosition();
	CVec3d x1 = particle[1].getPosition();
	CVec3d v0 = particle[0].getVelocity();
	CVec3d v1 = particle[1].getVelocity();
	double r0 = particle[0].getRadius();
	double r1 = particle[1].getRadius();
	double m0 = particle[0].getMass();
	double m1 = particle[1].getMass();
	CVec3d v0new, v1new;

	double d = (x0-x1).len();
	if(d<r0+r1) { // collided! (position)
		if(v1[0]-v0[0] > 0) { // velocity collision check
			v0new = (m0-m1)*v0 + 2.0*m1*v1;
			v1new = (m1-m0)*v1 + 2.0*m0*v0;
			v0new = (1.0/(m0+m1)) * v0new;
			v1new = (1.0/(m0+m1)) * v1new;

			particle[0].setVelocity(v0new[0], v0new[1], v0new[2]);
			particle[1].setVelocity(v1new[0], v1new[1], v1new[2]);
		}
	}


	// draw
	for(int i=0; i<NPARTICLES; i++) {
		particle[i].drawWithGL();
	}
}


void CDynamicSimulator::doAfterSimulation(double dt, double currentTime) {

}