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
		particle[i].setVelocity(rand(-1,1), rand(-1,1), rand(-1,1));
		particle[i].setRadius(rand(0.05,0.1));		
		particle[i].setMass(particle[i].getRadius());
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
		//particle[i].addAcc(gravity);		
	}

	for(int i=0; i<NPARTICLES; i++) {
		for(int j=i+1; j<NPARTICLES; j++) {
			CVec3d f =  computeAttraction(particle[i], particle[j]);
			particle[i].addForce(f);
			particle[j].addForce(-1.0*f);
		}
	}

	// simulate
	for(int i=0; i<NPARTICLES; i++) {
		particle[i].simulate(dt, currentTime);
	}

	// collision handling
	for(int i=0; i<NPARTICLES; i++) {
		for(int j=i+1; j<NPARTICLES; j++) {
			collisionHandle(particle[i], particle[j]);
		}
	}
	



}


void CDynamicSimulator::doAfterSimulation(double dt, double currentTime) {
	/*
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
		double penetration = distance - (BoundaryRadius - r);
		if ( penetration > 0 ) {
			colNorm = -1.0 * c.getNormalized();
			double alpha = v ^ colNorm;
			vp = alpha * colNorm;
			v = v - (1.0 + ELASTICITY) * vp;
			particle[i].setVelocity(v[0], v[1], v[2]);

			c = c + ((1.0 + ELASTICITY) * penetration )*colNorm;			
			particle[i].setPosition(c[0],c[1],c[2]);
		}
	}
	*/
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

	glColor3f(1,0,0);glutWireSphere(BoundaryRadius, 30,30);
}

CVec3d CDynamicSimulator::computeAttraction(
	CParticle &p1, CParticle &p2) {
	
		// collision detect
		CVec3d c1 = p1.getPosition();
		CVec3d c2 = p2.getPosition();
		CVec3d N = c2 - c1;
		N.normalize();
		double dist = N.len();
		double m1 = p1.getMass();
        double m2 = p2.getMass();
	
		CVec3d force; double Coeff = 0.5;
		force = (Coeff*(m1*m2)/(dist*dist))*N;
		return force;
}

void CDynamicSimulator::collisionHandle(CParticle &p1, CParticle &p2) {

	// collision detect
    CVec3d c1 = p1.getPosition();
    CVec3d c2 = p2.getPosition();
    CVec3d N = c1 - c2;
    double dist = N.len();
	double penetration = p1.getRadius() + p2.getRadius() - dist;
    if(penetration > 0) {
        // collision detected
        N.normalize();
        CVec3d v1 = p1.getVelocity();
        CVec3d v2 = p2.getVelocity();
        double v1N = v1 ^ N;
        double v2N = v2 ^ N;
		double vr = v1N - v2N;
		double e = 1.5;
        double m1 = p1.getMass();
        double m2 = p2.getMass();
        // approaching ?

        if( vr < 0 ) { // approaching
			double J = -vr*(ELASTICITY+1.0)/(1.0/m1 + 1.0/m2);
            double v1New = v1N + J/m1;
            double v2New = v2N - J/m2;
			v1 = v1 - v1N * N + v1New*N;
			v2 = v2 - v2N * N + v2New*N; 
            p1.setVelocity(v1.x, v1.y, v1.z);
            p2.setVelocity(v2.x, v2.y, v2.z);
        }   
		c1 = c1 + ((1.0+ELASTICITY)*penetration)*N;
		c2 = c2 - ((1.0+ELASTICITY)*penetration)*N;
		p1.setPosition(c1.x, c1.y, c1.z);
		p2.setPosition(c2.x, c2.y, c2.z);
    }
}