#define new_analysis_cxx
// The class definition in new_analysis.h has been generated automatically
// by the ROOT utility TTree::MakeSelector(). This class is derived
// from the ROOT class TSelector. For more information on the TSelector
// framework see $ROOTSYS/README/README.SELECTOR or the ROOT User Manual.

// The following methods are defined in this file:
//    Begin():        called every time a loop on the tree starts,
//                    a convenient place to create your histograms.
//    SlaveBegin():   called after Begin(), when on PROOF called only on the
//                    slave servers.
//    Process():      called for each event, in this function you decide what
//                    to read and fill your histograms.
//    SlaveTerminate: called at the end of the loop on the tree, when on PROOF
//                    called only on the slave servers.
//    Terminate():    called at the end of the loop on the tree,
//                    a convenient place to draw/fit your histograms.
//
// To use this file, try the following session on your Tree T:
//
// Root > T->Process("new_analysis.C")
// Root > T->Process("new_analysis.C","some options")
// Root > T->Process("new_analysis.C+")
//

#include "new_analysis.h"
#include <TH2.h>
#include <TStyle.h>


void new_analysis::Begin(TTree * /*tree*/)
{
   // The Begin() function is called at the start of the query.
   // When running with PROOF Begin() is only called on the client.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();

}

void new_analysis::SlaveBegin(TTree * /*tree*/)
{
   // The SlaveBegin() function is called after the Begin() function.
   // When running with PROOF SlaveBegin() is called on each slave server.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();
   h1_vz =  new TH1F("h1_vz","Vertex Z for the recoiling target",100,-5,5);
   h1_E = new TH1F("h1_E","kinetic Energy spectrum for the recoiling target",100,0.,2.);
   h1_masspi0 = new TH1F("h1_masspi0","Mass #pi^0 from #pi^0",100,0.,0.3);
   h1_mass2gamma = new TH1F("h1_mass2gamma","Mass #pi^0 from #pi^0",100,0.,0.3);


   fOutput->Add(h1_vz);
   fOutput->Add(h1_E);
   fOutput->Add(h1_masspi0);
   fOutput->Add(h1_mass2gamma);

}

Bool_t new_analysis::Process(Long64_t entry)
{
   // The Process() function is called for each entry in the tree (or possibly
   // keyed object in the case of PROOF) to be processed. The entry argument
   // specifies which entry in the currently loaded tree is to be processed.
   // It can be passed to either new_analysis::GetEntry() or TBranch::GetEntry()
   // to read either all or the required parts of the data. When processing
   // keyed objects with PROOF, the object is already loaded and is available
   // via the fObject pointer.
   //
   // This function should contain the "body" of the analysis. It can contain
   // simple or elaborate selection criteria, run algorithms on the data
   // of the event and typically fill histograms.
   //
   // The processing can be stopped by calling Abort().
   //
   // Use fStatus to set the return value of TTree::Process().
   //
   // The return value is currently not used.
  b_Ef->GetEntry(entry);
  b_pf->GetEntry(entry);
  b_vx->GetEntry(entry);
  b_vy->GetEntry(entry);
  b_vz->GetEntry(entry);
  b_px->GetEntry(entry);
  b_py->GetEntry(entry);
  b_pz->GetEntry(entry);


  h1_vz->Fill(vz[0]);
  h1_E->Fill(pf[0]);
  h1_masspi0->Fill(pow(pow(Ef[1],2)-pow(pf[1],2),0.5));
  TLorentzVector v4_gamma1(px[2],py[2],pz[2],Ef[2]);
  TLorentzVector v4_gamma2(px[3],py[3],pz[3],Ef[3]);

  TLorentzVector v4_pi0 = v4_gamma1 + v4_gamma2;
  h1_mass2gamma->Fill(v4_pi0.M());

   return kTRUE;
}

void new_analysis::SlaveTerminate()
{
   // The SlaveTerminate() function is called after all entries or objects
   // have been processed. When running with PROOF SlaveTerminate() is called
   // on each slave server.

}

void new_analysis::Terminate()
{
   // The Terminate() function is the last function to be called during
   // a query. It always runs on the client, it can be used to present
   // the results graphically or save the results to file.

  TFile file_out("analysis_output.root","recreate");
  TList *outlist = GetOutputList();
  
  outlist->Write();
  file_out.Write();
  file_out.Close();


}
