Using the Stage 1 Ntuplizer
===========================

The ntuplizer can run over locally generated monte carlo files, JSON files, and DAS files.
The selection criteria can be altered in the plugins directory.

JSON and DAS files
==================

The input DAS and JSON files can be found in the Samples_v3.py file. The make_crab_script.py takes Samples_v3.py as an input.

Locally Generated Monte Carlo
=============================

UFDiMuonAnalyzer_Brendan_Example.py is a template for submitting local monte carlo files. In order to run the stage 1 ntuplizer on these files, simply follow this command:

	cmsRun UFDiMuonAnalyzer_<versionName>.py

Or, if running on the UF HPC, you can make a generator.submit file, which can be run with this command:

	qsub generator.submit


