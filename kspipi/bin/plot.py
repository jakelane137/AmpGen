#!/bin/python3
from ROOT import TFile, TH1D, TCanvas,TGraph2D, TH2D, gStyle, RooFit, RooRealVar, RooDataHist, RooArgList, gPad, gROOT, RooPlot
#import LHCbStyle
import os, argparse

def makePlot(s):
    if (type(s)==TH1D):
        s.SetStats(0)
        x = RooRealVar("x", "x", 0, 3)
        l = RooArgList(x)
        dh = RooDataHist("dh", "dh", l, s)
        frame = x.frame()

        dh.plotOn(frame)
        frame.SetTitle(name)
        #frame.GetXaxis().SetTitle(s.GetXaxis().GetTitle())
        frame.GetYaxis().SetTitle(s.GetYaxis().GetTitle())

       
#        frame.GetYaxis().SetTopMargin(0.15)
        #frame.Draw(draw)
        return frame


    elif (type(s) == TH2D):
        s.SetStats(0)
        x = RooRealVar("x", "x", 0, 3)
        y = RooRealVar("y", "y", 0, 3)
        l = RooArgList(x,y);
        dh = RooDataHist("dh", "dh", l, s)
        t = TGraph2D(s)
        #t.GetXaxis().SetTitle(s.GetXaxis().GetTitle())
        return t
        

    elif (type(s)==TGraph2D):
        s.SetMarkerSize(1.0)
        s.SetMarkerStyle(1)
        return s
    





parser = argparse.ArgumentParser(description="testing program for polynomials in ampGen")
parser.add_argument("--nEvents", metavar="N", type=int, nargs='?', default=100, help="Number of events")
parser.add_argument("--name", metavar="name", type=str, nargs='?', default="all", help="Variable to plot, options are: s01, s02, s12, s01_vs_s02, s01_vs_s12, s02_vs_s12")
parser.add_argument("--draw1D", metavar="draw1D", type=str, nargs='?', default="C", help="Draw options for 1D plots")
parser.add_argument("--draw2D", metavar="draw2D", type=str, nargs='?', default="colz", help="Draw options for 2D plots")
parser.add_argument("opt", metavar="opt", type=str, nargs='?', default="testPhasePoly", help="options ")
parser.add_argument("--output", metavar="out", type=str, nargs='?', default="output", help="location for the output png ")
parser.add_argument("--imgtype", metavar="imgtype", type=str, nargs='?', default="eps", help="plot output picture type (eps) ")
parser.add_argument("--generate", action='store_true')
args = parser.parse_args()
N = args.nEvents
name = args.name
draw1D = args.draw1D
draw2D = args.draw2D
opt = args.opt
out = args.output
generate = args.generate
imgtype = args.imgtype
print(N)
print(name[1:])
print(opt)

GeVc2 = "GeV ^{2}/#it{c} ^{4}"
kspip = "s(K_{ S}^{ 0} #pi^{+})"
kspim = "s(K_{ S}^{ 0} #pi^{-})"
pippim = "s(#pi^{+} #pi^{-})"


titles = {"gArg":"Phase of A(%s, %s)" % (kspip, kspim),
          "gAbs": "Magnitude of A(%s, %s)" % (kspip, kspim),
          "s01":"%s distribution" % (kspip), 
          "s02":"%s distribution" % (kspim), 
          "s12":"%s distibution" % (kspim),
          "s01_vs_s02" : "Dalitz plot of %s vs %s" % (kspip, kspim),
          "s01_vs_s12" : "Dalitz plot of %s vs %s" % (kspip, pippim),
          "s02_vs_s12" : "Dalitz plot of %s vs %s" % (kspim, pippim)
         }

xtitles = {"gArg" : "%s / (%s)" % (kspip, GeVc2),
           "gAbs" : "%s / (%s)" % (kspip, GeVc2) ,
           "s01"  : "%s / (%s)" % (kspip, GeVc2),
           "s02"  :  "%s / (%s)" % (kspim, GeVc2),
           "s12"  :  "%s / (%s)" % (pippim, GeVc2),
           "s01_vs_s02"  : "%s / (%s)" % (kspip, GeVc2),
           "s01_vs_s12"  : "%s / (%s)" % (kspip, GeVc2),
           "s02_vs_s12"  : "%s / (%s)" % (kspim, GeVc2)
          }
