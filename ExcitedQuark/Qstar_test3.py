# Auto generated configuration file
# using:
# Revision: 1.172
# Source: /cvs_server/repositories/CMSSW/CMSSW/Configuration/PyReleaseValidation/python/ConfigBuilder.py,v
# with command line options: ZMM.cfi -s GEN,SIM,DIGI,L1,DIGI2RAW,HLT,RAW2DIGI -n 10 --no_exec --conditions START36_V10::All
import FWCore.ParameterSet.Config as cms

process = cms.Process('GEN')

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.StandardSequences.MixingNoPileUp_cff')
process.load('Configuration.StandardSequences.GeometryExtended_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('Configuration.StandardSequences.Generator_cff')
process.load('Configuration.StandardSequences.VtxSmearedEarly10TeVCollision_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
process.load('Configuration.EventContent.EventContent_cff')

#process.RandomNumberGeneratorService.generator.initialSeed = cms.untracked.uint32(110_RSEED_)
process.RandomNumberGeneratorService.generator.initialSeed = cms.untracked.uint32(110)

process.configurationMetadata = cms.untracked.PSet(
    version = cms.untracked.string('$Revision: 1.172 $'),
    annotation = cms.untracked.string('Qstar.cfi nevts:10'),
    name = cms.untracked.string('PyReleaseValidation')
)
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(5)
)
process.options = cms.untracked.PSet(

)
# Input source
process.source = cms.Source("EmptySource")

# Output definition
process.output = cms.OutputModule("PoolOutputModule",
    splitLevel = cms.untracked.int32(0),
    fileName = cms.untracked.string('file:./test3.root'),
    dataset = cms.untracked.PSet(
        dataTier = cms.untracked.string(''),
        filterName = cms.untracked.string('')
    ),
    SelectEvents = cms.untracked.PSet(
        SelectEvents = cms.vstring('generation_step')
    )
)

# Additional output definition

from Configuration.Generator.PythiaUESettings_cfi import *

# Other statements
process.GlobalTag.globaltag = 'START38_V12::All'
process.generator = cms.EDFilter("Pythia6GeneratorFilter",
    pythiaPylistVerbosity = cms.untracked.int32(1),
    filterEfficiency = cms.untracked.double(1.0),
    pythiaHepMCVerbosity = cms.untracked.bool(False),
    comEnergy = cms.double(7000.0),
    maxEventsToPrint = cms.untracked.int32(-1),
    PythiaParameters = cms.PSet(
        pythiaUESettingsBlock,
        processParameters = cms.vstring(
            'MSEL        = 0 ',
            'MSUB(147)   = 1     !d* ',
            'MSUB(148)   = 1     !u* ',
            'MSUB(167)   = 0     !u* ci ',
            'MSUB(168)   = 0     !d* ci ',
            'PMAS(343,1) = 500  !mass of d*',
            'PMAS(344,1) = 500  !mass of u*',
            'RTCM(41)    = 500  !Lambda = mass ',
            'RTCM(43)    = 1     !f ',
            'RTCM(44)    = 1     !fp ',
            'RTCM(45)    = 1     !fs ',
            'MDME(174,1) = 0    !Z decay into d dbar',
            'MDME(175,1) = 0    !Z decay into u ubar',
            'MDME(176,1) = 0    !Z decay into s sbar',
            'MDME(177,1) = 0    !Z decay into c cbar',
            'MDME(178,1) = 0    !Z decay into b bbar',
            'MDME(179,1) = 0    !Z decay into t tbar',
            'MDME(182,1) = 0    !Z decay into e- e+',
            'MDME(183,1) = 0    !Z decay into nu_e nu_ebar',
            'MDME(184,1) = 1    !Z decay into mu- mu+',
            'MDME(185,1) = 0    !Z decay into nu_mu nu_mubar',
            'MDME(186,1) = 0    !Z decay into tau- tau+',
            'MDME(187,1) = 0    !Z decay into nu_tau nu_taubar',
            '4000001:ALLOFF            !Turn off all u* decays', 
            '4000001:ONIFMATCH 1 23    !Turn on u*->u Z', 
            '4000002:ALLOFF            !Turn off all d* decays', 
            '4000002:ONIFMATCH 2 23    !Turn on d*->d g'
        ),
        pdfParameters = cms.vstring(
            'MSTP(52)=2     ! work with LHAPDF',
            'MSTP(51)=10041 ! structure function chosen (external PDF CTEQ6L1)' # (  p.193/201 + table in http://projects.hepforge.org/lhapdf/manual)
#            'MSTP(51)=20060 ! structure function chosen (external PDF MRST2001lo)'
#            'MSTP(51)=21000! structure function chosen (external PDF MSTW2008)'
        ),
        isrParameters = cms.vstring(
            #'PARP(67)    = 2.5 ', # amount of initial-state radiation (varied by +-0.5 and +-1.5, p.324/332)
        	'PARP(67)    = 3 ', # amount of initial-state radiation (varied by +-0.5 and +-1.5, p.324/332)
		),
        fsrParameters = cms.vstring(
            'MSTP(71)    = 1 ', # master switch for final-state QCD and QED radiation (0/1 = off/on, p.323/331)
            'PARP(71)    = 4.0 '  # amount of final-state radiation (varied -1.5 - +4.0, p.324/332)
        ),
        mpiParameters = cms.vstring(
            'MSTP(81)    = 1 ' # master switch for multiple interactions (-1/1/... = off/on/... , p.347/355)
        ),
        parameterSets = cms.vstring(
            #'pythiaUESettings',
            #'pdfParameters',
            'isrParameters',
            'fsrParameters',
            'processParameters')
    )
# Look for more in: 
#  https://twiki.cern.ch/twiki/bin/viewauth/CMS/SWGuideEWKUtilities#PDF_SYSTEMATICS_PDFWeightProduce
#  https://twiki.cern.ch/twiki/bin/viewauth/CMS/SWGuideEWKUtilities#INITIAL_STATE_RADIATION_ISR_SYST
)
process.mumugenfilter = cms.EDFilter("MCParticlePairFilter",
    Status = cms.untracked.vint32(1, 1),
    MinPt = cms.untracked.vdouble(2.5, 2.5),
    MaxEta = cms.untracked.vdouble(2.5, 2.5),
    MinEta = cms.untracked.vdouble(-2.5, -2.5),
    ParticleCharge = cms.untracked.int32(-1),
    ParticleID1 = cms.untracked.vint32(13),
    ParticleID2 = cms.untracked.vint32(13)
)

process.ProductionFilterSequence = cms.Sequence(process.generator)

# Path and EndPath definitions
process.generation_step = cms.Path(process.pgen)
process.endjob_step = cms.Path(process.endOfProcess)
process.out_step = cms.EndPath(process.output)

# Schedule definition
process.schedule = cms.Schedule(process.generation_step,process.endjob_step,process.out_step)

# special treatment in case of production filter sequence
for path in process.paths:
    getattr(process,path)._seq = process.ProductionFilterSequence*getattr(process,path)._seq
