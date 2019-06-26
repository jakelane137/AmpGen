#!/bin/ipython3
from ROOT import TFile, TH1D, TCanvas
import os, argparse

parser = argparse.ArgumentParser(description="testing program for polynomials in ampGen")
parser.add_argument("--nEvents", metavar="N", type=int, nargs='?', default=100, help="Number of events")
parser.add_argument("--name", metavar="name", type=str, nargs='?', default="s01_vs_s02", help="Variable to plot, options are: s01, s02, s12, s01_vs_s02, s01_vs_s12, s02_vs_s12")
parser.add_argument("--draw", metavar="draw", type=str, nargs='?', default="colz", help="Draw options for ")
parser.add_argument("--opt", metavar="opt", type=str, nargs='?', default="testPhasePoly", help="options ")
args = parser.parse_args()
N = args.nEvents
name = args.name
draw = args.draw
opt = args.opt
print(N)
print(name)
print(opt)
os.system("Generator --nEvents %i --Output %s.root %s.opt" % (N, opt, opt))
f = TFile.Open("%s.root" % (opt))
s = f.Get(name)
c = TCanvas("c_%s" % (name), name , 1000, 1000) 
c.cd()
s.Draw(draw)
c.SaveAs("%s.png" % (name))