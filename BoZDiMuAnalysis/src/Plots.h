// Plots.h

#ifndef ADD_PLOTS
#define ADD_PLOTS

#include <vector>
#include <iostream>
#include <map>

#include "Sample.h"
#include "SampleHistos.h"
#include "../selection/Cuts.h"

#include "TH1F.h"
#include "TH2F.h"
#include "THStack.h"
#include "TString.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TFrame.h"
#include "TGraphErrors.h"
#include "TStyle.h"
#include "TROOT.h"

class Plots
{
   public:
	Plots();
	Plots(std::map<std::string, Sample*> insample, std::map<std::string, SampleHistos*> inhistos);

	std::map<std::string, Sample*> sample;
	std::map<std::string, SampleHistos*> histos;
	std::vector<TCanvas*> canvas;

};

#endif
