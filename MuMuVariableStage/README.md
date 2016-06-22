# UFhmumuVariableStage
This code calculates additional variables using the stage1 ntuples created by Justin's UFDiMuonsAnalyzer.

Current path: Data -> UFDiMuonsAnalyzer -> UFhmumuVariableStage

Instructions
============

VariableAdder.C is an script for calculating new variables in our Ntuples.  To run it, and load the needed libraries, execute:

    root -b -q -x run.C
    
This will create new files, *_13TeV_stageVar.root, that contain trees with the new variables. To make files that contain histograms, run the VariableHistogramer by executing this command:

    root -b -q -x runHist.C
    
This will create new files, *_13TeV_Hist.root, that contain trees with the histograms. 

In order to display the histograms create a plot*.py script (for example see plotDiJetMass.py) and execute the script using python:

    python plot*.py
    
This will create a *.png file with the desired histogram.

If any of the root file locations need to updated, look at the input variables in run.C and runHist.C
    
