// Histograms.h

#ifndef ADD_HISTOGRAMS
#define ADD_HISTOGRAMS

#include "TMath.h"
#include "TH1F.h"
#include "TFile.h"
#include "TTree.h"
#include "TEntryList.h"

#include "LumiReweightingStandAlone.h"
#include "VarSet.h"

class Histograms
{
    public:
        Histograms();
	Histograms(Sample insample, float luminosity);
	~Sample();

	Sample sample;   // Sample that used to create histograms
	float wieght;    // Scalefactor for the histograms

	void newHistogram(TH1F* newHisto, TString varName, float variable, int bins, float xlow, float xhigh, TString xname, TString yname, int stats);
	void saveOutput();
};
