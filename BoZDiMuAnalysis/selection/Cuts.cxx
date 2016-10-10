//////////////////////////////////////////////////////////////
//                         Cuts.cxx                         //
//==========================================================//
//                                                          //
// Contains functions for the analysis's various versions   //
// Selection Criteria                                       //
//////////////////////////////////////////////////////////////

#include "Cuts.h"

//////////////////////////////////////////////////////////////
//______________________Cuts________________________________//
//////////////////////////////////////////////////////////////

Cuts::Cuts(){}

//////////////////////////////////////////////////////////////
//----------------------------------------------------------//
//////////////////////////////////////////////////////////////

Cuts::Cuts(Sample* insample)
{
// For loop that runs over all the events to create boolean flags

   unsigned reportEach = 1000000;

   sample = insample;

   isBoostedZprelim.resize(sample->nEvents);
   isRun1BoostedZ.resize(sample->nEvents);

   for(unsigned i=0; i<sample->nEvents; i++)
   {
	if(i % reportEach == 0) std::cout << "Event: " << i << std::endl;
	BoostedZprelim(i);
	Run1BoostedZ(i);
   }
}

///////////////////////////////////////////////////////////////
//-----------------------------------------------------------//
//////////////////////////////////////////////////////////////

void Cuts::BoostedZprelim(int i)
{
// Preliminary cuts (such as DiMu Mass, Eta, etc)

   sample->getEntry(i);

   //sample->setAdditionalVariables(i);

   isBoostedZprelim[i] = false;   

   // Cut on Dimuon Mass
   if(sample->vars.recoCandMass >= 60 && sample->vars.recoCandMass <= 120){
	isBoostedZprelim[i] = true;
	//std::cout << "Mass: " << sample->vars.recoCandMass << std::endl;
	//std::cout << "inverseDiMuPt: " << sample->inverseDiMuPt[i] << std::endl;
   }
}

/////////////////////////////////////////////////////////////
//---------------------------------------------------------//
/////////////////////////////////////////////////////////////

void Cuts::Run1BoostedZ(int i)
{
// Cuts used in the first run of the LHC

   sample->getEntry(i);

   isRun1BoostedZ[i] = false;

   // Cut on Dimuon Mass
   if(sample->vars.recoCandMass >= 60 && sample->vars.recoCandMass <= 120){
	//debugging
	std::cout << "Event: " << i << " has correct mass" << std::endl;
   // Cut on Dimuon Pt
   if(sample->vars.recoCandPt >= 50){
	//debugging
	std::cout << "  has correct dimuon pt" << std::endl;
   // Cut on individual muon pt
   if(sample->vars.reco1.pt >= 45 || sample->vars.reco2.pt >= 45){
	//debugging
	std::cout << "  has correct muon pt" << std::endl;
   // Opposite sign charges
   if(sample->vars.reco1.charge != sample->vars.reco2.charge){
	//debugging
	std::cout << "  has correct charge" << std::endl;
   // Cut on the muon eta difference
   if(sample->deltaEta[i] <= 1.0){
	//debugging
	std::cout << "  has correct eta" << std::endl;
   if(sample->vars.reco1.isTightMuon == 1 && sample->vars.reco2.isTightMuon == 1){
   // Cut on the primary vetex
   for(unsigned j=0; j<20; j++){
       if(sample->vars.vertices.isValid[j] == true){
          if(sample->vars.vertices.normChi2[j] < 10){
	     //debugging
	     std::cout << "   has the correct chi square" << std::endl;
             isRun1BoostedZ[i] = true;
          }
          break;
       }
   }}}}}}}
}


