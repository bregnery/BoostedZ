// Keeps track of some sample information
// Extremely helpful for calculating scale factors

#include "SampleClass.h"

Sample::Sample() 
{
    xsec = -999; 
}

Sample::Sample(TString infilename, TString inname, TTree *intree, TTree *inmetadata)
{
    filename = infilename;
    name = inname;
    tree = intree;

    if(filename == TString("DY_13TeV_stageVar.root")) xsec = 6025.2; // pb
    else if(filename == TString("TT_13TeV_stageVar.root")) xsec = 831.76; // pb
    else xsec = -999; 
    
    calculateNoriginal(&inmetadata);
}

Sample::~Sample() {
  // free pointed to memory!
  if (tree != 0) {
    delete tree;
  }
  if (metadata != 0) {
    delete metadata;
  }
}

void Sample::calculateNoriginal(TTree *inmetadata)
{
// Calculate the number of original events using the meta data tree
// Calculate the weighted number of original events as well
    metadata = inmetadata;
    metadata->Draw("sumEventWeights>>eweights_"+name);
    TH1F* sumEventWeightsHist = (TH1F*) gDirectory->Get("eweights_"+name); 

    // There are many ttrees combined so the histogram has a numEvents entry for each
    // file. The total number is equal to the average number times the total number of entries.
    nOriginalWeighted = sumEventWeightsHist->GetEntries()*sumEventWeightsHist->GetMean();

    metadata->Draw("originalNumEvents>>nevents_"+name);
    TH1F* nEventsHist = (TH1F*) gDirectory->Get("nevents_"+name); 
    nOriginal = nEventsHist->GetEntries()*nEventsHist->GetMean();
}

float Sample::getScaleFactor(float luminosity)
{
// Scale the MC histograms based upon the data luminosity, the number of events
// that the CMSSW analyzer looked at, and the xsec for the process
   return luminosity*xsec/nOriginalWeighted;
}
