//Cuts.h

#ifndef ADD_CUTS
#define ADD_CUTS

#include "Sample.h"
#include <vector>

class Cuts
{
    public:
	Cuts();
	Cuts(Sample* insample);

	// Save the sample variable
	Sample* sample;

	// Boolean variables that state whether an event passes a selection criteria
	std::vector<bool> isBoostedZprelim;
	std::vector<bool> isRun1BoostedZ;

	// Selection criteria, each void function contains a different set of cuts
	void BoostedZprelim(int i);
	void Run1BoostedZ(int i);
};
#endif

