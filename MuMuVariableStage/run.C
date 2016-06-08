{ 
  gROOT->ProcessLine(".L VariableAdder.C++");

  //////////////////////////////////////////////////////////
  // This inputs the most update ntuples from Andrew
  //////////////////////////////////////////////////////////

  //VariableAdder("/scratch/osg/bregnery/jhugon/stage1/CMSSW_7_4_2/src/UserArea/UFDiMuonsAnalyzer/test/stage_1_gg_HToMuMu_asympt25_ALL.root","ggHmumu_13TeV_stageVar.root",false,true,true);
  //VariableAdder("/scratch/osg/bregnery/jhugon/stage1/CMSSW_7_4_2/src/UserArea/UFDiMuonsAnalyzer/test/stage_1_vbf_HToMuMu_asympt25_ALL.root","VBFHmumu_13TeV_stageVar.root",false,true,true);

  /////////////////////////////////////////////////////////////////////////////
  // This inputs the stage 1 ntuples on the UF hipergator and UF Tier 2 cluster 
  /////////////////////////////////////////////////////////////////////////////

  // Signal Monte Carlo
  //VariableAdder("/scratch/osg/bregnery/jhugon/stage1/CMSSW_7_4_2/src/UserArea/UFDiMuonsAnalyzer/test/ggHmumu_13TeV_stage1.root","ggHmumu_13TeV_stageVar.root",false,true,false);

  // Drell Yan Monte Carlo
  VariableAdder("/cms/data/store/user/t2/users/acarnes/h2mumu/samples/stage1/monte_carlo/bg/dy/stage_1_dy_jetsToLL_ALL.root","DY_13TeV_stageVar.root",false,false,true);
  
  // TT Bar Monte Carlo
  //VariableAdder("/scratch/osg/bregnery/jhugon/stage1/CMSSW_7_4_2/src/UserArea/UFDiMuonsAnalyzer/test/TT_13TeV_Stage1.root","TT_13TeV_stageVar.root",false,false,false);

}
