Boosted Z Studies
=================

This repository contains programs used to complete a simple search for Boosted Z's decaying to dimuons.

Installation Instructions
=========================

This program has been tested with CMSSW_7_4_2. To use this program, obtain this CMSSW release and move into the source directory.

    cmsrel CMSSW_7_4_2
    cd CMSSW_7_4_2
    cd src
    cmsenv
  
Then, clone this git repository and compile CMSSW

    git clone https://github.com/bregnery/BoostedZ.git
    scram b
    cmsenv

There are 3 directories in this repository: ExcitedQuark and UFDiMuonAnalyzer.
The UFDiMuonAnalyzer contains an altered version of the stage 1 ntuplizer used in the UF Hmumu studies. 
Please note that this was not used in our study, it is merely here for completeness sake.
The ExcitedQuark directory contains the programs used to generate local excited quark monte carlo samples.
The
