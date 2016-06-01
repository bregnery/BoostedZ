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

There are 5 directories in this repository: ExcitedQuark, interface, plugins, python, and test.
The programs that input data and monte carlo files into the stage 1 ntuplizer are located in the test directory.
The stage 1 ntuplizer is located in the plugins directory.
The ExcitedQuark directory contains the programs used to generate local excited quark monte carlo samples.
