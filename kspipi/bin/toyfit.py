#!/usr/bin/python3
import multiprocessing
from ROOT import TGraph2D, TFile, TCanvas, gPad, TH1D, gStyle, TLegend
import numpy as np
from matplotlib import pyplot as plt
from mpl_toolkits import mplot3d
import os, argparse, pickle
from ampplot import ampplot
from ampplot import set_palette, subprocess

class toyFit:
    def __init__(self, nEvents, name, draw1D, draw2D, opt, out, imgtype, generate, EventType, DataSample, IntegrationSample, mcMult, nCores):
        self.nEvents = nEvents
        self.name = name
        self.draw1D = draw1D
        self.draw2D = draw2D
        self.opt = opt
        self.output = out
        self.imgtype = imgtype
        self.generate = generate
        self.EventType = EventType
        self.DataSample = DataSample
        self.IntegrationSample = IntegrationSample
        self.mcMult = mcMult
        self.nCores = nCores
        self.output = self.EventType.split()[0] + "/" + self.output

    def fit(self):
        subprocess.call(("mkdir -p %s" % (self.output)).split())
        if (self.DataSample == "NONE"):
            self.DataSample = self.opt.split(".")[0].split("/")
            self.DataSample = self.output + "/" + self.DataSample[len(self.DataSample) - 1] + ".root"
           
            #print(self.EventType)
            runGen = "Generator --EventType='%s' --Output=%s --nEvents %i %s | tee %s/gen.log" % (self.EventType, self.DataSample, self.nEvents, self.opt, self.output)
            #print(runGen.split(","))
            #subprocess.call(runGen.split(","))
            os.system(runGen)
        if (self.IntegrationSample == "NONE"):
            runFit = "SignalOnlyFitter --DataSample %s --EventType \"%s\" --Plots %s/plots.root --nEvents %i --nCores %i --LogFile %s/fit.log %s" % (self.DataSample, self.EventType, self.output, self.nEvents * self.mcMult, self.nCores, self.output, self.opt)
        else:
            runFit = "SignalOnlyFitter --DataSample %s --EventType \"%s\" --Plots %s/plots.root --IntegrationSample %s --nCores %i --LogFile %s/fit.log %s" % (self.DataSample, self.EventType, self.output, self.IntegrationSample, self.nCores, self.output, self.opt)

        #subprocess.call(runFit.split())
        os.system(runFit)
        #print(runFit)
        fittedOpt = self.opt.split("/")
        fittedOpt = fittedOpt[len(fittedOpt) - 1]
        fittedOpt = fittedOpt.split(".opt")
        fittedOpt = fittedOpt[0]
        fitLog = open("%s/fit.log" %(self.output))
        fitRes = open("%s/fitted_%s.opt" % (self.output, fittedOpt), "w")
        fitRes.write("CouplingConstant::Coordinates  cartesian\n")
        fitRes.write("Import $AMPGENROOT/options/kMatrix.opt\n")
        fitRes.write("Particle::DefaultModifier BL\n")
        fitRes.write("Particle::SpinFormalism   Canonical\n")
        print(fitLog.name)
        for line in fitLog.readlines():
            linearr = line.split()
            newline = ""
            for i in linearr[1:5]:
                newline += i + " "
            if (linearr[0]=="Parameter"):
                print(newline)
                fitRes.write(newline + "\n")

        fitLog.close()
        fitRes.close()
        runGen = "Generator --EventType '%s' --Output %s/%sMC.root --nEvents %i %s/fitted_%s.opt" % (self.EventType, self.output , fittedOpt ,self.nEvents * self.mcMult, self.output, fittedOpt)
        print(runGen)
        os.system(runGen)
        self.IntegrationSample ="%s/%sMC.root" % (self.output, fittedOpt) 
        runFit = "SignalOnlyFitter --DataSample %s --EventType \"%s\" --Plots %s/plots.root --IntegrationSample %s --nCores %i --LogFile %s/fit.log %s" % (self.DataSample, self.EventType, self.output, self.IntegrationSample, self.nCores, self.output, self.opt)
        os.system(runFit)
        print(runFit)
        self.plot()

    def plot(self):
        objs = ["s01", "s02", "s12", "s01_vs_s02", "s01_vs_s12", "s02_vs_s12"]
        data = TFile.Open(self.DataSample)
        print(data)
        mc = TFile.Open(self.IntegrationSample)
        print(mc)
        for obj in objs:
            c = TCanvas("c%s" % (obj), "c%s"%(obj), 1000, 1000)
            gStyle.SetPalette(51)
            c.cd()
            x = data.Get(obj)
            xmc = mc.Get(obj)

            x.Scale(1/x.GetEntries())
            xmc.Scale(1/xmc.GetEntries())
            div = x.Clone("div")
            div.Add(xmc, -1)
            draw="SAME"
            drawmc="SAME BAR"
            if (type(x)==TH1D):
                draw="SAME" + " " + self.draw1D
            else:
                draw="SAME" + " " + self.draw2D
            if (type(xmc)==TH1D):
                drawmc="SAME" + " " + "C" + "HIST" + "P*"
                xmc.SetLineWidth(4)
                xmc.SetLineColor(4)
            else:
                drawmc="SAME" + " " + "COL"
            print(type(x))
            print(type(xmc))
            print(draw)
            print(drawmc)
            gPad.SetLeftMargin(0.15)
            x.SetStats(0)
            xmc.SetStats(0)
            xmc.SetTitle("%s" % (obj))
            xmc.GetXaxis().SetTitleOffset(1.5)
            xmc.GetYaxis().SetTitleOffset(2)
            xmc.Draw(drawmc)
            x.SetTitle("%s" % (obj))
            x.GetXaxis().SetTitleOffset(100)
            x.GetYaxis().SetTitleOffset(100)
            x.Draw(draw)
            leg = TLegend(0.99,0.99,0.85,0.85)
            leg.AddEntry(x, "Data")
            leg.AddEntry(xmc, "Fit")
            leg.Draw("SAME")
            c.SaveAs("%s/%s.%s" % (self.output, obj ,self.imgtype))
            cdiv = TCanvas("c%s_difference" % (obj), "c%s_difference" % (obj), 1000, 1000)
            cdiv.cd()
            div.SetStats(0)

            gPad.SetLeftMargin(0.15)
            div.SetTitle("Normalised %s_{Data} - %s_{Fit}" % (obj, obj) )
            div.GetXaxis().SetTitleOffset(1.5)
            div.GetYaxis().SetTitleOffset(2)
            div.Draw(draw)
            cdiv.SaveAs("%s/%s_difference.%s" % (self.output, obj, self.imgtype))
        




