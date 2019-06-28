#!/bin/env ipython 
from ROOT import TGraph2D, TFile, TCanvas
import numpy as np
from matplotlib import pyplot as plt
from mpl_toolkits import mplot3d
import os, argpars
from ampplot.py import ampplot
parser = argparse.ArgumentParser(description="ampGen difference script")
parser.add_argument("--nEvents", metavar="N", type=int, nargs='?', default=100, help="Number of events")
parser.add_argument("--name", metavar="name", type=str, nargs='?', default="all", help="Variable to plot, options are: s01, s02, s12, s01_vs_s02, s01_vs_s12, s02_vs_s12")
parser.add_argument("--draw1D", metavar="draw1D", type=str, nargs='?', default="C", help="Draw options for 1D plots")
parser.add_argument("--draw2D", metavar="draw2D", type=str, nargs='?', default="colz", help="Draw options for 2D plots")
parser.add_argument("opt1", metavar="opt1", type=str, nargs='?', default="belle", help="options ")
parser.add_argument("opt2", metavar="opt2", type=str, nargs='?', default="belle", help="options ")
parser.add_argument("--output", metavar="out", type=str, nargs='?', default="output", help="location for the output png ")
parser.add_argument("--imgtype", metavar="imgtype", type=str, nargs='?', default="eps", help="plot output picture type (eps) ")
parser.add_argument("--generate", action='store_true')
args = parser.parse_args()
nEvents = args.nEvents
name = args.name
draw1D = args.draw1D
draw2D = args.draw2D
nEvents = args.nEvents
opt1 = args.opt1
opt2 = args.opt2
output = args.output
imgtype = args.imgtype
generate = args.generate

a1 = ampplot(nEvents, name, draw1D, draw2D, opt1, output, imgtype, generate)

fD01 = TFile("D01.root")
fD02 = TFile("D02.root")
fDbar01 = TFile("Dbar01.root")
fDbar02 = TFile("Dbar02.root")

gD01 = fD01.Get("gArg")
gD02 = fD02.Get("gArg")
gDbar01 = fDbar01.Get("gArg")
gDbar02 = fDbar02.Get("gArg")


N = gD01.GetN()
xD01 = gD01.GetX();
yD01 = gD01.GetY();
zD01 = gD01.GetZ();
xD02 = gD02.GetX();
yD02 = gD02.GetY();
zD02 = gD02.GetZ();
xDbar01 = gDbar01.GetX();
yDbar01 = gDbar01.GetY();
zDbar01 = gDbar01.GetZ();
xDbar02 = gDbar02.GetX();
yDbar02 = gDbar02.GetY();
zDbar02 = gDbar02.GetZ();

gr1 = TGraph2D(N)
gr2 = TGraph2D(N)
for i in range(N):
    x1 = xD01[i]
    y1 = yD01[i]
    z1 = zD01[i] - gDbar01.Interpolate(y1,x1)
    gr1.SetPoint(i, x1, y1, z1)
    x2 = xD02[i]
    y2 = yD02[i]
    z2 = zD02[i] - gDbar02.Interpolate(y2,x2)
    gr2.SetPoint(i, x2, y2, z2)


xD1 = gr1.GetX()
yD1 = gr1.GetY()
zD1 = gr1.GetZ()

xD2 = gr2.GetX()
yD2 = gr2.GetY()
zD2 = gr2.GetZ()
grD = TGraph2D(N)
for i in range(N):
    xD = xD1[i]
    yD = yD1[i]
    zD = zD1[i] - gr2.Interpolate(xD,yD)
    grD.SetPoint(i,xD,yD,zD)


c1 = TCanvas("c1", "c1", 4000, 4000)
c1.cd()
gr1.SetTitle("#Delta #delta_{D}_{1} ; m^{2}_{K_{S}^{0} #pi^{+}} ; m^{2}_{K_{S}^{0} #pi^{-}}")
gr1.Draw("colz")
c1.SaveAs("ampgen_argdiff1.png")
c2 = TCanvas("c2", "c2", 4000, 4000)
c2.cd()

gr2.SetTitle("#Delta #delta_{D}_{2} ; m^{2}_{K_{S}^{0} #pi^{+}} ; m^{2}_{K_{S}^{0} #pi^{-}}")
gr2.Draw("colz")
c2.SaveAs("ampgen_argdiff2.png")
cD = TCanvas("cD", "cD", 4000, 4000)
cD.cd()

grD.SetTitle("#Delta #delta_{D}_{1} - #Delta #delta_{D}_{2} ; m^{2}_{K_{S}^{0} #pi^{+}} ; m^{2}_{K_{S}^{0} #pi^{-}} ")
grD.Draw("colz")
cD.SaveAs("ampgen_argdiffD.png")

