#include "EdOutput.h"

EdOutput::EdOutput(EdInput *inp, const char *fileout){
    char defaultname[255] = "output.root";

    if( fileout ){
	strcpy(fOutName, fileout);
    } else {
	strcpy(fOutName, defaultname);
    }
    printf("output file set as %s\n", fOutName);

    fTree = new TTree("T", "HG Monte Carlo");
    fNevt    = ((double) inp->GetNevt());
    n_part = inp->GetNpart();

    InitTree();

    return;
}

EdOutput::~EdOutput(){
    delete fTree;

    return;
}

void EdOutput::InitTree(){
    fTree->Branch("n_part", &n_part, "n_part/I");
    fTree->Branch("theta", theta, "theta[n_part]/D");
  
    fTree->Branch("phi", phi, "phi[n_part]/D");
    fTree->Branch("x", &x, "x/D");
    fTree->Branch("Ef", Ef, "Ef[n_part]/D");
 
    fTree->Branch("Q2", &Q2, "Q2/D");
    fTree->Branch("nu", &nu, "nu/D");

    fTree->Branch("W", &W, "W/D");
    fTree->Branch("y", &y, "y/D");

  
    fTree->Branch("Z_ion", &Z_ion, "Z_ion/I");
    fTree->Branch("N_ion", &N_ion, "N_ion/I");
    
    fTree->Branch("particle_id", particle_id, "particle_id[n_part]/I");
    fTree->Branch("charge", charge, "charge[n_part]/I");

    fTree->Branch("pf", pf, "pf[n_part]/D");
    fTree->Branch("px", px, "px[n_part]/D");
    fTree->Branch("py", py, "py[n_part]/D");
    fTree->Branch("pz", pz, "pz[n_part]/D");

    fTree->Branch("vx", &vx, "vx[n_part]/D");
    fTree->Branch("vy", &vy, "vy[n_part]/D");
    fTree->Branch("vz", &vz, "vz[n_part]/D");

    fTree->Branch("weight", &weight, "weight/D");


    return;
}

void EdOutput::SetTheta( double *val, int tot){
  for (int i =0; i<tot; i++) {
    theta[i] = val[i];
  }
  n_part = tot;
}
void EdOutput::SetPhi(double *val, int tot){
  for (int i =0; i<tot; i++) {
    phi[i] = val[i];
  }
}
void EdOutput::SetEf(double *val, int tot){
  for (int i =0; i<tot; i++) {
    Ef[i] = val[i];
  }

}
void EdOutput::Setpf(double *val, int tot){
  for (int i =0; i<tot; i++) {
    pf[i] = val[i];
  }

}
void EdOutput::Setpx(double *val, int tot){
  for (int i =0; i<tot; i++) {
    px[i] = val[i];
  }

}
void EdOutput::Setpy(double *val, int tot){
  for (int i =0; i<tot; i++) {
    py[i] = val[i];
  }

}
void EdOutput::Setpz(double *val, int tot){
  for (int i =0; i<tot; i++) {
    pz[i] = val[i];
  }

}
void EdOutput::Setparticle_id(int *val, int tot){
  for (int i =0; i<tot; i++) {
    particle_id[i] = val[i];
  }

}
void EdOutput::Setcharge(int *val, int tot){
  for (int i =0; i<tot; i++) {
    charge[i] = val[i];
  }

}
void EdOutput::Setvx(double *val, int tot){
  for (int i =0; i<tot; i++) {
    vx[i] = val[i];
  }

}
void EdOutput::Setvy(double *val, int tot){
  for (int i =0; i<tot; i++) {
    vy[i] = val[i];
  }

}
void EdOutput::Setvz(double *val, int tot){
  for (int i =0; i<tot; i++) {
    vz[i] = val[i];
  }

}
void EdOutput::Setweight(double *val, int tot){
  for (int i =0; i<tot; i++) {
    weight[i] = val[i];
  }

}
void EdOutput::Settowrite(int *val, int tot){
  for (int i =0; i<tot; i++) {
    towrite[i] = val[i];
  }

}

void EdOutput::Write(){
    fTree->Fill();

    return;
}

void EdOutput::Close(){
    fOutfile = new TFile(fOutName, "RECREATE");
    fTree->Write();
    fOutfile->Close();
    delete fOutfile;

    return;
}

