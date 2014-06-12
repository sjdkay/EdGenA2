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
