// Sample.h

#ifndef ADD_SAMPLE
#define ADD_SAMPLE

#include <vector>
#include "TMath.h"
#include "TH1F.h"
#include "TFile.h"
#include "TTree.h"
#include "TEntryList.h"

#include "LumiReweightingStandAlone.h"
#include "VarSet.h"

class Sample
{
    public:
        Sample();
        Sample(TString infilename, TString iname, TString insampleType);
        ~Sample();

        TString name;
        TString filename;
        TString treename;
        TTree* tree;
	//TTree* outTree;
        reweight::LumiReWeighting* lumiWeights;  // Information for pileup reweighting 

        TString dir;           // DAS directory
        TString pileupfile;    // used for pile up reweighting through lumiWeights
        TString sampleType;    // "data", "signal", "background"

        int plotColor;         // the color used when plotting the sample
        int nOriginal;         // the number of events run over to get this sample
        int nOriginalWeighted; // the number of original events run over to get this sample accounting for genWeights
        int nEvents;           // the number of events in the sample

        float xsec;            // xsec in pb
        float lumi;            // the luminosity of the data or effective luminosity of MC

        VarSet vars;           // all of the variables from the ttree
	std::vector<float> inverseDiMuPt;   // 1/ Dimuon Pt
	std::vector<float> deltaEta;        // the eta difference between the two muons

        int getEntry(int i);                    // load the ith event from the ttree into vars
        int getEntry(int i, TEntryList* list);  // load ith event from the list into vars
                                                // the ith event in the list maps to the jth tree entry

        void calculateNoriginal(); // calculate nOriginal and nOriginalWeighted
        void setAdditionalVariables(); // calculates values of new variables
	void setBranchAddresses(); // link the values in the tree to vars
        void orderMuons();         // Orders muons by Pt
	void addBranch(float newVar, TString newVarName, TBranch* newVarBranch); // Adds a branch with a leaf containing a floating point variable 
        float getWeight();         // get the weight for the histogram based upon the pileup weight and the MC gen weight
        float getScaleFactor(float luminosity); // get the scale factor for the MC histogram based upon the number of events, the data luminosity, and the xsec for the process 
	//void getOutFile();

    protected:
        TFile* file;           // the file with the ttree
	//TFile* outFile;        // the output file that will contain new variables

};

#endif
