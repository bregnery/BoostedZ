// Sample.h

#ifndef ADD_SAMPLE
#define ADD_SAMPLE

#include "TMath.h"
#include "TH1F.h"
#include "TFile.h"
#include "TTree.h"
#include "TEntryList.h"

#include "LumiReweightingStandAlone.h"
#include "VarSet.h"

class Sample
{
    private:
        TString name_;
        TString filename_;
        TString treename_;
        TTree* tree_;
        reweight::LumiReWeighting* lumiWeights_;  // Information for pileup reweighting 

        TString dir_;           // DAS directory
        TString pileupfile_;    // used for pile up reweighting through lumiWeights
        TString sampleType_;    // "data", "signal", "background"

        int plotColor_;         // the color used when plotting the sample
        int nOriginal_;         // the number of events run over to get this sample
        int nOriginalWeighted_; // the number of original events run over to get this sample accounting for genWeights
        int nEvents_;           // the number of events in the sample

        float xsec_;            // xsec in pb
        float lumi_;            // the luminosity of the data or effective luminosity of MC

        VarSet vars_;           // all of the variables from the ttree

    public:
        Sample();
        Sample(TString infilename, TString name);
        Sample(TString infilename, TString name, TString sampleType);
        ~Sample();

        int getEntry(int i);                    // load the ith event from the ttree into vars
        int getEntry(int i, TEntryList* list);  // load ith event from the list into vars
                                                // the ith event in the list maps to the jth tree entry
                                                
        void calculateNoriginal(); // calculate nOriginal and nOriginalWeighted
        void setBranchAddresses(); // link the values in the tree to vars
        float getWeight();         // get the weight for the histogram based upon the pileup weight and the MC gen weight
        float getScaleFactor(float luminosity); // get the scale factor for the MC histogram based upon the number of events, the data luminosity, and the xsec for the process 
        float getScaleFactor(float luminosity, float reductionFactor); // get the scale factor for the MC histogram based upon the number of events, the data luminosity, and the xsec for the process 
         
     protected:
        TFile* file;           // the file with the ttree
                      
};

#endif                                              //                                                     #endif
