
/////////////////////////////////////////////////////////////////////
//                         Plots.cxx                               //
//=================================================================//
//                                                                 //
// Contains functions for producing the analysis's Plots           //
/////////////////////////////////////////////////////////////////////

#include "Plots.h"

///////////////////////////////////////////////////////////////////////
//_________________________Sample Histograms_________________________//
///////////////////////////////////////////////////////////////////////

Plots::Plots(){}

///////////////////////////////////////////////////////////////////////
//-------------------------------------------------------------------//
///////////////////////////////////////////////////////////////////////

Plots::Plots(std::map<std::string, Sample*> insample, std::map<std::string, SampleHistos*> inhistos)
{
   /////////////////////////////////////////////////////////////////////
   // Save Class Variables----------------------------------------------
   /////////////////////////////////////////////////////////////////////

   sample = insample;
   histos = inhistos;

   /////////////////////////////////////////////////////////////////////
   // Create necessary canvas variables and set root parameters---------
   /////////////////////////////////////////////////////////////////////

   std::vector<THStack*> stackVec;

   int index = 0;
   double width = 1000;
   double height = 1000;

   gStyle->SetPadLeftMargin(0.15);
   //gROOT->SetBatch();

   ////////////////////////////////////////////////////////////////////
   // Create Canvas----------------------------------------------------
   ////////////////////////////////////////////////////////////////////

	
    for(std::vector<TH1F*>::const_iterator j = histos["DYJetsToLL"]->histo1D.begin(); j != histos["DYJetsToLL"]->histo1D.end(); j++){
	// Create the THStack
	TString histoVarName((*j)->GetName());
	THStack* stackTemp = new THStack(histoVarName, (*j)->GetTitle());
	//stackTemp->GetXaxis()->SetTitle((*j)->GetLa );
	//stackTemp->GetYaxis()->SetTitle((*j)->GetYaxis()->GetTitle() );
	stackVec.push_back(stackTemp);
    }

   /////////////////////////////////////////////////////////////////////
   // Histogram Settings------------------------------------------------
   /////////////////////////////////////////////////////////////////////

   for(typename std::map<std::string, SampleHistos*>::const_iterator itr = histos.begin(); itr != histos.end(); itr++){
	
	index = 0;

      	for(std::vector<TH1F*>::const_iterator j = (*itr).second->histo1D.begin(); j != (*itr).second->histo1D.end(); j++){

	    TString histoVarName((*j)->GetName());

	    // Set Histogram filling parameters
	    (*j)->SetMarkerStyle(0);
	    (*j)->SetFillStyle(1);
	    (*j)->GetYaxis()->SetTitleOffset(2.0);

	    if((*itr).first == "DYJetsToLL"){
		(*j)->SetFillColor(kOrange);
		(*j)->SetLineColor(kOrange+7);
	    }
	    else if((*itr).first == "TTJets"){
		(*j)->SetFillColor(kGreen-1);
		(*j)->SetLineColor(kGreen+1);
	    }
	    else if((*itr).first == "QstarZm1000"){
		(*j)->SetFillColor(kMagenta-1);
		(*j)->SetLineColor(kMagenta+1);
		(*j)->SetFillStyle(3005);
	    }
	    else if((*itr).first == "QstarZm2000"){
		(*j)->SetFillColor(kBlue-1);
		(*j)->SetLineColor(kBlue+1);
		(*j)->SetFillStyle(3005);
	    }
	    else if((*itr).first == "QstarZm5000"){
		(*j)->SetFillColor(kTeal-1);
		(*j)->SetLineColor(kTeal+1);
		(*j)->SetFillStyle(3005);
	    }
	    else if((*itr).first == "Data"){
		(*j)->SetFillColor(1);
		(*j)->SetLineColor(1);
		(*j)->SetMarkerStyle(8);
		(*j)->SetLineStyle(1);
	    }

	    // THStack the Monte Carlo
	    if((*itr).first == "DYJetsToLL" || (*itr).first == "TTJets"){
		
		// Debugging
		std::cout << "Adding " << (*itr).first << " to " <<  histoVarName << std::endl;

		stackVec[index]->Add( (*j) );
	    }

	    index++;
     	}
	
   }

   /////////////////////////////////////////////////////////////////////
   // Draw Plots--------------------------------------------------------
   /////////////////////////////////////////////////////////////////////

   index = 0;
	
   for(std::vector<THStack*>::const_iterator itr = stackVec.begin(); itr != stackVec.end(); itr++){
	TString histoVarName((*itr)->GetName());

	// Create Canvas
  	TCanvas* canvasTemp = new TCanvas("c" + histoVarName, "c" + histoVarName, width, height);

	// Log Y
	//canvasTemp->SetLogy(true);	

	// Draw Histograms
	(*itr)->Draw("hist");
	histos["Data"]->histo1D[index]->Draw("same");
	canvasTemp->SaveAs("Hist_" + histoVarName + ".png");

	// Save Canvas Vector
	canvas.push_back(canvasTemp);

	// Debugging	
	std::cout << "Saved canvas" << std::endl;

	index++;
   }


/*
   gStyle->SetPadRightMargin(0.17);

// Plot 2D histograms
   for(std::vector<TH2F*>::const_iterator j = histos->histo2D.begin(); j != histos->histo2D.end(); j++){

	    TString histoVarName((*j)->GetName());

	    // Create Canvas
  	    TCanvas* canvasTemp = new TCanvas("c" + histoVarName, "c" + histoVarName, width, height);
	    
	    // Set Histogram filling parameters
	    (*j)->SetFillColor(kOrange);
	    (*j)->SetLineColor(kOrange+7);
	    (*j)->SetMarkerStyle(0);
	    (*j)->SetFillStyle(1);
	    (*j)->GetYaxis()->SetTitleOffset(2.0);
	    (*j)->SetStats(0);
	    (*j)->Draw("colz text");
	
	    canvasTemp->SaveAs("Hist_" + histoVarName + ".png");
	
	    // Save Canvas Vector
	    canvas.push_back(canvasTemp);

	    index++;
   }
*/

}

////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////

