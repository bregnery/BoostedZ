{
   gROOT->ProcessLine(".L VariableAdder.C++");
 
   /////////////////////////////////////////////////////////////////////////////
   // This inputs the stage 1 ntuples on the UF hipergator and UF Tier 2 cluster 
   /////////////////////////////////////////////////////////////////////////////
 
   // Signal Monte Carlo
   //VariableAdder("/scratch/osg/bregnery/jhugon/stage1/CMSSW_7_4_2/src/UserArea/UFDiMuonsAnalyzer/test/ggHmumu_13TeV_stage1.root","ggHmumu_13TeV_stageVar.root",false,true,false);
 
   // Drell Yan Monte Carlo
   //VariableAdder("/cms/data/store/user/t2/users/acarnes/h2mumu/samples/stage1/monte_carlo/bg/dy/stage_1_dy_jetsToLL_ALL.root","DY_13TeV_stageVar.root",false,false,true);
   
   // TT Bar Monte Carlo
   //VariableAdder("/scratch/osg/bregnery/jhugon/stage1/CMSSW_7_4_2/src/UserArea/UFDiMuonsAnalyzer/test/TT_13TeV_Stage1.root","TT_13TeV_stageVar.root",false,false,false);

   // Data from Golden JSON
   VariableAdder("/cms/data/store/user/t2/users/acarnes/h2mumu/samples/stage1/data_from_json/25ns/golden/3-25-16/stage_1_singleMuon_RunC25nsOct_MINIAOD_GOLDEN_ALL.root","Run25nsOct_13TeV_stageVar.root",true,false,true);
   VariableAdder("/cms/data/store/user/t2/users/acarnes/h2mumu/samples/stage1/data_from_json/25ns/golden/3-25-16/stage_1_singleMuon_RunCD_GOLDEN_ALL.root","RunCD_13TeV_stageVar.root",true,false,true);
   VariableAdder("/cms/data/store/user/t2/users/acarnes/h2mumu/samples/stage1/data_from_json/25ns/golden/3-25-16/stage_1_singleMuon_RunDOct_v1_MINIAOD_GOLDEN_ALL.root","RunDOct_v1_13TeV_stageVar.root",true,false,true);
   VariableAdder("/cms/data/store/user/t2/users/acarnes/h2mumu/samples/stage1/data_from_json/25ns/golden/3-25-16/stage_1_singleMuon_RunDPrompt_v4_MINIAOD_GOLDEN_ALL.root","RunDPrompt_v4_stageVar.root",true,false,true);
 
 }
