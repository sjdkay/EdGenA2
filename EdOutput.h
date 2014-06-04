#ifndef __EdOutput_h
#define __EdOutput_h

#include "EdInput.h"


#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TChain.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <math.h>


#include <stdlib.h>
#include <errno.h>
#include <ntypes.h>
#include <math.h>
#include <sys/types.h>
#include <time.h>
extern "C" {
#include <bostypes.h>
}



#define MAX_PART 10
using namespace std; 


extern"C" {
  void close_fpack_unit(char *dataname);
}

class EdOutput {
    public:
        EdOutput(EdInput *inp = 0, const char* fileout="output.root");
	~EdOutput();

	void Write();
	void Close();
	void MakeFileLUND();
	void MakeFileBOS();
	void SetTheta( double *, int);
	void SetPhi(double *, int);
	void SetEf(double *, int);
	void Setpf(double *, int);
	void Setpx(double *, int);
	void Setpy(double *, int);
	void Setpz(double *, int);
	void Setparticle_id(int *, int);
	void Setcharge(int *, int);
	void Setx(double val){x = val;}
	void SetW(double val){W = val; }
	void Sety(double val){y = val; }
	void SetQ2(double val){Q2 = val; }
	void Setnu(double val){nu = val; }
	void SetZ_ion(int val){Z_ion = val; }
	void SetN_ion(int val){N_ion = val; }
	void Setvx(double *, int);
	void Setvy(double *, int);
	void Setvz(double *, int);
	void Setweight(double *, int);
	void Settowrite(int *, int);

    private:
	void InitTree();

	char fOutName[255];

	TFile *fOutfile;
	TTree *fTree;

	double fNevt;

	int towrite[MAX_PART];

	int n_part;
	double theta[MAX_PART];
	double phi[MAX_PART];
	double Ef[MAX_PART];
	double pf[MAX_PART];
	double px[MAX_PART];
	double py[MAX_PART];
	double pz[MAX_PART];
	double x;
	double W;
	double y;
	double Q2;
	double nu;
	int particle_id[MAX_PART];
	int charge[MAX_PART];
	int Z_ion;
	int N_ion;
	double vx[MAX_PART];
	double vy[MAX_PART];
	double vz[MAX_PART];
	double weight[MAX_PART];


};
#endif//__EdOutput_h
