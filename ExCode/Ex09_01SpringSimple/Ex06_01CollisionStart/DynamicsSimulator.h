//
//  KinematicsSimulator.h
//
//  Created by young-min kang on 3/27/15.
//  Copyright (c) 2015 young-min kang. All rights reserved.
//

#ifndef __GPcode01_01_xcode__DynamicsSimulator__
#define __GPcode01_01_xcode__DynamicsSimulator__

#include "Simulator.h"
#include "Particle.h"


#define NPARTICLES 2
#define ELASTICITY 1.0

class CDynamicSimulator : public CSimulator {
    CParticle particle[NPARTICLES];

public:
    CDynamicSimulator();

    void init(void);

private:

	CVec3d computeSpringForce(CParticle &p1, CParticle &p2);

    // Actions to be performed before the simulation frame
    void doBeforeSimulation(double dt, double currentTime);
    // Simulation is done here
    void doSimulation(double dt, double currentTime);
    // Actions to be performed after the simulation frame
    void doAfterSimulation(double dt, double currentTime);

};

#endif /* defined(__GPcode01_01_xcode__KinematicsSimulator__) */