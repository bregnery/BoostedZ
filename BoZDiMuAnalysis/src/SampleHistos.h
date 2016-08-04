// SampleHistos.h

#ifndef PLOTS
#define PLOTS

#include <vector>
#include <iostream>

#include "Sample.h"
#include "../selection/Cuts.h"

#include "TH1F.h"
#include "TString.h"

class SampleHistos
{
   public:
	SampleHistos();
	SampleHistos(Sample* sample, std::vector<bool> isCut, TString cutName, float luminosity);

	std::vector<TH1F*> histo1D;

	void setHistTitles(TH1F* hist, TString xtitle, TString ytitle);
	void closeFile();

   protected:
	TFile* file;  // output file with histograms

};

#endif
