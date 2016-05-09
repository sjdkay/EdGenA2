#include "./includes.h"

// Attempt to fit 1/x^(?) fn to photon energy plot
// Currently results in a huge crash when used
// For some reason events at low photon energy are not copied into new histogram correctly
// define a function with 1 parameter
Double_t fitf(Double_t *x,Double_t *par)
{
    Double_t fitval = 0;
    fitval =  1/(Power(x, par[0]));
    return fitval;
}

void RealBremFit(){

  Double_t E;
  Double_t Energy;

  TF1 *RealBremFit = new TF1("RealBremFit",  fitf, 0, 900, 1); //Give a name and range to the fitting funcion
  RealBremFit->SetParLimits(1, 0, 10);
  TH1F* hist = new TH1F ("Bremsstrahlung Fit", "Real_Brem_Fit_Hist", 100, 100, 850);

  TFile *f = new TFile("/Disk/ds-sopa-group/np/thehubdata/thehub4/SKay/Data/Acqu_With_Vertex/Acqu_Run_Deuterium_March2013_445_renamed.root"); // Open the latest PTotal file to load histograms from
  TTree *t = (TTree*)f->Get("tagger");
  TBranch *b = t->GetBranch("taggedEnergy");
  t->SetBranchAddress("taggedEnergy", &E);

  for (Int_t i = 0; i < (b->GetEntryNumber()); i++){

    b->GetEvent(i);
    Energy = E;
    hist -> Fill(Energy);

  }

  Char_t* Title = "Bremsstrahlung Spectrum Fit; Real_Brem_Fit";

  TCanvas *canvas = new TCanvas("canvas","canvas",1000,10,550,400);

  f -> cd();

  TPad *pad1 = new TPad("pad1","",0,0,1,1);
  pad1->Draw();
  pad1->cd();

  pad1->SetTickx(1);
  pad1->SetTicky(1);
  pad1->SetGridx(1);
  pad1->SetGridy(1);

  TH1F  *hr;
  Char_t hrTitle[64];

  Float_t xMin = 0;
  Float_t xMax = 900;
  Float_t yMin = 0;
  Float_t yMax = 1500000;

  strcpy(hrTitle, Title);
  hr = canvas->DrawFrame(xMin,yMin,xMax,yMax);
  hr->SetTitle(hrTitle);

  hist->Draw("EHISTSAMES"); // Draw the histogram with errors
  hist->Fit("RealBremFit"); // Fit function to histogram using a log likelihood fit
  RealBremFit->SetLineColor(4);
  RealBremFit->Draw("SAMES"); // Draw the resulting fit
  gStyle->SetOptFit(0111);
  gPad->Update(); // Refresh plot

}

