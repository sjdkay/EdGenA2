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
#include <math.h>
#include <time.h>



#define MAX_PART 10
using namespace std; 

enum{ ENullPDG = 1000000000 };
// Cross reference GEANT-3 and PDG particle ID indices
struct ParticleCrossRef_t{
  Char_t* name;                                 // name of particle
  Int_t iG3;                                    // G3 index
  Int_t iPDG;                                   // PDG index
};
static const ParticleCrossRef_t kG3toPDG[] = {
  { (Char_t*)"NULL",           0,    ENullPDG },
  { (Char_t*)"gamma",           1,    22 },
  { (Char_t*)"e+",              2,   -11 },
  { (Char_t*)"e-",              3,    11 },
  { (Char_t*)"nu_e",            4,    12 },
  { (Char_t*)"mu+",             5,   -13 },
  { (Char_t*)"mu-",             6,    13 },
  { (Char_t*)"pi0",             7,   111 },
  { (Char_t*)"pi+",             8,   211 },
  { (Char_t*)"pi-",             9,  -211 },
  { (Char_t*)"kaon0",             10,   311 },
  { (Char_t*)"kaon+",             11,   321 },
  { (Char_t*)"kaon-",             12,  -321 },
  { (Char_t*)"kaon0L",           16,   130 },
  { (Char_t*)"kaon0S",           16,   310 },
  { (Char_t*)"eta",            17,   221 },
  { (Char_t*)"eta_prime",           17,   331 },
  { (Char_t*)"omega",          24,   223 },
  { (Char_t*)"rho+",           -1,   213 },
  { (Char_t*)"rho-",           -1,  -213 },
  { (Char_t*)"rho0",           -1,   113 },
  { (Char_t*)"neutron",        13,  2112 },
  { (Char_t*)"proton",         14,  2212 },
  { (Char_t*)"antiproton",     15, -2212 },
  { (Char_t*)"antineutron",    25, -2112 },
  { (Char_t*)"lambda",        18,  3122 },
  { (Char_t*)"sigma+",        19,  3222 },
  { (Char_t*)"sigma0",        20,  3212 },
  { (Char_t*)"sigma-",        21,  3112 },
  { (Char_t*)"anti_lambda",    26, -3122 },
  { (Char_t*)"delta+",         80,  2214 },
  { (Char_t*)"delta0",         81,  2114 },
  { (Char_t*)"deuteron",             45,  1000010020 },
  { (Char_t*)"triton",             46,  1000010030 },
  { (Char_t*)"alpha",          47,  1000020040 },
  { (Char_t*)"He3",            49,  1000020030 },
  { (Char_t*)"Li6", 61, 1000030060 },
  { (Char_t*)"Li7", 62, 1000030070 },
  { (Char_t*)"Be7", 63, 1000040070 },
  { (Char_t*)"Be9", 64, 1000040090 },
  { (Char_t*)"B10", 65, 1000050100 },
  { (Char_t*)"B11", 66, 1000050110 },
  { (Char_t*)"C12", 67, 1000060120 },
  { (Char_t*)"N14", 68, 1000070140 },
  { (Char_t*)"O16", 69, 1000080160 },
  { (Char_t*)"F19", 70, 1000090190 },
  { (Char_t*)"Ne20", 71, 1000100200 },
  { (Char_t*)"Na23", 72, 1000110230 },
  { (Char_t*)"Mg24", 73, 1000120240 },
  { (Char_t*)"Al27", 74, 1000130270 },
  { (Char_t*)"Si28", 75, 1000140280 },
  { (Char_t*)"P31", 76, 1000150310 },
  { (Char_t*)"S32", 77, 1000160320 },
  { (Char_t*)"Cl35", 78, 1000170350 },
  { (Char_t*)"Ar36", 79, 1000180360 },
  { (Char_t*)"K39", 80, 1000190390 },
  { (Char_t*)"Ca40", 81, 1000200400 },
  { (Char_t*)"Sc45", 82, 1000210450 },
  { (Char_t*)"Ti48", 83, 1000220480 },
  { (Char_t*)"V51", 84, 1000230510 },
  { (Char_t*)"Cr52", 85, 1000240520 },
  { (Char_t*)"Mn55", 86, 1000250550 },
  { (Char_t*)"Fe56", 87, 1000260560 },
  { (Char_t*)"Co59", 88, 1000270590 },
  { (Char_t*)"Ni58", 89, 1000280580 },
  { (Char_t*)"Cu63", 90, 1000290630 },
  { (Char_t*)"Zn64", 91, 1000300640 },
  { (Char_t*)"Ge74", 92, 1000320740 },
  { (Char_t*)"Se80", 93, 1000340800 },
  { (Char_t*)"Kr84", 94, 1000360840 },
  { (Char_t*)"Sr88", 95, 1000380880 },
  { (Char_t*)"Zr90", 96, 1000400900 },
  { (Char_t*)"Mo98", 97, 1000420980 },
  { (Char_t*)"Pd106", 98, 1000461060 },
  { (Char_t*)"Cd114", 99, 1000481140 },
  { (Char_t*)"Sn120", 100, 1000501200 },
  { (Char_t*)"Xe132", 101, 1000541320 },
  { (Char_t*)"Ba138", 102, 1000561380 },
  { (Char_t*)"Ce140", 103, 1000581400 },
  { (Char_t*)"Sm152", 104, 1000621520 },
  { (Char_t*)"Dy164", 105, 1000661640 },
  { (Char_t*)"Yb174", 106, 1000701740 },
  { (Char_t*)"W184", 107, 1000741840 },
  { (Char_t*)"Pt194", 108, 1000781940 },
  { (Char_t*)"Au197", 109, 1000791970 },
  { (Char_t*)"Hg202", 110, 1000802020 },
  { (Char_t*)"Pb208", 111, 1000822080 },
  { (Char_t*)"U238", 112, 1000922380 },
  { NULL,             99, -1 },
};


