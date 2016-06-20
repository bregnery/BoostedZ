{
  gROOT->ProcessLine(".L VariableHistogramer.C++");
  
  ///////////////////////////////////////////////////////
  // This inputs the stage 1 ntuples on the UF hipergator 
  
  // Monte Carlo Signal
  //VariableHistogramer("ggHmumu_13TeV_stageVar.root","ggHmumu_13TeV_Hist.root",false,true);
  //VariableHistogramer("VBFHmumu_13TeV_stageVar.root","VBFHmumu_13TeV_Hist.root",false,true);
  //VariableHistogramer("VHmumu_13TeV_stageVar.root","VHmumu_13TeV_Hist.root",false,true);
  //VariableHistogramer("VHmumu_13_TeV_HS_stageVar.root","VHmumu_13TeV_HS_Hist.root",false,true);
  //VariableHistogramer("ttHmumu_13TeV_stageVar.root","ttHmumu_13TeV_Hist.root",false,true);

  // Monte Carlo Background
  VariableHistogramer("DY_13TeV_stageVar.root","DY_13TeV_Hist.root",false,false);
  //VariableHistogramer("TT_13TeV_stageVar.root","TT_13TeV_Hist.root",false,false,false);
   
  // Data from Golden JSON
  VariableHistogramer("Run25nsOct_13TeV_stageVar.root","Run25nsOct_13TeV_Hist.root",true,false);
  VariableHistogramer("RunCD_13TeV_stageVar.root","RunCD_13TeV_Hist.root",true,false);
  VariableHistogramer("RunDOct_v1_13TeV_stageVar.root","RunDOct_v1_13TeV_Hist.root",true,false);
  VariableHistogramer("RunDPrompt_v4_stageVar.root","RunDPrompt_v4_13TeV_Hist.root",true,false);
}

