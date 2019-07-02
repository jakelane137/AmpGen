#!/usr/bin/env python3 
from ROOT import TGraph2D, TFile, TCanvas, gPad
import numpy as np
from matplotlib import pyplot as plt
from mpl_toolkits import mplot3d
import os, argparse
from ampplot import ampplot
from ampplot import set_palette
parser = argparse.ArgumentParser(description="ampGen difference script")
parser.add_argument("--nEvents", metavar="N", type=int, nargs='?', default=100, help="Number of events")
parser.add_argument("--name", metavar="name", type=str, nargs='?', default="all", help="Variable to plot, options are: s01, s02, s12, s01_vs_s02, s01_vs_s12, s02_vs_s12")
parser.add_argument("--draw1D", metavar="draw1D", type=str, nargs='?', default="C", help="Draw options for 1D plots")
parser.add_argument("--draw2D", metavar="draw2D", type=str, nargs='?', default="PCOL", help="Draw options for 2D plots")
parser.add_argument("opt1", metavar="opt1", type=str, nargs='?', default="belle", help="options ")
parser.add_argument("opt2", metavar="opt2", type=str, nargs='?', default="belle", help="options ")
parser.add_argument("--output", metavar="out", type=str, nargs='?', default="output", help="location for the output png ")
parser.add_argument("--output1", metavar="out1", type=str, nargs='?', default="output1", help="location for the output png ")
parser.add_argument("--output2", metavar="out2", type=str, nargs='?', default="output2", help="location for the output png ")
parser.add_argument("--imgtype", metavar="imgtype", type=str, nargs='?', default="eps", help="plot output picture type (eps) ")
parser.add_argument("--generate", action='store_true')
parser.add_argument("--QC", action='store_true')
parser.add_argument("--EventType1", metavar="EventType1", type=str, nargs='?', default="D0 K0S0 pi+ pi-")
parser.add_argument("--EventType2", metavar="EventType2", type=str, nargs='?', default="D0 K0S0 pi+ pi-")
args = parser.parse_args()
nEvents = args.nEvents
name = args.name
draw1D = args.draw1D
draw2D = args.draw2D
nEvents = args.nEvents
opt1 = args.opt1
opt2 = args.opt2
output = args.output
output1 = output + "/" +opt1
output1cc = output1+"CC"
output2 = output + "/" + opt2 
output2cc = output2+"CC"
imgtype = args.imgtype
generate = args.generate
QC = args.QC
EventType1 = args.EventType1
EventType1CCarr = EventType1.split(" ")
EventType1CCarr[0] = "Dbar0"
EventType1CC = " ".join(EventType1CCarr)
EventType2 = args.EventType2
EventType2CCarr = EventType2.split(" ")
EventType2CCarr[0] = "Dbar0"
EventType2CC = " ".join(EventType2CCarr)


os.system("mkdir %s" % (output))

a1 = ampplot(nEvents, name, draw1D, draw2D, opt1, output1, imgtype, generate, EventType1)
a1CC = ampplot(nEvents, name, draw1D, draw2D, opt1, output1cc, imgtype, generate, EventType1CC)

a2 = ampplot(nEvents, name, draw1D, draw2D, opt2, output2, imgtype, generate, EventType2)
a2CC = ampplot(nEvents, name, draw1D, draw2D, opt2, output2cc, imgtype, generate, EventType2CC)

a1.plot()
a1CC.plot()
a2.plot()
a2CC.plot()
fD01 = TFile("%s.root" % (output1))
fDbar01 = TFile("%s.root" % (output1cc))
fD02 = TFile("%s.root" % (output2))
fDbar02 = TFile("%s.root" % (output2cc))

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
while i<N:
    xD = xD1[i]
    yD = yD1[i]
    zD = zD1[i] - gr2.Interpolate(xD,yD)
    grD.SetPoint(i,xD,yD,zD)
    i+=1

#set_palette()
gPad.SetLeftMargin(0.1)
theta = 89.9
phi=0.1
c1 = TCanvas("c1", "c1", 4000, 4000)
c1.cd()

gr1.SetTitle("#Delta #delta_{D}_{1} ; m^{2}_{K_{S}^{0} #pi^{+}} ; m^{2}_{K_{S}^{0} #pi^{-}}")

gr1.SetMargin(0.15)
gr1.Draw(draw2D)
gPad.SetTheta(theta)
gPad.SetPhi(phi)
gPad.Update()
c1.SaveAs("%s/ampgen_argdiff1.%s" % (output,imgtype))
c2 = TCanvas("c2", "c2", 4000, 4000)
c2.cd()

gr2.SetTitle("#Delta #delta_{D}_{2} ; m^{2}_{K_{S}^{0} #pi^{+}} ; m^{2}_{K_{S}^{0} #pi^{-}}")
gr2.SetMargin(0.15)

gr2.Draw(draw2D)
gPad.SetTheta(theta)
gPad.SetPhi(phi)
gPad.Update()
c2.SaveAs("%s/ampgen_argdiff2.%s" % (output,imgtype))
cD = TCanvas("cD", "cD", 4000, 4000)
cD.cd()

grD.SetTitle("#Delta #delta_{D}_{1} - #Delta #delta_{D}_{2} ; m^{2}_{K_{S}^{0} #pi^{+}} ; m^{2}_{K_{S}^{0} #pi^{-}} ")

grD.SetMargin(0.15)
grD.Draw(draw2D)
gPad.SetTheta(theta)
gPad.SetPhi(phi)
gPad.Update()
cD.SaveAs("%s/ampgen_argdiffD.%s" % (output,imgtype))

