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
    lumiWeights_ = 0;
    xsec_ = -999; 
    lumi_ = -999;
}

///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////

Sample::Sample(TString ifilename, TString iname)
{
    filename_ = ifilename;
    name_ = iname;
    treename_ = TString("dimuons/tree");
    file_ = new TFile(filename);
    tree_ = (TTree*)file->Get(treename);
    N_ = tree->GetEntries();

    lumiWeights_ = 0;
    xsec_ = -999; 
    lumi_ = -999;
    
    setBranchAddresses();
    calculateNoriginal();
}

///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////

Sample::Sample(TString ifilename, TString iname, TString isampleType)
{
    filename_ = ifilename;
    name_ = iname;
    sampleType_ = isampleType;
    treename_ = TString("dimuons/tree");
    file_ = new TFile(filename);
    tree_ = (TTree*)file->Get(treename);
    N_ = tree->GetEntries();

    lumiWeights_ = 0;
    xsec_ = -999; 
    lumi_ = -999;
    
    setBranchAddresses();
    calculateNoriginal();
}

///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////

Sample::~Sample() {
  // free pointed to memory!
  if (tree != 0) {
    delete tree_;
  }
  if (file !=0) {
    delete file_;
  }
  if (lumiWeights !=0) {
    delete lumiWeights_;
  }
}

///////////////////////////////////////////////////////////////////////////
// _______________________Other Functions________________________________//
///////////////////////////////////////////////////////////////////////////

void Sample::setBranchAddresses()
{
    tree_->SetBranchAddress("recoCandMass", &vars.recoCandMass);
    tree_->SetBranchAddress("nPU", &vars.nPU);
    tree_->SetBranchAddress("recoCandPt", &vars.recoCandPt);
    tree_->SetBranchAddress("vertexInfo", &vars.vertices);
    tree_->SetBranchAddress("eventInfo", &vars.eventInfo);
    tree_->SetBranchAddress("reco1", &vars.reco1);
    tree_->SetBranchAddress("reco2", &vars.reco2);
    tree_->SetBranchAddress("genWeight", &vars.genWeight);
    tree_->SetBranchAddress("pfJets", &vars.jets);
    tree_->SetBranchAddress("met", &vars.met);
    tree_->SetBranchAddress("recoCandMassPF", &vars.recoCandMassPF);
    tree_->SetBranchAddress("recoCandPtPF", &vars.recoCandPtPF);
    tree_->SetBranchAddress("rho", &vars.rho);
}
///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////

void Sample::calculateNoriginal()
{
// Calculate the number of original events using the meta data tree
// Calculate the weighted number of original events as well
    TTree* metadata = (TTree*)file_->Get("dimuons/metadata");
    metadata->Draw("sumEventWeights>>eweights_"+name);
    TH1F* sumEventWeightsHist = (TH1F*) gDirectory->Get("eweights_"+name); 

    // There are many ttrees combined so the histogram has a numEvents entry for each
    // file. The total number is equal to the average number times the total number of entries.
    nOriginalWeighted_ = sumEventWeightsHist->GetEntries()*sumEventWeightsHist->GetMean();

    metadata->Draw("originalNumEvents>>nevents_"+name);
    TH1F* nEventsHist = (TH1F*) gDirectory->Get("nevents_"+name); 
    nOriginal_ = nEventsHist->GetEntries()*nEventsHist->GetMean();
    if(metadata !=0) delete metadata;
}

///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////

int Sample::getEntry(int i)
{
    tree_->GetEntry(i);
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
    if(sampleType_.Contains("data")) return 1.0;
    else return 1.0*vars_.genWeight*lumiWeights->weight(vars.nPU);
    //else return 1.0*vars.genWeight;
}

///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////

float Sample::getScaleFactor(float luminosity)
{
// Scale the MC histograms based upon the data luminosity, the number of events
// that the CMSSW analyzer looked at, and the xsec for the process
    if(sampleType.Contains("data")) return 1.0;
    else return luminosity*xsec_/nOriginalWeighted_;
}

///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////

float Sample::getScaleFactor(float luminosity, float reductionFactor)
{
// Scale the MC histograms based upon the data luminosity, the number of events
// that the CMSSW analyzer looked at, and the xsec for the process
    if(sampleType.Contains("data")) return 1.0;
    else return luminosity*xsec_/nOriginalWeighted_;
}
