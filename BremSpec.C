#include "./includes.h"
#include <fstream>

void BremSpec(){

TF1* fBrem = new TF1("fBrem", "1000000*1/x", 300, 1557); // Define Bremsstrahlung function
TH1D* Brem = new TH1D("Brem", "Bremsstrahlung Spectra", 353, 300, 1557); // Define a histogram
Brem -> FillRandom("fBrem", 1000000); // Randomly fill Bremsstahlung histogram
Brem->Draw();
Brem->SaveAs("BremSpec_300_1557.png");
 Brem->SaveAs("BremSpec_300_1557.root");

std::ofstream ofs ("BremSpec_300_1557.txt", std::ofstream::out); // Define new text file to save spectrum to

// EdGen requires input energies in GeV
for(Int_t i = 0; i < ((Brem->GetSize())-2); i++){ // Go through all bins

    // Prints low edge, high edge and value of each bin to txt file
    ofs << Brem->GetBinLowEdge(i+1)/1000 << "\t" << (Brem->GetBinLowEdge(i+1) + Brem->GetBinWidth(i+1))/1000 << "\t" << Brem->GetBinContent(i+1) << endl;
    // cout << Brem->GetBinLowEdge(i+1) << "\t" << (Brem->GetBinLowEdge(i+1) + Brem->GetBinWidth(i+1)) << "\t" << Brem->GetBinContent(i+1) << endl;

    }

ofs.close(); // Close output file

}


// Works as intended BUT not sure of the function is correct!
// Need to refine Bremsstrahlung function before use but the drawing/saving stuff works
// exactly as needed.
// Change from tab separated to space separated?
// Will EdGen care?
