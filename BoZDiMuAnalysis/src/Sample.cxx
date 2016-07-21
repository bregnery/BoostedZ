///////////////////////////////////////////////////////////////////////////
//                             Sample.cxx                                //
//=======================================================================//
//                                                                       //
//        Keeps track of the sample information. TTree, xsec, etc.       //
//                                                                       //
///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
// _______________________Includes_______________________________________//
///////////////////////////////////////////////////////////////////////////

#include "Sample.h"

///////////////////////////////////////////////////////////////////////////
// _______________________Constructor/Destructor_________________________//
///////////////////////////////////////////////////////////////////////////

Sample::Sample() 
{
    lumiWeights = 0;
    xsec = -999; 
    lumi = -999;
}

///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////

Sample::Sample(TString infilename, TString iname, TString insampleType)
{
    filename = infilename;
    name = iname;
    sampleType = insampleType;
    treename = TString("dimuons/tree");
    file = new TFile(infilename);
    tree = (TTree*)file->Get(treename);
    //outFile = new TFile(iname + "_StageVar.root", "RECREATE");
    //outFile->cd();
    //outTree = new TTree("outTree","RECREATE");
    //outTree = tree->CloneTree();
    nEvents = tree->GetEntries();

    lumiWeights = 0;
    xsec = -999; 
    lumi = -999;
 
    setBranchAddresses();
    calculateNoriginal();
    orderMuons();
    setAdditionalVariables();
}

///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////

Sample::~Sample() {
  // free pointed to memory!
  if (tree != 0) {
    delete tree;
  }
  if (file !=0) {
    delete file;
  }
  if (lumiWeights !=0) {
    delete lumiWeights;
  }
}

///////////////////////////////////////////////////////////////////////////
// _______________________Other Functions________________________________//
///////////////////////////////////////////////////////////////////////////

void Sample::setBranchAddresses()
{
    tree->SetBranchAddress("recoCandMass", &vars.recoCandMass);
    tree->SetBranchAddress("nPU", &vars.nPU);
    tree->SetBranchAddress("recoCandPt", &vars.recoCandPt);
    tree->SetBranchAddress("recoCandY", &vars.recoCandY);
    tree->SetBranchAddress("recoCandPhi",&vars.recoCandPhi);
    tree->SetBranchAddress("vertexInfo", &vars.vertices);
    tree->SetBranchAddress("eventInfo", &vars.eventInfo);
    tree->SetBranchAddress("reco1", &vars.reco1);
    tree->SetBranchAddress("reco2", &vars.reco2);
    tree->SetBranchAddress("genWeight", &vars.genWeight);
    tree->SetBranchAddress("pfJets", &vars.jets);
    tree->SetBranchAddress("met", &vars.met);
    tree->SetBranchAddress("recoCandMassPF", &vars.recoCandMassPF);
    tree->SetBranchAddress("recoCandPtPF", &vars.recoCandPtPF);
    tree->SetBranchAddress("recoCandYPF", &vars.recoCandYPF);
    tree->SetBranchAddress("recoCandPhiPF", &vars.recoCandPhiPF);
    tree->SetBranchAddress("rho", &vars.rho);
}

///////////////////////////////////////////////////////////////////////////////
////-----------------------------------------------------------------------------
/////////////////////////////////////////////////////////////////////////////////

void Sample::setAdditionalVariables()
{
    for(unsigned i=0; i<nEvents; i++){
	getEntry(i);
	// Calculate inverse Dimuon Pt for each event
	inverseDiMuPt.push_back (1 / vars.recoCandPt);
	// Calculate the eta difference between the muons
	// for each event
	deltaEta.push_back(TMath::Abs(vars.reco1.eta - vars.reco2.eta));
		
	// Debugging
	//std::cout << "inverseDiMuPt: " << inverseDiMuPt[i] << std::endl;
    }
}

///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////

void Sample::calculateNoriginal()
{
// Calculate the number of original events using the meta data tree
// Calculate the weighted number of original events as well
    TTree* metadata = (TTree*)file->Get("dimuons/metadata");
    metadata->Draw("sumEventWeights>>eweights_"+name);
    TH1F* sumEventWeightsHist = (TH1F*) gDirectory->Get("eweights_"+name); 

    // There are many ttrees combined so the histogram has a numEvents entry for each
    // file. The total number is equal to the average number times the total number of entries.
    nOriginalWeighted = sumEventWeightsHist->GetEntries()*sumEventWeightsHist->GetMean();

    metadata->Draw("originalNumEvents>>nevents_"+name);
    TH1F* nEventsHist = (TH1F*) gDirectory->Get("nevents_"+name); 
    nOriginal = nEventsHist->GetEntries()*nEventsHist->GetMean();
    if(metadata !=0) delete metadata;
}

///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////


void Sample::orderMuons(){
// Orders reco1 and reco2 muons based on Pt
     for(unsigned i=0; i<nEvents; i++){
       if (vars.reco1.pt < vars.reco2.pt)
       {
            _MuonInfo tmpMuon = vars.reco1;
           vars.reco1 = vars.reco2;
           vars.reco1 = tmpMuon;
       }
     }
}

/*
///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////

void Sample::addBranch(float newVar, TString newVarName, TBranch* newVarBranch){
// makes a new branch in the output tree
// this branch has a leaf containing a floating point variable
     newVarBranch = outTree->Branch(newVarName, &newVar, newVarName + "/F");
}
*/

///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////

int Sample::getEntry(int i)
{
    tree->GetEntry(i);
    return i;
}

///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////

int Sample::getEntry(int i, TEntryList* list)
{
    int treenum = list->GetEntry(i);
    tree->GetEntry(treenum);
    return treenum;
}

///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////


float Sample::getWeight()
{
// Assumes getEntry has already been called to load the appropriate values.
// Gets the weight for the histogram depending on the sample type 
     if(sampleType.Contains("data")) return 1.0;
     else return 1.0*vars.genWeight*lumiWeights->weight(vars.nPU);
     //else return 1.0*vars.genWeight;
}

///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////

float Sample::getScaleFactor(float luminosity)
{
// Scale the MC histograms based upon the data luminosity, the number of events
// that the CMSSW analyzer looked at, and the xsec for the process
      // Debugging
      //if(sampleType.Contains("data")) std::cout << "data" << std::endl;

      if(sampleType.Contains("data")) return 1.0;
      else return luminosity*xsec/nOriginalWeighted;
}

/*
///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////

void Sample::getOutFile(){
// Creates an output file
// Saves the output tree in this file
      outTree->Write();
      outFile->Close();
}
*/

