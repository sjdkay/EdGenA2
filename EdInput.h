#ifndef __EdInput_h
#define __EdInput_h

#include "TObject.h"
#include "TString.h"

struct inputdata {
    int    nevt;
    int    nprnt;
    int    model;
   TString ifile;
    int    npart; // total number of particles involved
    int    nvertex; // total number of vertexes
    int    npvert[10]; // total number of particle at one vertex
    int    overt[10]; // particle at origin of one vertex (need to be already existing)
    int    dvert[10][10]; // particle daughters at vertex 
    int    v_type[10]; // vertex type (1= ratio  of probability , 2= cross section
    double v_ratio[10]; // ration to be applied to vertex

    int    pid[100];
    int    beam_pid;
    double e_energy;
    double length;
    double lenx;
    double leny;
 
    double theta_min;
    double theta_max;

    int    tg_Z;
    int    tg_N;
    double off_x;
    double off_y;
    double off_z;

    int    out_fmt; // 1=root 2=root+LUND

};

class EdInput{ 
    public:
	 EdInput(const char *file);
	~EdInput();

	int    GetNevt(){ return fData.nevt; }
	int    GetNprnt(){ return fData.nprnt; }
	int    GetNpart(){ return fData.npart; }
	int    GetModel(){ return fData.model; }
      TString  GetIfile(){ return fData.ifile; }
	int    GetBeamPID(){ return fData.beam_pid; }
	int    GetNvertex(){ return fData.nvertex; }
	int    GetOvert(int i){ return fData.overt[i]; }
	int    GetNpvert(int i){ return fData.npvert[i]; }
	int    GetDvert(int i, int j){ return fData.dvert[i][j]; }
	int    GetV_type(int i){ return fData.v_type[i]; }
	int    GetV_ratio(int i){ return fData.v_ratio[i]; }
	int    GetPid(int i){ return fData.pid[i]; }
	double Get_eEnergy(){ return fData.e_energy; }
	double Get_length(){ return fData.length; }
	int    Get_tg_Z(){ return fData.tg_Z; }
	int    Get_tg_N(){ return fData.tg_N; }
	double Get_lenx(){ return fData.lenx; }
	double Get_leny(){ return fData.leny; }
	int    Get_fmt(){ return fData.out_fmt; }
	double Get_thetaMin(){ return fData.theta_min; }
	double Get_thetaMax(){ return fData.theta_max; }

	double GetTgtXoff(){ return fData.off_x; }
	double GetTgtYoff(){ return fData.off_y; }
	double GetTgtZoff(){ return fData.off_z; }
	


    private:
	inputdata fData;
	int numpart;
};
#endif//__EdInput_h
