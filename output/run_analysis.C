{
  TProof::Open("");
  TChain *mc_edgen = new TChain("h1");
  mc_edgen->Add("output.root");
  mc_edgen->SetProof();
  mc_edgen->Process("analysis.C++");


}
