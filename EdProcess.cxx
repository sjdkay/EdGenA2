#include "EdProcess.h"

EdProcess::EdProcess(const char *file, char *file2){

    finp   = new EdInput(file);
    fout  = new EdOutput(finp,file2);
    fmodel = new EdModel(finp);
    fphy  = new EdPhysics(fmodel);
   
 
    return;
}

void EdProcess::Run(){
    int nevt = finp->GetNevt();

    printf("nevt = %d\n", nevt);

    int evt;
    int nprnt = finp->GetNprnt();
    TString fmtst[2];    
    fmtst[0] = "ROOT";
    fmtst[1] = "ROOT and A2";
    int fmt = finp->Get_fmt();
 
    for( evt = 0; evt < nevt; evt++ ){
      if( (evt%nprnt) == 0 ){printf("Event %10d \n", evt);}
      fphy->MakeEvent(fout, fmodel);
    }
    if (fmt == 2 ) { // also LUND format 
      printf("Creating LUND output \n") ;
      fout->MakeFileA2();
    }


    fout->Close();


    

    return;
}

EdProcess::~EdProcess(){
    return;
}
