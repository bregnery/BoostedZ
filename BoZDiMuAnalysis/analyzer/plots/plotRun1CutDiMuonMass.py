#!/usr/bin/env python

import glob
import ROOT as root
from src.helpers import *

root.gROOT.SetBatch(True)

# Open root files
dy = root.TFile("../DYJetsToLL_Run1Cuts_Hist.root")
json = root.TFile("../Data_Run1Cuts_Hist.root")

# Create TCanvas
canvas = root.TCanvas()

# Access Histograms
#ttHist = tt.Get("phiStarHist")
#ttHist.SetName("TT")
dyHist = dy.Get("dimuonMassHist")
jsonHist = json.Get("dimuonMassHist")

# Create a 2D Histogram for more control
xMin = 60
xMax = 120
yMin = 0
yMax = 20000
xTitle = "M(#mu#mu) [GeV/c^{2}]"

axisHist = root.TH2F("axisHist","M(#mu#mu)",1,xMin,xMax,1,yMin,yMax)
axisHist.GetXaxis().SetTitle(xTitle)
axisHist.GetYaxis().SetTitle("Events/Bin")
axisHist.GetYaxis().SetTitleOffset(1.7)
axisHist.Draw()

jsonHist.SetLineColor(1)
jsonHist.SetMarkerStyle(8)
jsonHist.SetLineStyle(1)
dyHist.SetFillColor(root.kOrange)
dyHist.SetLineColor(root.kOrange)
dyHist.SetMarkerStyle(0)
dyHist.SetFillStyle(1)

leg = root.TLegend(.7,.7,.9,.9,"MC sample")
leg.AddEntry(jsonHist,"JSON data","l")
leg.AddEntry(dyHist,"DY","l")

#canvas.GetPad(0).Update()
#stats_vhmumu = vhmumuHist.GetListOfFunctions().FindObject("stats").Clone("stats_vhmumu")

#y1 = stats_vhmumu.GetY1NDC()
#y2 = stats_vhmumu.GetY2NDC()

#stats_vhmumu.SetY1NDC(2 * y1 - y2)
#stats_vhmumu.SetY2NDC(y1)
#stats_vhmumu.Draw()
dyHist.Draw("hist same")
jsonHist.Draw("SAMES")
leg.Draw()

canvas.SaveAs("Hist_Run1CutsDiMuonMass.png")