def main():
    defaultOpt= os.environ['AMPGEN'] + "/kspipi/opts/belle.opt"
    parser = argparse.ArgumentParser(description="ampGen plotting script")
    parser.add_argument("--nEvents", metavar="nEvents", type=int, nargs='?', default=100, help="Number of events")
    parser.add_argument("--name", metavar="name", type=str, nargs='?', default="all", help="Variable to plot, options are: s01, s02, s12, s01_vs_s02, s01_vs_s12, s02_vs_s12")
    parser.add_argument("--draw1D", metavar="draw1D", type=str, nargs='?', default="", help="Draw options for 1D plots")
    parser.add_argument("--draw2D", metavar="draw2D", type=str, nargs='?', default="PCOLZ", help="Draw options for 2D plots")
    parser.add_argument("--opt", metavar="opt", type=str, nargs='?', default="%s" % (defaultOpt), help="options ")
    parser.add_argument("--output", metavar="out", type=str, nargs='?', default="output" , help="location for the output png ")
    parser.add_argument("--imgtype", metavar="imgtype", type=str, nargs='?', default="eps", help="plot output picture type (eps) ")
    parser.add_argument("--generate", action='store_true') 
    parser.add_argument("--EventType", metavar="EventType", type=str, nargs='?', default="D0 K0S0 pi+ pi-", help="Event type of form X a b c ")
    parser.add_argument("--DataSample", metavar="DataSample", type=str, nargs='?', default="NONE", help="Event type of form X a b c ")
    parser.add_argument("--IntegrationSample", metavar="IntegrationSample", type=str, nargs='?', default="NONE", help="Event type of form X a b c ")
    parser.add_argument("--mcMult", metavar="mcMult", type=int, nargs='?', default=10, help="Event type of form X a b c ")
    parser.add_argument("--nCores", metavar="nCores", type=int, nargs='?', default=multiprocessing.cpu_count(), help="Event type of form X a b c ")
    args = parser.parse_args()
    nEvents = args.nEvents
    name = args.name
    draw1D = args.draw1D
    draw2D = args.draw2D
    opt = args.opt
    out = args.output
    imgtype = args.imgtype
    generate = args.generate
    EventType = args.EventType
    DataSample = args.DataSample
    IntegrationSample = args.IntegrationSample
    mcMult = args.mcMult
    nCores = args.nCores
    #tf = toyFit(N,name, draw1D,draw2D, opt, out, imgtype, generate, DataSample, IntegrationSample, mcMult)
    tf = toyFit(nEvents, name, draw1D, draw2D, opt, out, imgtype, generate, EventType, DataSample, IntegrationSample, mcMult, nCores)
    tf.fit()

if __name__=='__main__':
    main()
           
