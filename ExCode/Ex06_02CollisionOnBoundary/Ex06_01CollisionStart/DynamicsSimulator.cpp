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
		particle[i].setVelocity(4, 0,0); //rand(-3,3), 0, rand(-3,3));
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
			v = v - (1.0 + 0.9) * vp;
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