/////////////////////////////////////////////////////////////////////
//                         SampleHistos.cxx                        //
//=================================================================//
//                                                                 //
// Contains functions for producing th analysis's histograms       //
/////////////////////////////////////////////////////////////////////

#include "SampleHistos.h"

///////////////////////////////////////////////////////////////////////
//_________________________Sample Histograms_________________________//
///////////////////////////////////////////////////////////////////////

SampleHistos::SampleHistos(){}

///////////////////////////////////////////////////////////////////////
//-------------------------------------------------------------------//
///////////////////////////////////////////////////////////////////////

SampleHistos::SampleHistos(Sample* sample, std::vector<bool> isCut, TString cutName, float luminosity)
{
   using namespace std;

   ///////////////////////////////////////////////////////////////////
   // Output file-----------------------------------------------------
   ///////////////////////////////////////////////////////////////////

   file = new TFile(sample->name + "_" + cutName + "_Hist.root", "RECREATE");
   file->cd();

   ///////////////////////////////////////////////////////////////////
   // Histograms------------------------------------------------------
   ///////////////////////////////////////////////////////////////////

   // Plots Mass of the Dimuons
   TH1F* dimuonMassHist = new TH1F("dimuonMassHist","",50,60,120);
   setHistTitles(dimuonMassHist,"M(#mu#mu) [GeV/c^{2}]","Events");
   dimuonMassHist->Sumw2();

   // Plot the Dimuon Pt
   TH1F* dimuonPtHist = new TH1F("dimuonPtHist","",100,0,2000);
   setHistTitles(dimuonPtHist,"P_{T}(#mu#mu) [GeV/c]","Events");
   dimuonPtHist->SetStats(1);
   dimuonPtHist->Sumw2();

   // Plot the 1/mumuPt
   TH1F* inverseDiMuPtHist = new TH1F("inverseDiMuPtHist","",100,0,0.2);
   setHistTitles(inverseDiMuPtHist,"1/P_{T}(#mu#mu) [c/GeV]","Events");
   inverseDiMuPtHist->SetStats(1);
   inverseDiMuPtHist->Sumw2();

   ////////////////////////////////////////////////////////////////////
   // Fill Histograms--------------------------------------------------
   ////////////////////////////////////////////////////////////////////

   unsigned reportEach = 1000000;

   // Event loop
   for(unsigned i=0; i<sample->nEvents; i++)
   {
	if(i % reportEach == 0) std::cout << "Event: " << i << std::endl;

	// Test if event passes the cut
	if(isCut[i] == false) continue;
	
	sample->getEntry(i);

	// Debugging
	//std::cout << "Mass: " << sample->vars.recoCandMass << std::endl;
	std::cout << "inverseDiMuPt: " << sample->inverseDiMuPt[i] << std::endl;
	

        // fill histograms
        dimuonMassHist->Fill(sample->vars.recoCandMass, sample->getScaleFactor(luminosity) );
	dimuonPtHist->Fill(sample->vars.recoCandPt, sample->getScaleFactor(luminosity) );
	inverseDiMuPtHist->Fill(sample->inverseDiMuPt[i], sample->getScaleFactor(luminosity) );
	
   }
  
   /////////////////////////////////////////////////////////////////////
   // Write Histograms--------------------------------------------------
   /////////////////////////////////////////////////////////////////////

   dimuonMassHist->Write();
   dimuonPtHist->Write();
   inverseDiMuPtHist->Write();
   file->Close();
}

//////////////////////////////////////////////////////////////////
//--------------------------------------------------------------//
//////////////////////////////////////////////////////////////////

void SampleHistos::setHistTitles(TH1F* hist, TString xtitle, TString ytitle)
{
  hist->GetXaxis()->SetTitle(xtitle);
  hist->GetYaxis()->SetTitle(ytitle);
}

