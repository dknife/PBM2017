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
	normal = new CVec3d[n];
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
	// spring force
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

	// damping
	// f_damp(i) = k_damp * (v(j) - v(i)) 
	// for All Spring(i,j)

	double dampingCoeff = 0.5;
	for(int i=0;i<nSprings;i++) { // for all spring
		
		int p1 = s[i].p1;
		int p2 = s[i].p2;
		CVec3d v1 = p[p1].getVelocity();
		CVec3d v2 = p[p2].getVelocity();
		CVec3d f_damp = dampingCoeff * (v2 - v1);
		p[p1].addForce(f_damp);
		p[p2].addForce(-1.0*f_damp);

	}

	// drag and lift
	CVec3d wind(50,0,0);
	float k_drag = 0.05, k_lift = 0.01;
	CVec3d fdrag, flift;
	for(int i=0; i<nParticles; i++) {
		float NdotW = normal[i]^wind.getNormalized();
		if(NdotW<0) NdotW = -NdotW;
		fdrag = (k_drag * NdotW) * wind;
		p[i].addForce(fdrag);
		flift = (k_lift * (1.0 - NdotW)) * wind.len() * normal[i];
		p[i].addForce(flift);
	}
	
}

void CSpringNet::ComputeNormals(int NRow, int NCol) {
	for(int i=0; i<nParticles;i++) {
		int pLeft = i-1;
		int pBelow = i + NCol;
		int pUp = i - NCol;
		int pRight = i+1;

		CVec3d v1, v2;
		// if left and bottom
		if (i%NCol==0 && i >= (NRow-1)*NCol) {
			v1 = p[pRight].getPosition() - p[i].getPosition();
			v2 = p[pUp].getPosition() - p[i].getPosition();
		}
		// if left end
		else if(i%NCol==0) {
			v1 = p[pBelow].getPosition() - p[i].getPosition();
			v2 = p[pRight].getPosition() - p[i].getPosition();
		}
		// if bottom line
		else if(i >= (NRow-1)*NCol) {
			v1 = p[pUp].getPosition() - p[i].getPosition();
			v2 = p[pLeft].getPosition() - p[i].getPosition();
		}
		// else 
		else {
			v1 = p[pLeft].getPosition() - p[i].getPosition();
			v2 = p[pBelow].getPosition() - p[i].getPosition();
		}
		CVec3d N = v1 * v2; // cross product
		N.normalize();
		normal[i] = N;
	}
}