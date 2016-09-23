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
   TH1F* dimuonMassHist = new TH1F("dimuonMassHist","Mass (#mu#mu)",50,60,120);
   setHistTitles(dimuonMassHist,"M(#mu#mu) [GeV/c^{2}]","Events");
   dimuonMassHist->Sumw2();

   // Plot the Dimuon Pt
   TH1F* dimuonPtHist = new TH1F("dimuonPtHist","P_{T} (#mu#mu)",100,0,2000);
   setHistTitles(dimuonPtHist,"P_{T}(#mu#mu) [GeV/c]","Events");
   dimuonPtHist->SetStats(1);
   dimuonPtHist->Sumw2();

   // Plot the 1/mumuPt
   TH1F* inverseDiMuPtHist = new TH1F("inverseDiMuPtHist","Inverse P_{T} (#mu#mu)",100,0,0.02);
   setHistTitles(inverseDiMuPtHist,"1/P_{T}(#mu#mu) [c/GeV]","Events");
   inverseDiMuPtHist->SetStats(1);
   inverseDiMuPtHist->Sumw2();

   // Plot Pt difference
   TH1F* diffMuPtHist = new TH1F("diffMuPtHist","#Delta P_{T} (#mu)",100,0,200);
   setHistTitles(diffMuPtHist,"P_{T}(#mu) [GeV/c]","Events");
   diffMuPtHist->SetStats(1);
   diffMuPtHist->Sumw2();

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
	//std::cout << "inverseDiMuPt: " << sample->inverseDiMuPt[i] << std::endl;
	

        // fill histograms
        dimuonMassHist->Fill(sample->vars.recoCandMass, sample->getWeight() );
	dimuonPtHist->Fill(sample->vars.recoCandPt, sample->getWeight() );
	inverseDiMuPtHist->Fill(sample->inverseDiMuPt[i], sample->getWeight() );
	diffMuPtHist->Fill(sample->vars.reco1.pt - sample->vars.reco2.pt, sample->getWeight() );
	
   	////////////////////////////////////////////////////////////////////
   	// Scatter Plots----------------------------------------------------
   	////////////////////////////////////////////////////////////////////

   	// Plot reco 1 Pt vs reco 2 Pt
   	//TGraph
   }
   
   // Debugging
   std::cout << "Scale Factor: " << sample->getScaleFactor(luminosity) << std::endl;

   /////////////////////////////////////////////////////////////////////
   // Save Histogram Vector---------------------------------------------
   /////////////////////////////////////////////////////////////////////

   histo1D.push_back(dimuonMassHist);
   histo1D.push_back(dimuonPtHist);
   histo1D.push_back(inverseDiMuPtHist);
   histo1D.push_back(diffMuPtHist);

   /////////////////////////////////////////////////////////////////////
   // Scale Histograms--------------------------------------------------
   /////////////////////////////////////////////////////////////////////

   for(std::vector<TH1F*>::const_iterator itr = histo1D.begin(); itr != histo1D.end(); itr++){
	(*itr)->Scale(sample->getScaleFactor(luminosity) );
   }
	
   /////////////////////////////////////////////////////////////////////
   // Write Histograms--------------------------------------------------
   /////////////////////////////////////////////////////////////////////

   for(std::vector<TH1F*>::const_iterator itr = histo1D.begin(); itr != histo1D.end(); itr++){
	(*itr)->Write();
   }
}

//////////////////////////////////////////////////////////////////
//--------------------------------------------------------------//
//////////////////////////////////////////////////////////////////

void SampleHistos::setHistTitles(TH1F* hist, TString xtitle, TString ytitle)
{
  hist->GetXaxis()->SetTitle(xtitle);
  hist->GetYaxis()->SetTitle(ytitle);
}

//////////////////////////////////////////////////////////////////
//--------------------------------------------------------------//
//////////////////////////////////////////////////////////////////

void SampleHistos::closeFile()
{
   file->Close();
}

