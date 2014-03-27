#ifndef __EdModel_h
#define __EdModel_h

#include "EdInput.h"
#include <math.h>
#include <cstdlib>

#include <TVector3.h>

// HG electron beam

class EdModel{
    public:
	EdModel(EdInput *inp = 0);
	~EdModel();

	double GetLength() {return length; }
	double GetLx() {return len_x; }
	double GetLy() {return len_y; }
	double GetEnergy() {return energy; }
	double GetTheta_min() {return theta_min;}
	double GetTheta_max() {return theta_max;}
	int    GetNpart() {return npart;}
	TVector3 GetTgtOffset(){ return offset; }
	int    GetPid(int i){ return pid[i]; }
	int    GetNvertex(){ return nvertex; }
	int    GetOvert(int i){ return overt[i]; }
	int    GetNpvert(int i){ return npvert[i]; }
	int    GetDvert(int i, int j){ return dvert[i][j]; }
	int    GetV_type(int i){ return v_type[i]; }
	int    GetV_ratio(int i){ return v_ratio[i]; }

    private:
	double length;
	double len_x;
	double len_y;
	double energy;
	double theta_min;
	double theta_max;
	int    pid[100];
	int    npart;
	int    nvertex; // total number of vertexes
	int    npvert[10]; // total number of particle at one vertex
	int    overt[10]; // particle at origin of one vertex (need to be already existing)
	int    dvert[10][10]; // particle daughters at vertex 
	int    v_type[10]; // vertex type (1= ratio  of probability , 2= cross section
	double v_ratio[10]; // ration to be applied to vertex
	TVector3 offset;
};
#endif//__EdModel_h
