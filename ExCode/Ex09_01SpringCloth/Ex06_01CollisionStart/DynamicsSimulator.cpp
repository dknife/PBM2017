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
	springNet = new CSpringNet(
		NPartRow*NPartCol, // number of particles
		NPartRow*(NPartCol-1) +  // horizontal edges
		NPartCol*(NPartRow-1) +  // vertical edges
		2 * (NPartCol-1)*(NPartRow-1) // structural edges
		);	
	// particle setting
	for(int i=0;i<NPartRow; i++) {
		for(int j=0; j<NPartCol; j++) {
			springNet->SetParticle(i*NPartCol+j, // index
				CVec3d(j*0.5, 10.0-i*0.5, 0),
				CVec3d(0,0,0),
				0.1);
		}
	}

	// horizontal edges
	int idx = 0;
	for(int i=0; i<NPartRow; i++) {
		for(int j=0; j<NPartCol-1; j++) {
			springNet->SetSpring(idx, 
				i*NPartCol+j, i*NPartCol+j+1, 
				0.5, 15.0);
			idx++;
		}
	}

	// vertical edges
	for(int i=0; i<NPartRow-1; i++) {
		for(int j=0; j<NPartCol; j++) {
			springNet->SetSpring(idx, 
				i*NPartCol+j, (i+1)*NPartCol+j, 
				0.5, 15.0);
			idx++;
		}
	}

	// structural edges
	double sqrt2 = sqrt(2.0);
	for(int i=0; i<NPartRow-1; i++) {
		for(int j=0; j<NPartCol-1; j++) {
			springNet->SetSpring(idx, 
				i*NPartCol+j, (i+1)*NPartCol+j+1, 
				0.5*sqrt2, 15.0);
			idx++;
			springNet->SetSpring(idx, 
				(i+1)*NPartCol+j, (i)*NPartCol+j+1, 
				0.5*sqrt2, 15.0);
			idx++;
		}
	}
	
	
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

	glBegin(GL_LINES);
	for(int i=0; i<springNet->nSprings; i++) {
		CVec3d loc1 = springNet->p[springNet->s[i].p1].getPosition();
		CVec3d loc2 = springNet->p[springNet->s[i].p2].getPosition();
		glVertex3f(loc1[0],loc1[1],loc1[2]);
		glVertex3f(loc2[0],loc2[1],loc2[2]);

	}
	glEnd();
	
	
}