struct IonCrossRef_t{
  Char_t* Name;                                 // name of particle
  Int_t iG3;                                    // G3 index
  Double_t Mass;                                // mass of ion
  Int_t iPDG;                                   // PDG index of ion
};
static const IonCrossRef_t kG3toPDGions[] = {
  //          Name      G3      Mass (GeV)      PDG (100ZZZAAA0)
  { (Char_t*)"deuteron",45, 1.875613, 1000010020 },
  { (Char_t*)"triton", 46, 2.80925, 1000010030 },
  { (Char_t*)"alpha", 47, 3.727417, 1000020040 },
  { (Char_t*)"Geantino",48, 0,         0 },
  { (Char_t*)"He3", 49, 2.80923, 1000020030 },
  { (Char_t*)"Li6", 61, 5.60305, 1000030060 },
  { (Char_t*)"Li7",     62, 6.53536, 1000030070 },
  { (Char_t*)"Be7",   63, 6.53622, 1000040070 },
  { (Char_t*)"Be9",   64, 8.39479, 1000040090 },
  { (Char_t*)"B10",   65, 9.32699, 1000050100 },
  { (Char_t*)"B11", 66, 10.25510, 1000050110 },
  { (Char_t*)"C12", 67, 11.17793, 1000060120 },
  { (Char_t*)"N14", 68, 13.04378, 1000070140 },
  { (Char_t*)"O16", 69, 14.89917, 1000080160 },
  { (Char_t*)"F19", 70, 17.69690, 1000090190 },
  { (Char_t*)"Ne20", 71, 18.62284, 1000100200 },
  { (Char_t*)"Na23", 72, 21.41483, 1000110230 },
  { (Char_t*)"Mg24", 73, 22.34193, 1000120240 },
  { (Char_t*)"Al27", 74, 25.13314, 1000130270 },
  { (Char_t*)"Si28", 75,26.06034, 1000140280 },
  { (Char_t*)"P31", 76, 28.85188, 1000150310 },
  { (Char_t*)"S32", 77, 29.78180, 1000160320 },
  { (Char_t*)"Cl35", 78, 32.57328, 1000170350 },
  { (Char_t*)"Ar36", 79, 33.50356, 1000180360 },
  { (Char_t*)"K39", 80, 36.29447, 1000190390 },
  { (Char_t*)"Ca40", 81, 37.22492, 1000200400 },
  { (Char_t*)"Sc45", 82, 41.87617, 1000210450 },
  { (Char_t*)"Ti48", 83, 44.66324, 1000220480 },
  { (Char_t*)"V51", 84, 47.45401, 1000230510 },
  { (Char_t*)"Cr52", 85, 48.38228, 1000240520 },
  { (Char_t*)"Mn55", 86, 51.17447, 1000250550 },
  { (Char_t*)"Fe56", 87, 52.10307, 1000260560 },
  { (Char_t*)"Co59", 88, 54.89593, 1000270590 },
  { (Char_t*)"Ni58", 89, 53.96644, 1000280580 },
  { (Char_t*)"Cu63", 90, 58.61856, 1000290630 },
  { (Char_t*)"Zn64", 91, 59.54963, 1000300640 },
  { (Char_t*)"Ge74", 92, 68.85715, 1000320740 },
  { (Char_t*)"Se80", 93, 74.44178, 1000340800 },
  { (Char_t*)"Kr84", 94, 78.16309, 1000360840 },
  { (Char_t*)"Sr88", 95, 81.88358, 1000380880 },
  { (Char_t*)"Zr90", 96, 83.74571, 1000400900 },
  { (Char_t*)"Mo98", 97, 91.19832, 1000420980 },
  { (Char_t*)"Pd106", 98, 98.64997, 1000461060 },
  { (Char_t*)"Cd114", 99, 106.10997, 1000481140 },
  { (Char_t*)"Sn120", 100, 111.68821, 1000501200 },
  { (Char_t*)"Xe132", 101, 122.86796, 1000541320 },
  { (Char_t*)"Ba138", 102, 128.45793, 1000561380 },
  { (Char_t*)"Ce140", 103, 130.32111, 1000581400 },
  { (Char_t*)"Sm152", 104, 141.51236, 1000621520 },
  { (Char_t*)"Dy164", 105, 152.69909, 1000661640 },
  { (Char_t*)"Yb174", 106, 162.02245, 1000701740 },
  { (Char_t*)"W184",    107, 171.34924, 1000741840 },
  { (Char_t*)"Pt194", 108, 180.67513, 1000781940 },
  { (Char_t*)"Au197", 109, 183.47324, 1000791970 },
  { (Char_t*)"Hg202", 110, 188.13451, 1000802020 },
  { (Char_t*)"Pb208", 111, 193.72907, 1000822080 },
  { (Char_t*)"U238", 112, 221.74295, 1000922380 },
  { (Char_t*)"NULL",     -1,      0.0,          ENullPDG },
};

