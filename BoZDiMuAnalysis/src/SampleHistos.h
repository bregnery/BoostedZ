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
	SampleHistos(Sample* sample, vector<bool> isCut, TString cutName, float luminosity);

   protected:
	TFile* file;  // output file with histograms

};

#endif
