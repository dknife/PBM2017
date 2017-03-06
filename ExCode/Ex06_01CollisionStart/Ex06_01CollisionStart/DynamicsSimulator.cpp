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
	particle[0].setMass(0.2);
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

	// draw
	for(int i=0; i<NPARTICLES; i++) {
		particle[i].drawWithGL();
	}
}


void CDynamicSimulator::doAfterSimulation(double dt, double currentTime) {

}