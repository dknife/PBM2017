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
   for(int i=0; i<NPARTICLES; i++) particle[i].init();
}

void CDynamicSimulator::doBeforeSimulation(double dt, double currentTime) {

}

void CDynamicSimulator::doSimulation(double dt, double currentTime) {
	
	for(int i=0; i<NPARTICLES; i++) {
		particle[i].simulate(dt, currentTime);
		particle[i].drawWithGL();
	}
}


void CDynamicSimulator::doAfterSimulation(double dt, double currentTime) {

}