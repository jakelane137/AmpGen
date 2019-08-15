#!/usr/bin/env python 
from ROOT import TGraph2D, TFile, TCanvas, gPad, gStyle
import numpy as np
from matplotlib import pyplot as plt
from math import pi
from mpl_toolkits import mplot3d
import os, argparse
from ampplot import ampplot
from ampplot import set_palette
class diff:
    def __init__(self, nEvents, name, draw1D, draw2D, opt1, opt2, output, input1, input1cc, input2, input2cc, imgtype, generate, QC, EventType1, EventType2, obj, repeat):
        self.nEvents = nEvents
        self.name = name
        self.draw1D = draw1D
        self.draw2D = draw2D
        self.nEvents = nEvents
        self.opt1 = opt1
        self.opt2 = opt2
        self.output = output
        self.input1 = input1
        self.input1cc = input1cc
        self.input2 = input2
        self.input2cc = input2cc
        self.imgtype = imgtype
        self.generate = generate
        self.repeat = repeat
        self.QC = QC
        self.EventType1 = EventType1
        EventType1CCarr = self.EventType1.split(" ")
        EventType1CCarr[0] = "Dbar0"
        self.EventType1CC = " ".join(EventType1CCarr)
        self.EventType2 = EventType2
        EventType2CCarr = EventType2.split(" ")
        EventType2CCarr[0] = "Dbar0"
        self.EventType2CC = " ".join(EventType2CCarr)
        self.obj = obj
        print(self.input1)

    def difference(self):       
        if (self.generate or self.input1=="input1" or self.input1cc=="input1CC"):
            generate = True
            self.input1 = self.output + "/" + "1"
            self.input1cc = self.input1+"CC"
            os.system("mkdir -p %s" % (self.input1))
            os.system("mkdir -p %s" % (self.input1cc))
            self.input1 += "D0.root"
            self.input1cc += "Dbar0.root"
            a1 = ampplot(self.nEvents, self.name, self.draw1D, self.draw2D, self.opt1, self.input1, self.imgtype, generate, self.EventType1)
            a1CC = ampplot(self.nEvents, self.name, self.draw1D, self.draw2D, self.opt1, self.input1cc, self.imgtype, generate, self.EventType1CC)
            a1.plot()
            a1CC.plot()
            if (self.repeat):
                self.input2 = self.output + "/" + "2"
                self.input2cc = self.input2+"CC"
                os.system("mkdir -p %s" % (self.input2))
                os.system("mkdir -p %s" % (self.input2cc))
                self.input2 += "D0.root"
                self.input2cc += "Dbar0.root"
                a2 = ampplot(self.nEvents, self.name, self.draw1D, self.draw2D, self.opt2, self.input2, self.imgtype, generate, self.EventType2)
                a2CC = ampplot(self.nEvents, self.name, self.draw1D, self.draw2D, self.opt2, self.input2cc, self.imgtype, generate, self.EventType2CC)
                a2.plot()
                a2CC.plot()
        print("Opening %s" % self.input1)
        fD01 = TFile("%s" % (self.input1))
        print("Opening %s" % self.input1cc)
        fDbar01 = TFile("%s" % (self.input1cc))
        gD01 = fD01.Get(self.obj)
        gDbar01 = fDbar01.Get(self.obj)
        gr1 = self.plot(gD01, gDbar01, "%s/%sdiff.%s" % (self.output, self.obj ,self.imgtype))
        if self.repeat:
            fD02 = TFile("%s" % (self.input2))
            fDbar02 = TFile("%s" % (self.input2cc))
            gD02 = fD02.Get(self.obj)
            gDbar02 = fDbar02.Get(self.obj)
            gr2 = self.plot(gD02, gDbar02, "%s/%sdiff_repeat.%s" % (self.output, self.obj, self.imgtype))
            grD = self.plot(gr1, gr2, "%s/%sdiff_consistency.%s" % (self.output, self.obj, self.imgtype), self.repeat)

    def plot(self, gD01, gDbar01, repeat=False):
        N = gD01.GetN()

        xD01 = gD01.GetX()
        yD01 = gD01.GetY()
        zD01 = gD01.GetZ()
        xDbar01 = gDbar01.GetX()
        yDbar01 = gDbar01.GetY()
        zDbar01 = gDbar01.GetZ()
        gr1 = TGraph2D(N)
        gr1.SetName("delta" + self.obj)

        for i in range(N):
            x1 = xD01[i]
            y1 = yD01[i]
            if self.obj=="gAbs":
                z1 =  gDbar01.Interpolate(y1,x1) / zD01[i] * 100
            else:
                z1 = gDbar01.Interpolate(y1, x1) - zD01[i] * 100
                if (z1 < 0):
                    z1 += 2 * pi 
            #z1 *= 1/(2*pi)
            #z1 = zDbar01[i] - gD01.Interpolate(y1,x1)
            gr1.SetPoint(i, x1, y1, z1)

        xD1 = gr1.GetX()
        yD1 = gr1.GetY()
        zD1 = gr1.GetZ()


        #set_palette()

        theta = 89.9
        phi=0.1
        c1 = TCanvas("c1", "c1", 4000, 4000)
        gPad.SetLeftMargin(0.1)
        c1.cd()

        
        titles = {
            "gArg":"#delta_{D}",
            "gAbs": "|A_{#bar{D}^{0}}|/|A_{D^{0}}|"
        }
        title = titles[self.obj]
        if (repeat):
            title = "#Delta" + title
        gr1.SetTitle("%s ; m^{2}_{K_{S}^{0} #pi^{+}} ; m^{2}_{K_{S}^{0} #pi^{-}}" % (title))
        gr1.GetXaxis().SetLabelOffset(15)
        gr1.GetYaxis().SetLabelOffset(15)
        gr1.GetZaxis().SetLabelOffset(15)
        gr1.SetMargin(0.02)
        gr1.Draw(self.draw2D)
        gPad.SetTheta(theta)
        gPad.SetPhi(phi)
        gPad.SetLeftMargin(0.15)
        gStyle.SetPalette(55)
        gPad.Update()
        c1.SaveAs("%s/Delta_%s.%s" % (self.output, self.obj, self.imgtype))
        return gr1

