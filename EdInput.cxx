#include "EdInput.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>
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
    int poscomma;
    int atvertex = 0;
    
    while( !inputfile.eof() ){
      c1 = inputfile.peek(); // read the first character , if it is a #, skip the line
      if (c1!='#') {
	inputfile.getline(command,100,delim);
	// printf("read command %s\n",command);
	valcommand = command;
	printf("%s \n",valcommand.Data());
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
	  printf("Print feedback every %d events\n",fData.nprnt);
	}
	if (valcommand.Contains("model")) {
	  valcommand.ReplaceAll("model:","");
	  valcommand.ReplaceAll(";","");
	  valcommand.ReplaceAll(" ","");
	  fData.model = valcommand.Atoi();
	  printf("Model for the generator %d\n",fData.model);
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
	  printf("Beam energy of %.4f\n",fData.e_energy);
	}
	if (valcommand.Contains("tg_Z")) {
	  valcommand.ReplaceAll("tg_Z:","");
	  valcommand.ReplaceAll(";","");
	  valcommand.ReplaceAll(" ","");
	  fData.tg_Z = valcommand.Atoi();
	  printf("Target Z: %d\n",fData.tg_Z);
	}
	if (valcommand.Contains("tg_N")) {
	  valcommand.ReplaceAll("tg_N:","");
	  valcommand.ReplaceAll(";","");
	  valcommand.ReplaceAll(" ","");
	  fData.tg_N = valcommand.Atoi();
	  printf("Target N: %d\n",fData.tg_N);
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
	  printf("Target length: %.4f cm\n",fData.length);	  
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
	  printf("Raster X: %.4f cm\n",fData.lenx);	  
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
	  printf("Raster Y: %.4f cm\n",fData.leny);	  
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
	  valc2 = valcommand(0,valcommand.First(","));
	  fData.theta_min = factor*valc2.Atof();
	  valc2 = valcommand(valcommand.First(",")+1,valcommand.Length());
	  fData.theta_max = factor*valc2.Atof();
	  printf("Theta_min=%.2f ;  Theta_max=%.2f\n",fData.theta_min,fData.theta_max);	  
	}
	if (valcommand.Contains("offset")) {
	  valcommand.ReplaceAll("offset:","");
	  valcommand.ReplaceAll(";","");
	  if (valcommand.Contains(" m")) factor = 0.01;
	  else factor = 1; //rad
	  valcommand.ReplaceAll(";","");
	  valcommand.ReplaceAll(" m","");
	  valcommand.ReplaceAll(" ","");
	  valcommand.ReplaceAll("cm","");
	  valc2 = valcommand(0,valcommand.First(",")-1);
	  fData.off_x = factor*valc2.Atof();
	  valcommand.Replace(0,valc2.Length()+1,"");
	  valc2 = valcommand(0,valcommand.First(",")-1);
	  fData.off_y = factor*valc2.Atof();
	  valcommand.Replace(0,valc2.Length()+1,"");
	  fData.off_z = factor*valcommand.Atof();
	  printf("Offset_X=%.2f ;  Offset_Y=%.2f ; Offset_Z=%.2f\n",fData.off_x,fData.off_y,fData.off_z);
	}
	if (valcommand.Contains("npart")) {
	  valcommand.ReplaceAll("npart:","");
	  valcommand.ReplaceAll(";","");
	  valcommand.ReplaceAll(" ","");
	  fData.npart = valcommand.Atoi();
	  printf("Number of particle in final state: %d\n",fData.npart);
	}
	if (valcommand.Contains("pid")) {
	  valcommand.ReplaceAll("pid:","");
	  valcommand.ReplaceAll(";","");
	  valcommand.ReplaceAll(" ","");
	  printf("Particle ID for final states particles: ");
	  for (int i=0; i<fData.npart -1; i++) {
	    poscomma = valcommand.First(",");
	    valc2 = valcommand(0,poscomma-1);
	    fData.pid[i] = valc2.Atoi();
	    valcommand.Replace(0,poscomma,"");
	    printf(" %d",fData.pid[i]);
	  }
	  fData.pid[fData.npart -1] = valcommand.Atoi();
	   printf(" %d \n",fData.pid[fData.npart -1]);
	}
	if (valcommand.Contains("nvertex")) {
	  valcommand.ReplaceAll("nvertex:","");
	  valcommand.ReplaceAll(";","");
	  valcommand.ReplaceAll(" ","");
	  fData.nvertex = valcommand.Atoi();
	  printf("Number of vertexes: %d\n",fData.nvertex);
	}
	if (valcommand.Contains("vertex")) {
	  valcommand.ReplaceAll("vertex:","");
	  valcommand.ReplaceAll(";","");
	  valcommand.ReplaceAll(" ","");
	  valc2 = valcommand(0,valcommand.First(","));
	  fData.overt[atvertex] = valc2.Atoi();
	  valc2 = valcommand(valcommand.First(",")+1,valcommand.Length());
	  fData.npvert[atvertex] = valc2.Atoi();
	  printf("Origin vertex particle n.: %d    Number of particles at this vertex: %d \n",fData.overt[atvertex],fData.npvert[atvertex]);
	  
	}
	if (valcommand.Contains("v_type")) {
	  valcommand.ReplaceAll("v_type:","");
	  valcommand.ReplaceAll(";","");
	  valcommand.ReplaceAll(" ","");
	  valc2 = valcommand(0,valcommand.First(","));
	  fData.v_type[atvertex] = valc2.Atoi();
	  printf("%s",valc2.Data());
	  valc2 = valcommand(valcommand.First(",")+1,valcommand.Length());
	  fData.v_ratio[atvertex] = valc2.Atof();
	  printf("Vertex type=%i , Vertex ratio=%.2f \n",fData.v_type[atvertex],fData.v_ratio[atvertex]);
	  if (fData.v_type[atvertex] != 1) {
	    printf("vertex n. %i type not supported \n",atvertex+1);
	    exit(1);
	  }
	  atvertex++;
	}
	if (valcommand.Contains("output")) {
	  valcommand.ReplaceAll("output:","");
	  valcommand.ReplaceAll(";","");
	  valcommand.ReplaceAll(" ","");
	  fData.out_fmt = valcommand.Atoi();
	  printf("Output format n.: %d\n",fData.out_fmt);
	  exit(1);
	}

      }
    }
    if (atvertex!=fData.npart) printf("Number of reqeusted vertexes is %i, but format written for just %i vertexes",fData.npart, atvertex);


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