class EdOutput {
    public:
        EdOutput(EdInput *inp = 0, const char* fileout="output.root");
	~EdOutput();

	void Write();
	void Close();
	void SetTheta( double *, int);
	void SetPhi(double *, int);
	void SetEf(double *, int);
	void Setpf(double *, int);
	void Setpx(double *, int);
	void Setpy(double *, int);
	void Setpz(double *, int);
	void Setparticle_id(int *, int);
	void Setcharge(int *, int);
	void SetEin(double val){Ein = val;}
	void Setx(double val){if (isnan(val)) x = 0; else x = val;}
	void SetW(double val){if (isnan(val)) W = 0; else W = val; }
	void Sety(double val){if (isnan(val)) y = 0; else y = val; }
	void SetQ2(double val){if (isnan(val)) Q2 = 0; else Q2 = val; }
	void Setnu(double val){if (isnan(val)) nu = 0; else nu = val; }
	void SetZ_ion(int val){Z_ion = val; }
	void SetN_ion(int val){N_ion = val; }
	void Setvx(double *, int);
	void Setvy(double *, int);
	void Setvz(double *, int);
	void Setweight(double *, int);
	void Settowrite(int *, int);

	inline Double_t GetIonMass( Int_t ipdg )
	{
	  for( Int_t i=0;;i++ ){
	    if( kG3toPDGions[i].iPDG == ENullPDG ) return 0.0;
	    if( kG3toPDGions[i].iPDG == ipdg ) return kG3toPDGions[i].Mass;
	  }
	}

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
	double Ein;
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
