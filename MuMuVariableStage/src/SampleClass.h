// Sample.h

#ifndef ADD_SAMPLE
#define ADD_SAMPLE

#include "TMath.h"
#include "TH1F.h"
#include "TFile.h"
#include "TTree.h"
#include "TEntryList.h"

class Sample{
	public:
		double xsec;            // cross section in pb
		int nOriginal;          // the number of events run over to get this sample
		int nOriginalWeighted;  // the number of original events run over to get this sample accounting for genWeights
		TString filename;       
		TString name;
		TString treename;
		TTree* tree;
	
		Sample();
		Sample(TString infilename, TString inname, TTree *intree, TTree *metadata);
		~Sample();

		void calculateNoriginal(TTree *metadata);   // calculate nOriginal and nOriginalWeighted
		float getScaleFactor(float luminosity);     // get the scale factor for the MC histogram based upon the number of events, the data luminosity, and the xsec for the process

};


#endif