ytitles = {"gArg" : "%s / (%s)" % (kspim, GeVc2),
           "gAbs" : "%s / (%s)" % (kspim, GeVc2) ,
           "s01"  : "%s / (%s)" % (kspip, GeVc2),
           "s02"  :  "%s / (%s)" % (kspim, GeVc2),
           "s12"  :  "%s / (%s)" % (pippim, GeVc2),
           "s01_vs_s02"  : "%s / (%s)" % (kspim, GeVc2),
           "s01_vs_s12"  : "%s / (%s)" % (pippim, GeVc2),
           "s02_vs_s12"  : "%s / (%s)" % (pippim, GeVc2)
          }

title=""
mymacroPath  = os.environ['AMPGEN'] + "/kspipi/macro/"
gROOT.SetMacroPath(os.pathsep.join([gROOT.GetMacroPath(), mymacroPath]))
#gROOT.LoadMacro("lhcbStyle.C")

os.system("mkdir %s" % (out))
if (generate):
    os.system("Generator --nEvents %i --Output %s.root %s.opt" % (N, out, opt))
f = TFile.Open("%s.root" % (out))
if (name=="gArg" or name=="gAbs" or name == "s01_vs_s02"):
    title = name[1:] + "(A(m^{2}_{K_{S}^{0}#pi^{+}},m^{2}_{K_{S}^{0}#pi^{-}})); m^{2}_{K_{S}^{0}#pi^{+}}(GeV); m^{2}_{K_{S}^{0}#pi^{-}} (GeV)"

if (name == "all"):
    names = ["s01", "s02", "s12", "s01_vs_s02", "s01_vs_s12", "s02_vs_s12", "gArg", "gAbs"]

    for iname in names:
        s = f.Get(iname)
        obj = makePlot(s)
        obj.GetXaxis().SetTitle(xtitles[iname])
        obj.GetXaxis().SetTitleOffset(0.5)
        draw=draw1D
        if (type(obj)!=TH1D):

            print(ytitles[iname])
            obj.GetYaxis().SetTitle(ytitles[iname])
            draw=draw2D
        obj.SetTitle(titles[iname])
        if (type(obj)==TGraph2D):
            print("test")
            print(ytitles[iname])
            obj.SetMarkerSize(1)
            obj.SetMarkerStyle(2)
            obj.SetTitle(titles[iname] + ";" + xtitles[iname] + ";" + ytitles[iname])
        c = TCanvas("c_%s" % (iname), iname , 1500, 1000) 
        c.cd()
    
        gStyle.SetPalette(55)
        #gPad.SetLeftMargin(0.15)
        obj.Draw(draw)
        c.SaveAs("%s/%s.%s" % (out, iname,imgtype))



else:
    s = f.Get(name)
    obj=makePlot(s)
#    obj.GetXaxis().SetTitle(xtitles[name])
 #   obj.GetXaxis().SetTitleOffset(0)
    c = TCanvas("c_%s" % (name), name, 1500, 1000)
    c.cd()


    gStyle.SetPalette(55)
    gStyle.SetPadLeftMargin(0)
    if (type(obj)==TH1D or type(obj)==RooPlot):
        obj.SetTitle("%s ; %s"% (titles[name], xtitles[name]))
#        obj.GetXaxis().SetTitleOffset(500)


        draw=draw1D
    else:
        draw=draw2D

        #obj.SetMarkerSize(1)
        #obj.SetMarkerStyle(2)
        obj.SetTitle("%s; %s; %s"% (titles[name],xtitles[name], ytitles[name]))
        obj.SetTitleOffset(1.25)
        print(ytitles[name])
        #obj.GetYaxis().SetTitle(ytitles[name])



#    obj.SetTitle(titles[name] + "; test")
   # obj.SetTitle("tset")
   # gStyle.SetTitleX("testTitle")
#    obj.SetTitleOffset(0.1)
    obj.Draw(draw)
    c.SaveAs("%s/%s.%s" % (out, name, imgtype))



