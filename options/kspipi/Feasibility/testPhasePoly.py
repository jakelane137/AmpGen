#!/bin/ipython3
from ROOT import TFile, TH1D, TCanvas
import os, argparse

parser = argparse.ArgumentParser(description="testing program for polynomials in ampGen")
parser.add_argument("--nEvents", metavar="N", type=int, nargs='?', default=1, help="Number of events")
args = parser.parse_args()
N = args.nEvents

print(N)
os.system("Generator --nEvents %i testPhasePoly.opt" % (N))
f = TFile.Open("testPhasePoly.root")
s_pipi = f.Get("s12")
c_pipi = TCanvas("c_pipi", "s_{\pi \pi} distribution", 1000, 1000)
c_pipi.cd()
s_pipi.Draw("E1")
c_pipi.SaveAs("s_pipi.png")