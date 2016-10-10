#include "Sample.h"
#include "../selection/Cuts.h"
#include "SampleHistos.h"
#include "Plots.h"

#include "TLorentzVector.h"

#include <sstream>
#include <map>
#include <vector>
#include <utility>

//////////////////////////////////////////////////
//------------------------------------------------
//////////////////////////////////////////////////

int main()
{
    // Should use this as the main database and choose from it to make the vector
    std::map<std::string, Sample*> samples;
       
    // Second container so that we can have a copy sorted by cross section.
    std::vector<Sample*> samplevec;

    ///////////////////////////////////////////////////////////////////
    // SAMPLES---------------------------------------------------------
    ///////////////////////////////////////////////////////////////////
    
    //float luminosity = 15900;  // pb -1 (for 2016 BCDE)
    float luminosity = 2169; // pb -1 (for 2015 CD all)
    //float lumiSF = 10;
    
    // use this to scale the MC for some projected amount of luminosity
    //luminosity *= lumiSF;
    
    //float signalSF = 100;
   
    // ================================================================
    // DYJetsToLL -----------------------------------------------------
    // ================================================================
  
    std::cout << "========== Accessing DY Monte Carlo =========" << std::endl;
 
    TString dyfilename  = TString("/home/bregnery/BoostedZ/CMSSW_8_0_9/src/mc/stage_1_dy_jetsToLL_1.root");
    //TString dyfilename   = TString("/cms/data/store/user/t2/users/acarnes/h2mumu/samples/stage1/mc/bg/dy/CMSSW_7_4_X/stage_1_dy_jetsToLL_ALL.root");
    samples["DYJetsToLL"] = new Sample(dyfilename, "DYJetsToLL", "background");
    //samples["DYJetsToLL"]->pileupfile = "./pu_reweight_trees/PUCalib_gw_DYJetsToLL.root"; //nPU
    samples["DYJetsToLL"]->xsec = 6025.2; // pb
    
    ///////////////////////////////////////////////////////////////////
    // Cuts------------------------------------------------------------
    ///////////////////////////////////////////////////////////////////

    // map containing the cuts
    std::map<std::string, Cuts*> cuts;   
    
    std::cout << "=========== Applying Selection Criteria to DY MC ======" << std::endl;
    cuts["DYJetsToLL"] = new Cuts(samples["DYJetsToLL"]);

    ///////////////////////////////////////////////////////////////////
    // Histograms------------------------------------------------------
    ///////////////////////////////////////////////////////////////////    

    // map containg the Histogram variables
    std::map<std::string, SampleHistos*> sampleHistos;

    // Run 1 Cuts
    std::cout << "=========== Creating DY MC Histogram file ==========" << std::endl;
    sampleHistos["DYJetsToLL"] = new SampleHistos(samples["DYJetsToLL"], cuts["DYJetsToLL"]->isRun1BoostedZ, "Run1Cuts", luminosity);

    ///////////////////////////////////////////////////////////////////
    // Plots-----------------------------------------------------------
    ///////////////////////////////////////////////////////////////////    

    // Make Plots
    std::cout << "=========== Creating Plots ===============" << std::endl;
    Plots* plots = new Plots(samples, sampleHistos);

    ///////////////////////////////////////////////////////////////////
    // Close files-----------------------------------------------------
    ///////////////////////////////////////////////////////////////////    

    std::cout << "=========== Closing Files ================" << std::endl;
    for(std::map<std::string, SampleHistos*>::const_iterator itr = sampleHistos.begin(); itr != sampleHistos.end(); itr++){
	(*itr).second->closeFile();
    }

    return 0;
}
