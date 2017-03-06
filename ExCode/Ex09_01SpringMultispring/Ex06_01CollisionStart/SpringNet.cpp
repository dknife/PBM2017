#include "SpringNet.h"
/*
class CSpringNet {
public:
	int nParticles;
	int nSprings;
	CParticle *p;
	CSpring *s;

public:
	*/
CSpringNet::CSpringNet(int n, int nE) {
	nParticles = n;
	nSprings = nE;
	p = new CParticle[n];
	s = new CSpring[nE];
}
void CSpringNet::SetParticle(int pIdx, CVec3d loc, 
	CVec3d vel, double mass) {
		p[pIdx].setPosition(loc[0],loc[1],loc[2]);
		p[pIdx].setVelocity(vel[0],vel[1],vel[2]);
		p[pIdx].setMass(mass);
		p[pIdx].setRadius(0.1);
}
void CSpringNet::SetSpring(
		int springIdx, int p1, int p2, 
		double len, double ks) {
		s[springIdx].p1 = p1;
		s[springIdx].p2 = p2;
		s[springIdx].len = len;
		s[springIdx].ks = ks;
}
void CSpringNet::ComputeSpringForce() {
		
	CParticle part1, part2;
	for(int i=0;i<nSprings;i++) { // for all spring
		part1 = p[s[i].p1];
		part2 = p[s[i].p2];
		CVec3d c1 = part1.getPosition();
		CVec3d c2 = part2.getPosition();
		CVec3d force = c2 - c1;
		double len = force.len();
		force.normalize();
		
		double magnitude = s[i].ks * (len - s[i].len);
		p[s[i].p1].addForce(magnitude*force);
		p[s[i].p2].addForce(-magnitude*force);


	}
	
}

