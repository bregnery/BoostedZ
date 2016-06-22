#include <TSystem.h>
#include <TROOT.h>
#include <TClonesArray.h>
#include <TParticle.h>
#include <iostream>
#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TH2F.h>
#include <TH1F.h>
#include <TProfile.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <TLegend.h>
#include <TF1.h>
#include <TRandom3.h>
#include <algorithm>
#include <vector>
#include <TMath.h>
#include <TEntryList.h>
#include "src/DataFormats.h"
#include "src/helpers.h"
#include "src/SampleClass.h"
#include "src/SampleClass.cxx"
#include "Math/Functor.h"
#include "Math/GSLMinimizer1D.h"

void VariableHistogramer (TString inputFileName,TString outputFileName, bool isData, bool isSignal)
{
  using namespace std;

  ///////////////////
  // Configuration

  ///////////////////////////
  // Output Histograms
      
  setStyle();
          
  // Plots Mass of the Dimuons
  TH1F* dimuonMassHist = new TH1F("dimuonMassHist","",50,60,120);
  setHistTitles(dimuonMassHist,"M(#mu#mu) [GeV/c^{2}]","Events");
  dimuonMassHist->Sumw2();

  // Plots the Phi star variable
  TH1F* phiStarHist = new TH1F("phiStarHist","",50,0,1);
  setHistTitles(phiStarHist,"#phi *","Events");
  phiStarHist->SetStats(1);
  phiStarHist->Sumw2();

  // Plot the Phi star cross check
  TH1F* phiStarCheckHist = new TH1F("phiStarCheckHist","",50,0,1);
  setHistTitles(phiStarCheckHist,"#phi *","Events");
  phiStarCheckHist->SetStats(1);
  phiStarHist->Sumw2();

  // Plot the Dimuon Pt
  TH1F* dimuonPtHist = new TH1F("dimuonPtHist","",100,0,2000);
  setHistTitles(dimuonPtHist,"P_{T}(#mu#mu) [GeV/c]","Events");
  dimuonPtHist->SetStats(1);
  dimuonPtHist->Sumw2();

  // Plot the 1/mumuPt
  TH1F* inverseDiMuPtHist = new TH1F("inverseDiMuPtHist","",100,0,0.02);
  setHistTitles(inverseDiMuPtHist,"1/P_{T}(#mu#mu) [c/GeV]","Events");
  inverseDiMuPtHist->SetStats(1);
  inverseDiMuPtHist->Sumw2();

  ////////////////////////////
  Double_t MASS_MUON = 0.105658367;    //GeV/c2
   
  //////////////////////////
  // Tree Branches
  cout << "Analyzing filename: "<< inputFileName.Data() << endl;
  if (isData)
     cout << "isData\n";
  if (isSignal)
     cout << "isSignal\n";
  
  TChain * tree = new TChain("tree");
  tree->Add(inputFileName);
  TChain * metadata = new TChain("metadata");
  metadata->Add(inputFileName);

  // These are the names of the muons (See src/DataFormats.h for definitions!)
  _MuonInfo reco1, reco2;
  
  tree->SetBranchAddress("reco1", &reco1);
  tree->SetBranchAddress("reco2", &reco2);
  
  // These are the dimuon mass, pt, rapidity, and phi
  float recoCandMass, recoCandPt, recoCandY, recoCandPhi;
 
  tree->SetBranchAddress("recoCandMass",       &recoCandMass);
  tree->SetBranchAddress("recoCandPt",         &recoCandPt);
  tree->SetBranchAddress("recoCandY",          &recoCandY);
  tree->SetBranchAddress("recoCandPhi",        &recoCandPhi);
  
  // MC truth info
  float trueMass=-99999.0;
  if(!isData && tree->GetBranchStatus("trueMass"))
     tree->SetBranchAddress("trueMass", &trueMass);
  
  // Higgs Boson MC truth info (after FSR)
  _genPartInfo genHpostFSR;
  if(!isData && tree->GetBranchStatus("genHpostFSR"))
     tree->SetBranchAddress("genHpostFSR", &genHpostFSR);
  
  _TrackInfo reco1GenPostFSR;
  if(!isData && tree->GetBranchStatus("genM1HpostFSR"))
     tree->SetBranchAddress("genM1HpostFSR", &reco1GenPostFSR);
  
  _TrackInfo reco2GenPostFSR;
  if(!isData && tree->GetBranchStatus("genM2HpostFSR"))
     tree->SetBranchAddress("genM2HpostFSR", &reco2GenPostFSR);

  // the jet collection
  _PFJetInfo rawJets;
  tree->SetBranchAddress("pfJets",&rawJets);

  // Variables from Variable Stage
  float phiStar;
  float phiStarCheck;
  float inverseDiMuPt;
  tree->SetBranchAddress("phiStar",&phiStar);
  tree->SetBranchAddress("phiStarCheck",&phiStarCheck);
  tree->SetBranchAddress("inverseDiMuPt",&inverseDiMuPt);

  // number of events
  unsigned nEvents = tree->GetEntries();
  unsigned reportEach = 100000;
  if (nEvents/100000 > reportEach)
     reportEach = nEvents/100000;

  // Calculate Scale Factors for MC
  double scaleFactor = 1;
  double luminosity = 2169;
  if (isData == false){
	Sample MCsample = Sample(inputFileName, outputFileName, tree, metadata);
	scaleFactor = MCsample.getScaleFactor(luminosity);
  } 

  ///////////////////////////////
  // Event Loop
        
  for(unsigned i=0; i<nEvents;i++)
  { 
    tree->GetEvent(i);
    if (i % reportEach == 0) cout << "Event: " << i << endl;
  
    // Reject events with invalid muons
    if (reco1.pt < 0. || reco2.pt < 0.)
      continue;
                                                      
    // Order muons by pt
    if (reco1.pt < reco2.pt)
    {
      _MuonInfo tmpMuon = reco1;
      reco1 = reco2;
      reco1 = tmpMuon;
    }
    
    /////////////////////
    // Selection Criteria

    // Dimuon Mass Selection
    if (recoCandMass >= 60 && recoCandMass <= 120){

       // Error testing for inverse DiMu Pt
       inverseDiMuPt = 1 / recoCandPt;
    
       /////////////////////
       // Fill Histograms
       dimuonMassHist->Fill(recoCandMass, scaleFactor);
       phiStarHist->Fill(phiStar, scaleFactor);
       phiStarCheckHist->Fill(phiStarCheck, scaleFactor);
       dimuonPtHist->Fill(recoCandPt, scaleFactor);
       inverseDiMuPtHist->Fill(inverseDiMuPt, scaleFactor);
    }
  }

  TFile* outFile = new TFile(outputFileName,"RECREATE");
  outFile->cd();
  dimuonMassHist->Write();
  phiStarHist->Write();
  phiStarCheckHist->Write();
  dimuonPtHist->Write();
  inverseDiMuPtHist->Write();
  outFile->Close();
}
