#include "EdInput.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include "TString.h"

EdInput::EdInput(const char *file){
    printf("Reading %s for input\n", file);

    char command[100];
    ifstream inputfile;
    inputfile.open(file, ifstream::in);
    if( !inputfile ) {
      printf("%s cannot be opened\n", file); 
      exit(1);
    }
    char c1;
    char delim = ';';
    TString valcommand;
    TString valc2;
    double factor;
    
    while( !inputfile.eof() ){
      c1 = inputfile.peek(); // read the first character , if it is a #, skip the line
      if (c1!='#') {
	inputfile.getline(command,100,delim);
	// printf("read command %s\n",command);
	valcommand = command;
	if (valcommand.Contains("nevt")) {
	  valcommand.ReplaceAll("nevt:","");
	  valcommand.ReplaceAll(";","");
	  valcommand.ReplaceAll(" ","");
	  fData.nevt = valcommand.Atoi();
	  printf("Total Number of events %d\n",fData.nevt);
	}
	if (valcommand.Contains("nprint")) {
	  valcommand.ReplaceAll("nprint:","");
	  valcommand.ReplaceAll(";","");
	  valcommand.ReplaceAll(" ","");
	  fData.nprnt = valcommand.Atoi();
	}
	if (valcommand.Contains("model")) {
	  valcommand.ReplaceAll("model:","");
	  valcommand.ReplaceAll(";","");
	  valcommand.ReplaceAll(" ","");
	  fData.model = valcommand.Atoi();
	}
	if (valcommand.Contains("beam")) {
	  valcommand.ReplaceAll("beam:","");
	  valcommand.ReplaceAll(";","");
	  if (valcommand.Contains("MeV")) factor = 0.001;
	  else factor = 1;
	  valcommand.ReplaceAll(";","");
	  valcommand.ReplaceAll(" ","");
	  valcommand.ReplaceAll("GeV","");
	  valcommand.ReplaceAll("MeV","");
	  fData.e_energy = factor*valcommand.Atof();
	}
	if (valcommand.Contains("tg_Z")) {
	  valcommand.ReplaceAll("tg_Z:","");
	  valcommand.ReplaceAll(";","");
	  valcommand.ReplaceAll(" ","");
	  fData.tg_Z = valcommand.Atoi();
	}
	if (valcommand.Contains("tg_N")) {
	  valcommand.ReplaceAll("tg_N:","");
	  valcommand.ReplaceAll(";","");
	  valcommand.ReplaceAll(" ","");
	  fData.tg_N = valcommand.Atoi();
	}
	if (valcommand.Contains("length")) {
	  valcommand.ReplaceAll("length:","");
	  valcommand.ReplaceAll(";","");
	  if (valcommand.Contains(" m")) factor = 0.01;
	  else factor = 1;
	  valcommand.ReplaceAll(";","");
	  valcommand.ReplaceAll(" m","");
	  valcommand.ReplaceAll(" ","");
	  valcommand.ReplaceAll("cm","");
	  fData.length = factor*valcommand.Atof();
	}
	if (valcommand.Contains("ras_x")) {
	  valcommand.ReplaceAll("ras_x:","");
	  valcommand.ReplaceAll(";","");
	  if (valcommand.Contains(" m")) factor = 0.01;
	  else factor = 1;
	  valcommand.ReplaceAll(";","");
	  valcommand.ReplaceAll(" m","");
	  valcommand.ReplaceAll(" ","");
	  valcommand.ReplaceAll("cm","");
	  fData.lenx = factor*valcommand.Atof();
	}
	if (valcommand.Contains("ran_y")) {
	  valcommand.ReplaceAll("ran_y:","");
	  valcommand.ReplaceAll(";","");
	  if (valcommand.Contains(" m")) factor = 0.01;
	  else factor = 1;
	  valcommand.ReplaceAll(";","");
	  valcommand.ReplaceAll(" m","");
	  valcommand.ReplaceAll(" ","");
	  valcommand.ReplaceAll("cm","");
	  fData.leny = factor*valcommand.Atof();
	}
	if (valcommand.Contains("theta")) {
	  valcommand.ReplaceAll("theta:","");
	  valcommand.ReplaceAll(";","");
	  if (valcommand.Contains(" deg")) factor = 3.14/180;
	  else factor = 1; //rad
	  valcommand.ReplaceAll(";","");
	  valcommand.ReplaceAll("deg","");
	  valcommand.ReplaceAll(" ","");
	  valcommand.ReplaceAll("rad","");
	  valc2 = valcommand(0,valcommand.First(",")-1);
	  fData.theta_min = factor*valc2.Atof();
	  valc2 = valcommand(valcommand.First(",")+1,valcommand.Length());
	  fData.theta_max = factor*valc2.Atof();
	  printf("Theta_min=%.2f ;  Theta_max=%.2f\n",fData.theta_min,fData.theta_max);
	}

      }
    }
    // FILE *f = fopen(file, "r");

    // if( !f ){ printf("%s cannot be opened\n", file); exit(1); }

    // char dummy[255];
    // numpart = 100;

    // fscanf(f, "%s%d", dummy, &fData.nevt);
    // fscanf(f, "%s%d", dummy, &fData.nprnt);
    // fscanf(f, "%s%lf%s", dummy, &fData.e_energy, dummy);
    // fscanf(f, "%s%i", dummy, &fData.tg_Z);
    // fscanf(f, "%s%i", dummy, &fData.tg_N);
    // fscanf(f, "%s%lf%s", dummy, &fData.length, dummy);
    // fscanf(f, "%s%lf%s", dummy, &fData.lenx, dummy);
    // fscanf(f, "%s%lf%s", dummy, &fData.leny, dummy);
    // fscanf(f, "%s%lf%lf%s", dummy, &fData.theta_min, &fData.theta_max, dummy);
    // fscanf(f, "%s%lf%lf%lf%s", dummy, &fData.off_x, &fData.off_y, 
    // 	    		       &fData.off_z, dummy);
    // fscanf(f, "%s%d", dummy, &fData.npart);
    // numpart = fData.npart;
    // fscanf(f, "%s", dummy);
    // for (int i=0; i<numpart; i++) fscanf(f, "%d", &fData.pid[i] );
    // fscanf(f, "%s%d", dummy, &fData.nvertex);
    // numpart = fData.nvertex;
    // printf("Number of vertexes = %i \n",numpart);
    // for (int i=0; i<numpart; i++) {
    //   fscanf(f, "%s%d%d", dummy,&fData.overt[i],&fData.npvert[i]); 
 
    //   // printf("vertex n. %i, Number of vertexes = %i part n. %i",i,*fData.npvert[i]);
 
    //   fscanf(f, "%s%d", dummy, &fData.v_type[i]);
    //   if (fData.v_type[i] == 1) fscanf(f, "%lf",&fData.v_ratio[i]);
    //   else {
    // 	printf("vertex n. %i type not supported \n",i+1);
    // 	exit(1);
    //   }
    // }
    // fscanf(f, "%s%d", dummy, &fData.out_fmt);

    // fclose(f);
}

EdInput::~EdInput(){
}
