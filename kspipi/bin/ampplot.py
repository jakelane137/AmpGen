#!/bin/python3
from ROOT import TFile, TH1D, TCanvas,TGraph2D, TH2D, gStyle, RooFit, RooRealVar, RooDataHist, RooArgList, gPad, gROOT, RooPlot, TColor
from array import array
#import LHCbStyle
import os, argparse
class ampplot:
    def __init__(self, nEvents, name, draw1D, draw2D, opt, out, imgtype, generate, EventType):
        self.nEvents = nEvents
        self.name = name
        self.draw1D = draw1D
        self.draw2D = draw2D
        self.opt = opt
        self.output = out
        self.imgtype = imgtype
        self.generate = generate
        self.EventType = EventType
    def plot(self):
        gROOT.SetBatch(1)
        N = self.nEvents
        name = self.name
        draw1D = self.draw1D
        draw2D = self.draw2D
        opt = self.opt
        out = self.output
        generate = self.generate
        imgtype = self.imgtype
        EventType = self.EventType
        print(N)
        print(name[1:])
        print(opt)
        print(out)
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
        #gROOT.SetStyle("Plain")

        os.system("mkdir -p %s" % (out))
        
        if (generate):
            os.system("Generator --nEvents %i --Output %s.root --EventType '%s' %s.opt" % (N, out,EventType, opt))
        f = TFile.Open("%s.root" % (out))
        if (name=="gArg" or name=="gAbs" or name == "s01_vs_s02"):
            title = name[1:] + "(A(m^{2}_{K_{S}^{0}#pi^{+}},m^{2}_{K_{S}^{0}#pi^{-}})); m^{2}_{K_{S}^{0}#pi^{+}}(GeV); m^{2}_{K_{S}^{0}#pi^{-}} (GeV)"

        if (name == "all"):
            names = ["s01", "s02", "s12", "s01_vs_s02", "s01_vs_s12", "s02_vs_s12", "gArg", "gAbs"]

            for iname in names:
                s = f.Get(iname)
                obj = makePlot(s)
                obj.GetXaxis().SetTitle(xtitles[iname])
                obj.GetXaxis().SetTitleOffset(1.1)
                draw=draw1D
                if (type(obj)!=TH1D):

                    print(ytitles[iname])
                    obj.GetYaxis().SetTitle(ytitles[iname])
                    draw=draw2D
                obj.SetTitle(titles[iname])
                if (type(obj)==TGraph2D):
                    print("test")
                    print(ytitles[iname])
                    #obj.SetMarkerSize(1)
                    #obj.SetMarkerStyle(2)
                    obj.SetTitle(titles[iname] + ";" + xtitles[iname] + ";" + ytitles[iname])
                    obj.GetXaxis().SetTitleOffset(1.4)
                    obj.GetYaxis().SetTitleOffset(4.4)
                    obj.SetMargin(0.15)
                c = TCanvas("c_%s" % (iname), iname , 1500, 1000) 
                c.cd()
  #              gStyle.SetMarkerSize(1)
 #               gStyle.SetMarkerStyle(1) 

                set_palette();
                gStyle.SetPalette(55)
                gPad.SetLeftMargin(0.1)
                gPad.SetTheta(90)
                gPad.SetPhi(0)
                gPad.Update()
                obj.Draw(draw)
                c.SaveAs("%s/%s.%s" % (out, iname,imgtype))



        else:
            s = f.Get(name)
            obj=makePlot(s)
        #    obj.GetXaxis().SetTitle(xtitles[name])
        #   obj.GetXaxis().SetTitleOffset(0)
            c = TCanvas("c_%s" % (name), name, 1500, 1000)
            c.cd()


            gStyle.SetPalette(100)
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


def makePlot(s):
    if (type(s)==TH1D):
        s.SetStats(0)
        x = RooRealVar("x", "x", 0, 3)
        l = RooArgList(x)
        dh = RooDataHist("dh", "dh", l, s)
        frame = x.frame()

        dh.plotOn(frame)
        #frame.SetTitle(name)
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
        s.SetMarkerSize(1.0)
        s.SetMarkerStyle(1)
        #t.GetXaxis().SetTitle(s.GetXaxis().GetTitle())
        return s
        

    elif (type(s)==TGraph2D):
        s.SetMarkerSize(1.0)
        s.SetMarkerStyle(1)
        return s
    
