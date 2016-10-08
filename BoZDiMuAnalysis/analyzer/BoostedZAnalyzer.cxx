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
    
    float luminosity = 15900;  // pb -1 (for 2016 BCDE)
    // float luminosity = 2169; // pb -1 (for 2015 CD all)
    //float lumiSF = 10;
    
    // use this to scale the MC for some projected amount of luminosity
    //luminosity *= lumiSF;
    
    //float signalSF = 100;
   
    // ================================================================
    // Data -----------------------------------------------------------
    // ================================================================
    
    std::cout << "============ Accessing Data ===============" << std::endl;           
    
    TString datafilename = TString("/home/bregnery/BoostedZ/CMSSW_8_0_9/src/data/stage_1_singleMuon_Run2016BCDE.root");
    //TString datafilename = TString("/cms/data/store/user/t2/users/acarnes/h2mumu/samples/stage1/data/25ns/golden/CMSSW_7_4_X/stage_1_singleMuon_RunCD_GOLDEN_ALL.root");
    //TString datafilename = TString("/cms/data/store/user/t2/users/acarnes/h2mumu/samples/stage1/data_from_json/25ns/golden/stage_1_singleMuon_RunDBoth_MINIAOD_GOLDEN_ALL.root");
    samples["Data"] = new Sample(datafilename, "Data", "data");
    samples["Data"]->lumi = luminosity;
    samples["Data"]->xsec = 9999;
    //datasample->pileupfile = "/cms/data/store/user/t2/users/acarnes/h2mumu/samples/stage1/data_from_json/25ns/golden/pileup/old/PUCalib_Golden_71mb.root";
    //datasample->pileupfile = "/cms/data/store/user/t2/users/acarnes/h2mumu/samples/stage1/data_from_json/25ns/golden/pileup/pileup_data_71mb.root";
    //samples["Data"] = datasample;
   
    // ================================================================
    // DYJetsToLL -----------------------------------------------------
    // ================================================================
  
    std::cout << "========== Accessing DY Monte Carlo =========" << std::endl;
 
    TString dyfilename  = TString("/home/bregnery/BoostedZ/CMSSW_8_0_9/src/mc/stage_1_dy_jetsToLL_1.root");
    //TString dyfilename   = TString("/cms/data/store/user/t2/users/acarnes/h2mumu/samples/stage1/mc/bg/dy/CMSSW_7_4_X/stage_1_dy_jetsToLL_ALL.root");
    samples["DYJetsToLL"] = new Sample(dyfilename, "DYJetsToLL", "background");
    //samples["DYJetsToLL"]->pileupfile = "./pu_reweight_trees/PUCalib_gw_DYJetsToLL.root"; //nPU
    samples["DYJetsToLL"]->xsec = 6025.2; // pb
    
    // ================================================================
    // TTJets ---------------------------------------------------------
    // ================================================================
   
    std::cout << "========== Accessing TT Monte Carlo =========" << std::endl;
 
    TString ttbarfilename   = TString("/home/bregnery/BoostedZ/CMSSW_8_0_9/src/mc/stage_1_ttJets.root");
    samples["TTJets"] = new Sample(ttbarfilename, "TTJets", "background");
    //samples["TTJets"]->pileupfile = "./pu_reweight_trees/PUCalib_gw_TTJets.root"; //nPU
    samples["TTJets"]->xsec = 831.76; // pb

    // ================================================================
    // QStar M-1000 ---------------------------------------------------
    // ================================================================
   
    std::cout << "========== Accessing QStar M-1000 Monte Carlo =========" << std::endl;
 
    TString Qstar1000filename   = TString("/home/bregnery/BoostedZ/CMSSW_8_0_9/src/mc/stage_1_QstarToQZm1000_1.root");
    samples["QstarZm1000"] = new Sample(Qstar1000filename, "QstarZm1000", "signal");
    //samples["TTJets"]->pileupfile = "./pu_reweight_trees/PUCalib_gw_TTJets.root"; //nPU
    samples["QstarZm1000"]->xsec = 6025; // pb

    // ================================================================
    // QStar M-2000 ---------------------------------------------------
    // ================================================================
   
    std::cout << "========== Accessing QStar M-2000 Monte Carlo =========" << std::endl;
 
    TString Qstar2000filename   = TString("/home/bregnery/BoostedZ/CMSSW_8_0_9/src/mc/stage_1_QstarToQZm2000_1.root");
    samples["QstarZm2000"] = new Sample(Qstar2000filename, "QstarZm2000", "signal");
    //samples["TTJets"]->pileupfile = "./pu_reweight_trees/PUCalib_gw_TTJets.root"; //nPU
    samples["QstarZm2000"]->xsec = 6025; // pb

    // ================================================================
    // QStar M-5000 ---------------------------------------------------
    // ================================================================
   
    std::cout << "========== Accessing QStar M-5000 Monte Carlo =========" << std::endl;
 
    TString Qstar5000filename   = TString("/home/bregnery/BoostedZ/CMSSW_8_0_9/src/mc/stage_1_QstarToQZm5000_1.root");
    samples["QstarZm5000"] = new Sample(Qstar5000filename, "QstarZm5000", "signal");
    //samples["TTJets"]->pileupfile = "./pu_reweight_trees/PUCalib_gw_TTJets.root"; //nPU
    samples["QstarZm5000"]->xsec = 6025; // pb

    ///////////////////////////////////////////////////////////////////
    // Cuts------------------------------------------------------------
    ///////////////////////////////////////////////////////////////////

    // map containing the cuts
    std::map<std::string, Cuts*> cuts;   
    
    std::cout << "=========== Applying Selection Criteria to Data ======" << std::endl;
    cuts["Data"] = new Cuts(samples["Data"]);
    std::cout << "=========== Applying Selection Criteria to DY MC ======" << std::endl;
    cuts["DYJetsToLL"] = new Cuts(samples["DYJetsToLL"]);
    std::cout << "=========== Applying Selection Criteria to TT MC ======" << std::endl;
    cuts["TTJets"] = new Cuts(samples["TTJets"]);

    ///////////////////////////////////////////////////////////////////
    // Histograms------------------------------------------------------
    ///////////////////////////////////////////////////////////////////    

    // map containg the Histogram variables
    std::map<std::string, SampleHistos*> sampleHistos;

