#ifndef _springnet_2016_hh
#define _springnet_2016_hh

#include "Particle.h"

class CSpring {
public:
	int p1;
	int p2;
	double len;
	double ks;
};

class CSpringNet {
public:
	int nParticles;
	int nSprings;
	CParticle *p;
	CVec3d *normal;
	CSpring *s;

public:
	CSpringNet(int n, int nE);
	void SetParticle(int pIdx, CVec3d loc, CVec3d vel, double mass);
	void SetSpring(
		int springIdx, int p1, int p2, 
		double len, double ks);
	void ComputeSpringForce();
	void ComputeNormals(int NRow, int NCol);
};

#endif