def main():
    defaultOpt= os.environ['AMPGEN'] + "/kspipi/opts/belle.opt"
    parser = argparse.ArgumentParser(description="ampGen difference script")
    parser.add_argument("--nEvents", metavar="N", type=int, nargs='?', default=10000, help="Number of events")
    parser.add_argument("--name", metavar="name", type=str, nargs='?', default="all", help="Variable to plot, options are: s01, s02, s12, s01_vs_s02, s01_vs_s12, s02_vs_s12")
    parser.add_argument("--draw1D", metavar="draw1D", type=str, nargs='?', default="C", help="Draw options for 1D plots")
    parser.add_argument("--draw2D", metavar="draw2D", type=str, nargs='?', default="COLZ", help="Draw options for 2D plots")
    parser.add_argument("--opt1", metavar="opt1", type=str, nargs='?', default="%s"% defaultOpt, help="options ")
    parser.add_argument("--opt2", metavar="opt2", type=str, nargs='?', default="%s"% defaultOpt, help="options ")
    parser.add_argument("--output", metavar="out", type=str, nargs='?', default="output", help="location for the output png ")
    parser.add_argument("--input1", metavar="in1", type=str, nargs='?', default="input1", help="location for the input png ")
    parser.add_argument("--input1cc", metavar="in1", type=str, nargs='?', default="input1", help="location for the input png ")
    parser.add_argument("--input2", metavar="in2", type=str, nargs='?', default="input2", help="location for the input png ")
    parser.add_argument("--input2cc", metavar="in2", type=str, nargs='?', default="input2", help="location for the input png ")
    parser.add_argument("--imgtype", metavar="imgtype", type=str, nargs='?', default="eps", help="plot input picture type (eps) ")
    parser.add_argument("--generate", action='store_true')
    parser.add_argument("--repeat", action='store_true')
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
    input1 = args.input1
    input2 = args.input2
    input1cc = args.input1cc
    input2cc = args.input2cc
    imgtype = args.imgtype
    generate = args.generate
    repeat = args.repeat
    QC = args.QC
    EventType1 = args.EventType1
    EventType1CCarr = EventType1.split(" ")
    if EventType1CCarr[0]=="D0":
        EventType1CCarr[0] = "Dbar0"
    elif EventType1CCarr[0]=="Dbar0":
        EventType1CCarr[0] = "D0"
    EventType1CC = " ".join(EventType1CCarr)
    EventType2 = args.EventType2
    EventType2CCarr = EventType2.split(" ")
    if EventType2CCarr[0]=="D0":
        EventType2CCarr[0] = "Dbar0"
    elif EventType2CCarr[0]=="Dbar0":
        EventType2CCarr[0] = "D0"

    EventType2CC = " ".join(EventType2CCarr)
    print(input1)
    print(input2)
    objects = ["gArg", "gAbs"]
    for obj in objects:
        D = diff(nEvents, name, draw1D, draw2D, opt1, opt2, output, input1, input1cc, input2, input2cc, imgtype, generate, QC, EventType1, EventType2, obj, repeat)
        D.difference()

if __name__=="__main__":
    main()