/*
    // Basic Cuts
    std::cout << "=========== Creating Data Histogram file ===========" << std::endl;
    sampleHistos["Data"] = new SampleHistos(samples["Data"], cuts["Data"]->isBoostedZprelim, "BasicCuts", luminosity);
    std::cout << "=========== Creating TT MC Histogram file ==========" << std::endl;
    sampleHistos["TTJets"] = new SampleHistos(samples["TTJets"], cuts["TTJets"]->isBoostedZprelim, "BasicCuts", luminosity);
    std::cout << "=========== Creating DY MC Histogram file ==========" << std::endl;
    sampleHistos["DYJetsToLL"] = new SampleHistos(samples["DYJetsToLL"], cuts["DYJetsToLL"]->isBoostedZprelim, "BasicCuts", luminosity);
*/

    // Run 1 Cuts
    std::cout << "=========== Creating Data Histogram file ===========" << std::endl;
    sampleHistos["Data"] = new SampleHistos(samples["Data"], cuts["Data"]->isRun1BoostedZ, "Run1Cuts", luminosity);
    std::cout << "=========== Creating DY MC Histogram file ==========" << std::endl;
    sampleHistos["DYJetsToLL"] = new SampleHistos(samples["DYJetsToLL"], cuts["DYJetsToLL"]->isRun1BoostedZ, "Run1Cuts", luminosity);
    std::cout << "=========== Creating TT MC Histogram file ==========" << std::endl;
    sampleHistos["TTJets"] = new SampleHistos(samples["TTJets"], cuts["TTJets"]->isRun1BoostedZ, "Run1Cuts", luminosity);


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
