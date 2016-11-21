
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
		(*j)->SetFillStyle(3325);
	    }
	    else if((*itr).first == "QstarZm2000"){
		(*j)->SetFillColor(kBlue-1);
		(*j)->SetLineColor(kBlue+1);
		(*j)->SetFillStyle(3325);
	    }
	    else if((*itr).first == "QstarZm5000"){
		(*j)->SetFillColor(kTeal+1);
		(*j)->SetLineColor(kTeal-5);
		(*j)->SetFillStyle(3325);
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

	// Draw Histograms Update Axis titles
	(*itr)->Draw("hist"); //Must draw before x and y axis can be modified
	TString xtitle(histos["DYJetsToLL"]->histo1D[index]->GetXaxis()->GetTitle() );
	TString ytitle(histos["DYJetsToLL"]->histo1D[index]->GetYaxis()->GetTitle() );
		//Debugging
		std::cout << xtitle << "    " << ytitle << std::endl;
	(*itr)->GetXaxis()->SetTitle(xtitle);
	(*itr)->GetYaxis()->SetTitle(ytitle);
	(*itr)->GetYaxis()->SetTitleOffset(2.0);
	canvasTemp->Modified();
	//histos["QstarZm1000"]->histo1D[index]->Draw("hist same");
	//histos["QstarZm2000"]->histo1D[index]->Draw("hist same");
	//histos["QstarZm5000"]->histo1D[index]->Draw("hist same");
	
	// Fit the 1/pt data
	if(histoVarName == "inverseDiMuPtHist"){
	    TF1 *dyfunc = new TF1("dyfunc",dyfunction,0,0.008,4);
	                      // change second to last number when changing the y bounds on the graph
	    dyfunc->SetParameters(1,1,1,1);
	    std::cout << "Made the fit function" << std::endl;
 
	    // Fit the data
	    histos["DYJetsToLL"]->histo1D[index]->Fit("dyfunc");
	    std::cout << "Fit the data" << std::endl;

	    // Inclusive plot
            histos["DYJetsToLL"]->histo1D[index]->Draw("same");
	    canvasTemp->SaveAs("Hist_" + histoVarName + ".png");

	    // Create canvas with pad for residuals
   	    //gStyle->SetPadBottomMargin(2.0);
	    TCanvas* canvasFit = new TCanvas("cFit" + histoVarName, "c" + histoVarName, width, height);
	    TPad *histopad = new TPad("histopad", "histopad",0.0,0.33,1.0,1.0); //xlow,ylow,xup,yup
	    TPad *residualpad = new TPad("residualpad","residualpad",0.0,0.0,1.0,0.33);
	    histopad->SetBottomMargin(0.00001);
	    histopad->SetBorderMode(0);
	    residualpad->SetTopMargin(0.00001);
	    residualpad->SetBottomMargin(0.3);
	    residualpad->SetBorderMode(0);
	    histopad->Draw();
	    residualpad->Draw();
	    std::cout << "Made TPad" << std::endl;

	    // plot the fit, data, and signal
	    histopad->cd();
	    histos["DYJetsToLL"]->histo1D[index]->SetStats(0);
	    histos["DYJetsToLL"]->histo1D[index]->GetYaxis()->SetTitleSize(0.045);
	    histos["DYJetsToLL"]->histo1D[index]->GetYaxis()->SetLabelSize(0.04);
	    histos["DYJetsToLL"]->histo1D[index]->Draw(); // no string in the draw options shows fitted function
	    //histos["QstarZm1000"]->histo1D[index]->Draw("hist same");
	    //histos["QstarZm2000"]->histo1D[index]->Draw("hist same");
	    //histos["QstarZm5000"]->histo1D[index]->Draw("hist same");	
	    histopad->Update(); // can also add histopad->Modified() if statsbox is needed

	    std::cout << "Drew Histogram" << std::endl;

	    // plot the residuals
	    residualpad->cd();
   	    TH1F* residualHist = new TH1F("ResInverseDiMuPtHist","",100,0,0.008);
	    residualHist->SetFillColor(kBlue-1);
	    residualHist->SetLineColor(kBlue+1);
	    residualHist->GetXaxis()->SetTitle("1/P_{T}(#mu#mu) [c/GeV]");
	    residualHist->GetXaxis()->SetTitleSize(0.1);
	    residualHist->GetXaxis()->SetTitleOffset(1.0);
	    residualHist->GetXaxis()->SetLabelSize(0.09);
	    residualHist->GetYaxis()->SetTitle("Ratio");
	    residualHist->GetYaxis()->SetTitleSize(0.1);
	    residualHist->GetYaxis()->SetTitleOffset(0.5);
	    residualHist->GetYaxis()->SetLabelSize(0.09);
	    for(int i = 1; i <= histos["DYJetsToLL"]->histo1D[index]->GetNbinsX(); i++){
		double res = 0;
		if(histos["DYJetsToLL"]->histo1D[index]->GetBinError(i) != 0){
		    res = (histos["DYJetsToLL"]->histo1D[index]->GetBinContent(i) - dyfunc->Eval(histos["DYJetsToLL"]->histo1D[index]->GetBinCenter(i))) / histos["DYJetsToLL"]->histo1D[index]->GetBinError(i);
		}
		else if(histos["DYJetsToLL"]->histo1D[index]->GetBinError(i) == 0){
		    res = histos["DYJetsToLL"]->histo1D[index]->GetBinContent(i) - dyfunc->Eval(histos["DYJetsToLL"]->histo1D[index]->GetBinCenter(i));
		}
		residualHist->SetBinContent(i,res);
	    }
	    residualHist->SetStats(0); 
	    residualHist->Draw("hist"); 
	    residualpad->Update(); 
	
	    // draw the plots
	    canvasFit->cd();
	    canvasFit->SaveAs("Hist_Fit" + histoVarName + ".png");   
        } 
	else if(histoVarName != "inverseDiMuPtHist"){
	     //histos["Data"]->histo1D[index]->Draw("same");
	     canvasTemp->SaveAs("Hist_" + histoVarName + ".png");
	}

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

double Plots::dyfunction(double *ptrx, double *p)
{
    float x = ptrx[0];
    double func = p[0]*TMath::Erf(p[1]*TMath::Power(x,p[2])-p[3])-p[0]*TMath::Erf(-p[3]);
    return func;
}

////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////