void  EdOutput::MakeFileLUND(){


  

  TString file(fOutName);
  file.ReplaceAll("root","lund"); 


  
  Int_t nentries = (Int_t)fTree->GetEntries();
  int tot_part = 0;
  for (int j=0; j<n_part; j++) {
    tot_part = tot_part +towrite[j];
  }

  double vxcm,vycm,vzcm;

  ofstream OUT (file.Data());
  for (int i=0; i<nentries ; i++) {
    fTree->GetEntry(i);
    if(i % 1000000 == 0 ){
      printf("Analyzed %09d events of total %09d \n",i,nentries);
    }
    
    OUT << tot_part << " \t " << (Z_ion + N_ion)  << " \t " << Z_ion  << " \t " << "0"  << " \t " << "0" << " \t "  << x << " \t " << y  << " \t " << W  << " \t " << Q2  << " \t " << nu << endl;
    for (int j=0; j<n_part; j++) {
      if (towrite[j] == 1) {
	vxcm = vx[j]*100.0;
	vycm = vy[j]*100.0;
	vzcm = vz[j]*100.0;
	OUT << " \t " << "1" << " \t " << charge[j] << " \t " << "1" << " \t " << particle_id[j] << " \t " << "0" << " \t " << "0" << " \t " << px[j] << " \t " << py[j] << " \t " << pz[j] << " \t " << Ef[j] << " \t " << "0" << " \t " << vzcm  << " \t " << vycm << " \t " << vzcm << endl;
      }
    }
  }

  OUT.close();

}


void  EdOutput::MakeFileBOS(){


  

  TString file(fOutName);
  file.ReplaceAll("root","bos"); 
  int AutoOutputUnitNo = 12; // unit to open for writing (!?!?!?!? FORTRAN)
  int maxFileLength = 2000000;  // Maximum length of the bos file (bos files can be maximum this size)
  int nFileWrite = 0;

  char out[100];
  char mess[100];

  Int_t nentries = (Int_t)fTree->GetEntries();
  int tot_part = 0;
  for (int j=0; j<n_part; j++) {
    tot_part = tot_part +towrite[j];
  }

  double vxcm,vycm,vzcm;


  printf("Output Bos file: %s\n",file.Data());
  unlink(file.Data());
  sprintf(out, "OPEN AUTOOUTPUT UNIT=%d FILE=\"%s\" WRITE STATUS=NEW RECL=32768", AutoOutputUnitNo, file.Data());
  if (!fparm_c(out)) {
    printf("Unable to open file \'%s\': %s\n\n",out,strerror(errno));
    exit(1);
  }
  //  bosInit( bcs_.iw, NBCS ); // bosio format
  initbos(); // c_bos_io format
  formatBank('HEAD','I');
  formatBank('MCTK','(6F,5I)');
  formatBank('MCVX','(4F,I)');

  bankList(&bcs_, "C=","HEADMCTKMCVX");  // Write HEAD MCTK MCVX banks into the bos file




  for (int i=0; i<nentries ; i++) {
    fTree->GetEntry(i);
    if(i % 1000000 == 0 ){
      printf("Analyzed %09d events of total %09d \n",i,nentries);
    }
    
    // Filling the array for bcs_ from the TTree
    makeBank(&bcs_,"HEAD",0,8,1); // void *makeBank(BOSbank *bcs, char *bankname, int banknum, int ncol, int nrow)
    makeBank(&bcs_,"MCTK",1,11,(tot_part+1)); // void *makeBank(BOSbank *bcs, char *bankname, int banknum, int ncol, int nrow)  
    makeBank(&bcs_,"MCVX",2,5,1); // void *makeBank(BOSbank *bcs, char *bankname, int banknum, int ncol, int nrow)
    // Writing into bos file
    
    putBOS(&bcs_, AutoOutputUnitNo, "C");

    if (fileLength("AUTOOUTPUT") > maxFileLength) {
      /*close file*/
      putBOS(&bcs_, AutoOutputUnitNo, "0");
      sprintf(mess,"CLOSE AUTOOUTPUT UNIT=%d", AutoOutputUnitNo);
      fparm_c(mess);
      sprintf(out,"_%d.bos",nFileWrite);
      file.ReplaceAll(".bos",out);
      nFileWrite++;
      /* if -j option was present, issue PutFile command */
      fprintf(stderr,"Output file: %s\n",file.Data());
      unlink(file.Data());
      sprintf(out, "OPEN AUTOOUTPUT UNIT=%d FILE=\"%s\" WRITE STATUS=NEW RECL=32768", AutoOutputUnitNo, outfile);
      if (!fparm_c(out)) {
	printf("Unable to open file \'%s\': %s\n\n",out,strerror(errno));
	exit(1);
      }
    }



  }

}
