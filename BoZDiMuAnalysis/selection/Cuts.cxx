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

Cuts::Cuts(Sample insample)
{
// For loop that runs over all the events to create boolean flags

   sample = insample;
   for(unsigned i=0; i<sample.nEvents; i++)
   {
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

   sample.getEntry(i);

   isBoostedZprelim = false;   

   // Cut on Dimuon Mass
   if(sample.vars.recoCandMass >= 60 && sample.vars.recoCandMass <= 120){
	continue;
   }

   isBoostedZprelim = true;
}

/////////////////////////////////////////////////////////////
//---------------------------------------------------------//
/////////////////////////////////////////////////////////////

void Cuts::Run1BoostedZ(int i)
{
// Cuts used in the first run of the LHC

    sample.getEntry(i);

    isRun1BoostedZ = false;

    isRun1BoostedZ = true;
}


