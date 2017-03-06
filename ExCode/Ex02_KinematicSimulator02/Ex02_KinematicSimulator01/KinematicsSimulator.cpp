//
//  KinematicsSimulator.cpp
//  GPcode01_01_xcode
//
//  Created by young-min kang on 3/27/15.
//  Copyright (c) 2015 young-min kang. All rights reserved.
//

#include "KinematicsSimulator.h"

CKinematicSimulator::CKinematicSimulator() : CSimulator() {}


void CKinematicSimulator::init() {
    pos.set(0, 1, 0);
    particle.setPosition(pos[0],pos[1],pos[2]);
    particle.setRadius(0.1);
}

void CKinematicSimulator::doBeforeSimulation(double dt, double currentTime) {

}

void CKinematicSimulator::doSimulation(double dt, double currentTime) {
	CVec3d initialPos(0,0,0);
	CVec3d initialVel(2,5,0);
	CVec3d gravity(0, -10,0);
    pos = initialPos + initialVel * currentTime
		+ 0.5 * gravity * (currentTime*currentTime);
		
    particle.setPosition(pos[0], pos[1], pos[2]);
    particle.drawWithGL();
}


void CKinematicSimulator::doAfterSimulation(double dt, double currentTime) {

}