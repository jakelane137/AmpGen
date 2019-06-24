#!/bin/ipython3
from ROOT import TFile, TH1D, TCanvas
import os, argparse

parser = argparse.ArgumentParser(description="testing program for polynomials in ampGen")
parser.add_argument("--nEvents", metavar="N", type=int, nargs='?', default=1, help="Number of events")
parser.add_argument("--name", metavar="name", type=str, nargs='?', default="s12", help="Variable to plot, options are: s01, s02, s12, s01_vs_s02, s01_vs_s12, s02_vs_s12")
parser.add_argument("--draw", metavar="draw", type=str, nargs='?', default="lego2", help="Draw options for ")
args = parser.parse_args()
N = args.nEvents
name = args.name
draw = args.draw
print(N)
print(name)
os.system("Generator --nEvents %i testPhasePoly.opt" % (N))
f = TFile.Open("testPhasePoly.root")
s = f.Get(name)
c = TCanvas("c_%s" % (name), name , 1000, 1000) 
c.cd()
s.Draw(draw)
c.SaveAs("%s.png" % (name))