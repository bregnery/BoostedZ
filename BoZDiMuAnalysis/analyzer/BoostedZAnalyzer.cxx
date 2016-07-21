#include "Sample.h"
#include "../selection/Cuts.h"
#include "SampleHistos.h"

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
   
    float luminosity = 2169;
    //float lumiSF = 10;
    
    // use this to scale the MC for some projected amount of luminosity
    //luminosity *= lumiSF;
    
    //float signalSF = 100;
    
    // ================================================================
    // Data -----------------------------------------------------------
    // ================================================================
    
    std::cout << "============ Accessing Data ===============" << std::endl;           
    
    TString datafilename = TString("/cms/data/store/user/t2/users/acarnes/h2mumu/samples/stage1/data/25ns/golden/CMSSW_7_4_X/stage_1_singleMuon_RunCD_GOLDEN_ALL.root");
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
 
    TString dyfilename   = TString("/cms/data/store/user/t2/users/acarnes/h2mumu/samples/stage1/mc/bg/dy/CMSSW_7_4_X/stage_1_dy_jetsToLL_ALL.root");
    samples["DYJetsToLL"] = new Sample(dyfilename, "DYJetsToLL", "background");
    //samples["DYJetsToLL"]->pileupfile = "./pu_reweight_trees/PUCalib_gw_DYJetsToLL.root"; //nPU
    samples["DYJetsToLL"]->xsec = 6025.2; // pb
    
    // ================================================================
    // TTJets ---------------------------------------------------------
    // ================================================================
   
    std::cout << "========== Accessing TT Monte Carlo =========" << std::endl;
 
    TString ttbarfilename   = TString("/cms/data/store/user/t2/users/acarnes/h2mumu/samples/stage1/mc/bg/ttbar/CMSSW_7_4_X/stage_1_ttJets_ALL.root");
    samples["TTJets"] = new Sample(ttbarfilename, "TTJets", "background");
    //samples["TTJets"]->pileupfile = "./pu_reweight_trees/PUCalib_gw_TTJets.root"; //nPU
    samples["TTJets"]->xsec = 831.76; // pb

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
    std::cout << "=========== Creating DY MC Histogram file ==========" << std::endl;
    sampleHistos["DYJetsToLL"] = new SampleHistos(samples["DYJetsToLL"], cuts["DYJetsToLL"]->isBoostedZprelim, "BasicCuts", luminosity);
    std::cout << "=========== Creating TT MC Histogram file ==========" << std::endl;
    sampleHistos["TTJets"] = new SampleHistos(samples["TTJets"], cuts["TTJets"]->isBoostedZprelim, "BasicCuts", luminosity);
*/

    // Run 1 Cuts
    std::cout << "=========== Creating Data Histogram file ===========" << std::endl;
    sampleHistos["Data"] = new SampleHistos(samples["Data"], cuts["Data"]->isRun1BoostedZ, "Run1Cuts", luminosity);
    std::cout << "=========== Creating DY MC Histogram file ==========" << std::endl;
    sampleHistos["DYJetsToLL"] = new SampleHistos(samples["DYJetsToLL"], cuts["DYJetsToLL"]->isRun1BoostedZ, "Run1Cuts", luminosity);
    std::cout << "=========== Creating TT MC Histogram file ==========" << std::endl;
    sampleHistos["TTJets"] = new SampleHistos(samples["TTJets"], cuts["TTJets"]->isRun1BoostedZ, "Run1Cuts", luminosity);
    return 0;
}