def set_palette(name="palette", n=100, ncontours=999):
    """Set a color palette from a given RGB list
    stops, red, green and blue should all be lists of the same length
    see set_decent_colors for an example"""

    if name == "gray" or name == "grayscale":
        stops = [0.00, 0.34, 0.61, 0.84, 1.00]
        red   = [1.00, 0.84, 0.61, 0.34, 0.00]
        green = [1.00, 0.84, 0.61, 0.34, 0.00]
        blue  = [1.00, 0.84, 0.61, 0.34, 0.00]
    elif name == "myPalette":
        # (define more palettes)
        stops = range(n)
        stops  = [-3 + float(i)/n for i in stops]
        Cb = 0.4
        Cr = 0.6
        blue = [-1/Cb * i +1 for i in stops]
        green = stops
        red =  [1/(1-Cr) * i for i in stops]
        for i in range(len(stops)):
            if stops[i]<Cb:
                green[i]=0
                red[i]=0
            if stops[i]>Cb and stops[i]<Cr:
                blue[i]=0
                red[i]=0
                if stops[i]<0.5:
                    green[i] = stops[i]/(0.5 - Cb)
                else:
                    green[i] = stops[i]/(0.5 - Cr)
            if stops[i]>Cr:
                green[i]=0
                blue[i]=0 
            

#        stops = [0.00, 0.10, 0.20, 0.30, 0.40, 0.50, 0.60, 0.70, 0.80, 0.90, 1.00]
#        red   = [0.00, 0.00, 0.00, 0.00, 0.10, 0.20, 0.30, 0.40, 0.50, 0.60, 1.00]
#        green = [0.00, 0.10, 0.30, 0.60, 0.80, 0.60, 0.40, 0.20, 0.00, 0.00, 0.00]
#        blue  = [0.50, 0.60, 0.70, 0.80, 0.50, 0.30, 0.00, 0.00, 0.00, 0.00, 0.00]
    else:
        # default palette, looks cool
        stops = [0.00, 0.34, 0.61, 0.84, 1.00]
        red   = [0.00, 0.00, 0.87, 1.00, 0.51]
        green = [0.00, 0.81, 1.00, 0.20, 0.00]
        blue  = [0.51, 1.00, 0.12, 0.00, 0.00]

    s = array('d', stops)
    r = array('d', red)
    g = array('d', green)
    b = array('d', blue)

    npoints = len(s)
    TColor.CreateGradientColorTable(npoints, s, r, g, b, ncontours)
    gStyle.SetNumberContours(ncontours)
    

def main():

    parser = argparse.ArgumentParser(description="ampGen plotting script")
    parser.add_argument("--nEvents", metavar="nEvents", type=int, nargs='?', default=100, help="Number of events")
    parser.add_argument("--name", metavar="name", type=str, nargs='?', default="all", help="Variable to plot, options are: s01, s02, s12, s01_vs_s02, s01_vs_s12, s02_vs_s12")
    parser.add_argument("--draw1D", metavar="draw1D", type=str, nargs='?', default="C", help="Draw options for 1D plots")
    parser.add_argument("--draw2D", metavar="draw2D", type=str, nargs='?', default="PCOL", help="Draw options for 2D plots")
    parser.add_argument("opt", metavar="opt", type=str, nargs='?', default="testPhasePoly", help="options ")
    parser.add_argument("--output", metavar="out", type=str, nargs='?', default="output", help="location for the output png ")
    parser.add_argument("--imgtype", metavar="imgtype", type=str, nargs='?', default="eps", help="plot output picture type (eps) ")
    parser.add_argument("--generate", action='store_true') 
    parser.add_argument("--EventType", metavar="EventType", type=str, nargs='?', default="D0 K0S0 pi+ pi-", help="Event type of form X a b c ")
    args = parser.parse_args()
    N = args.nEvents
    name = args.name
    draw1D = args.draw1D
    draw2D = args.draw2D
    opt = args.opt
    out = args.output
    imgtype = args.imgtype
    generate = args.generate
    EventType = args.EventType
    a = ampplot(N, name, draw1D, draw2D, opt, out, imgtype, generate, EventType)
    a.plot()


if __name__=='__main__':
    main()