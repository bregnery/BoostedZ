#include "Sample.h"

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
    float lumiSF = 10;
    
    // use this to scale the MC for some projected amount of luminosity
    luminosity *= lumiSF;
    
    //float signalSF = 100;
    
    // ================================================================
    // Data -----------------------------------------------------------
    // ================================================================
    
    std::cout << "============ Accessing Data ===============" << std::endl;           
    
    TString datafilename = TString("/cms/data/store/user/t2/users/acarnes/h2mumu/samples/stage1/data_from_json/25ns/golden/stage_1_singleMuon_RunCD_GOLDEN_ALL.root");
    //TString datafilename = TString("/cms/data/store/user/t2/users/acarnes/h2mumu/samples/stage1/data_from_json/25ns/golden/stage_1_singleMuon_RunDBoth_MINIAOD_GOLDEN_ALL.root");
    Sample* datasample = new Sample(datafilename, "Data", "data");
    datasample->lumi = luminosity;
    datasample->xsec = 9999;
    //datasample->pileupfile = "/cms/data/store/user/t2/users/acarnes/h2mumu/samples/stage1/data_from_json/25ns/golden/pileup/old/PUCalib_Golden_71mb.root";
    //datasample->pileupfile = "/cms/data/store/user/t2/users/acarnes/h2mumu/samples/stage1/data_from_json/25ns/golden/pileup/pileup_data_71mb.root";
    samples["Data"] = datasample;
    
    // ================================================================
    // DYJetsToLL -----------------------------------------------------
    // ================================================================
  
    std::cout << "========= Accessing DY Monte Carlo =========" << std::endl;
 
    TString dyfilename   = TString("/cms/data/store/user/t2/users/acarnes/h2mumu/samples/stage1/monte_carlo/bg/dy/stage_1_dy_jetsToLL_ALL.root");
    samples["DYJetsToLL"] = new Sample(dyfilename, "DYJetsToLL", "background");
    //samples["DYJetsToLL"]->pileupfile = "./pu_reweight_trees/PUCalib_gw_DYJetsToLL.root"; //nPU
    samples["DYJetsToLL"]->xsec = 6025.2; // pb
    
    // ================================================================
    // TTJets ---------------------------------------------------------
    // ================================================================
   
    std::cout << "=========== Accessing TT Monte Carlo ========" << std::endl;
 
    TString ttbarfilename   = TString("/cms/data/store/user/t2/users/acarnes/h2mumu/samples/stage1/monte_carlo/bg/ttbar/stage_1_ttJets_ALL.root");
    samples["TTJets"] = new Sample(ttbarfilename, "TTJets", "background");
    //samples["TTJets"]->pileupfile = "./pu_reweight_trees/PUCalib_gw_TTJets.root"; //nPU
    samples["TTJets"]->xsec = 831.76; // pb

    return 0;
}
