
import multiprocessing
from ROOT import TGraph2D, TFile, TCanvas, gPad, TH1D, gStyle, TLegend, gROOT
import numpy as np
#from matplotlib import pyplot as plt
from math import cos, tan, sin, radians, degrees, sqrt
#from mpl_toolkits import mplot3d
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
        self.output = f"{self.output}/{self.EventType.split()[0]}/"
        self.optType = ""
        optFile = open(self.opt)
        string = optFile.read()
        if "polar" in string:
            self.optType = "polar"
        elif "cartsian" in string:
            self.optType = "cartesian"
        if "deg" in string:
            self.angleType = "deg"
        elif "rad" in string:
            self.angleType = "rad"

    def fit(self):
        subprocess.call(("mkdir -p %s" % (self.output)).split())
        os.system(f"cp {self.opt} {self.output}")
        runGen="echo \"no need to regenerate\""
        if (self.generate):
            DataSampleArr = self.opt.split(".")[0].split("/")
            DataSampleStr = DataSampleArr[len(DataSampleArr) - 1]
            #self.DataSample = self.output + "/" + self.DataSample[len(self.DataSample) - 1] + ".root"
            self.DataSample = f"{self.output}/{DataSampleStr}.root"

            #print(self.EventType)
#            runGen = "Generator --EventType='%s' --Output=%s --nEvents %i %s | tee %s/gen.log" % (self.EventType, self.DataSample, self.nEvents, self.opt, self.output)
            runGen = f"Generator --EventType \"{self.EventType}\" --Output {self.DataSample} --nEvents {self.nEvents} {self.opt} | tee {self.output}/gen.log"
            print(runGen)
            #subprocess.call(runGen.split(","))
            
        if (self.IntegrationSample == "NONE"):
#            runFit = "SignalOnlyFitter --DataSample %s --EventType \"%s\" --Plots %s/plots.root --nEvents %i --nCores %i --LogFile %s/fit.log %s" % (self.DataSample, self.EventType, self.output, self.nEvents * self.mcMult, self.nCores, self.output, self.opt)
            runFit = f"SignalOnlyFitter --DataSample {self.DataSample} --EventType \"{self.EventType}\" --Plots {self.output}/plots.root --nEvents {self.nEvents * self.mcMult} --nCores {self.nCores} --LogFile {self.output}/fit.log {self.opt}"
        else:
            #runFit = "SignalOnlyFitter --DataSample %s --EventType \"%s\" --Plots %s/plots.root --IntegrationSample %s --nCores %i --LogFile %s/fit.log %s" % (self.DataSample, self.EventType, self.output, self.IntegrationSample, self.nCores, self.output, self.opt)
            runFit = f"SignalOnlyFitter --DataSample {self.DataSample} --EventType \"{self.EventType}\" --IntegrationSample {self.IntegrationSample} --Plots {self.output}/plots.root --nCores {self.nCores} --LogFile {self.output}/fit.log {self.opt}"
       
        #runGenMC = "Generator --EventType='%s' --Output=%s --nEvents %i %s | tee %s/gen.log" % (self.EventType, self.IntegrationSample, self.nEvents, self.opt, self.output)
        #runFit = "SignalOnlyFitter --DataSample %s --EventType \"%s\" --Plots %s/plots.root --IntegrationSample %s --nCores %i --LogFile %s/fit.log %s" % (self.DataSample, self.EventType, self.output, self.IntegrationSample, self.nCores, self.output, self.opt)
        host = os.environ['HOSTNAME']
        #if "lxplus" in host:
        #    runGen = "lb-run -c x86_64-centos7-gcc62-opt ROOT " + runGen
        #    runFit = "lb-run -c x86_64-centos7-gcc62-opt ROOT " + runFit
        #subprocess.call(runFit.split())
        os.system(runGen)
       # os.system(runGenMC)
        print(runFit)
        os.system(runFit)
       
        fittedOpt = self.opt.split("/")
        fittedOpt = fittedOpt[len(fittedOpt) - 1]
        fittedOpt = fittedOpt.split(".opt")
        fittedOpt = fittedOpt[0]
        oldpar = open(self.opt)
        fitLog = open("%s/fit.log" %(self.output))
        comOpt = open("%s/opt.log" %(self.output), "w")
        fitRes = open("%s/fitted_%s.opt" % (self.output, fittedOpt), "w")
        fitRes.write("CouplingConstant::Coordinates  cartesian\n")
        fitRes.write("Import $AMPGENROOT/options/kMatrix.opt\n")
        fitRes.write("Particle::DefaultModifier BL\n")
        fitRes.write("Particle::SpinFormalism   Canonical\n")
        print(fitLog.name)
        for line in fitLog.readlines():
           
            linearr = line.split()[0:5]
            fitParam =0 
            fitErr =0
            fitName = linearr[1]
            if (linearr[0]=="Parameter"):
                fitParam = float(linearr[3])
                fitErr = float(linearr[4])
                ''' 
                if (fitErr > fitParam):
                    fitErr = 0.01 * abs(fitParam)
                    linearr[4] = str(fitErr)
                '''
                newline = " ".join(linearr[1:])
                
 #               print(newline)
                fitRes.write(newline + "\n")
            oldpar.seek(0)
            for par in oldpar.readlines():
                pararr = par.split()
                #print(f"pararr = {pararr}")
                oldParam=0
                oldErr=0 
                comLine=""
                if len(pararr) > 0:
                    oldName = pararr[0]
#                    print(f"oldname = {oldName}\n fitName = {fitName}")

                    if oldName in fitName: 
                       # print(f"len(pararr) = {len(pararr)}") 
                        if len(pararr)>6:
                            #print(fitName)
                            print(f"y = {pararr[5]}")
                            x1 = float(pararr[2])
                            dx1 = float(pararr[3])
                            x2 = float(pararr[5])
                            dx2 = float(pararr[6])
                            x=x1
                            dx=dx1
                            y=x2
                            dy=dx2
                            #print(f"optType={self.optType} \n angleType = {self.angleType}")
                            '''
                            if self.optType=="polar":
                                if (self.angleType=="deg"):
                                    x2 = radians(x2)
                                    dx2 = radians(dx2)
                                x = x1 * cos(x2)
                                dx = x * sqrt((dx1/x1)**2 + (tan(x2) * dx2)**2)
                                y = x1 * cos(x2)
                                if (tan(x2)!=0):
                                    dy = y * sqrt((dx1/x1)**2 + (dx2/tan(x2) )**2)
                                else:
                                    dy=0
                            '''
                            if "_Re" in fitName: 
                                comLine = f"{fitName}\nFitted Value = {fitParam} ± {fitErr} \nInitial Value = {x} ± {dx} \n"
                                #print(comLine)
                                comOpt.write(comLine)

                            elif "_Im" in fitName:

                                comLine = f"{fitName}\nFitted Value = {fitParam} ± {fitErr} \nInitial Value = {y} ± {dy} \n"
                                
                                comOpt.write(comLine)
                        else:
                            x = float(pararr[2])
                            dx = float(pararr[3])

                            comLine = f"{fitName}\nFitted Value = {fitParam} ± {fitErr} \nInitial Value = {x} ± {dx} \n"
                            
                            comOpt.write(comLine)

        fitLog.close()
        fitRes.close()
        comOpt.close()
        
        #runGen = "Generator --EventType '%s' --Output %s/%sMC.root --nEvents %i %s/fitted_%s.opt" % (self.EventType, self.output , fittedOpt ,self.nEvents * self.mcMult, self.output, fittedOpt)
        runGen = f"Generator --EventType \"{self.EventType}\" --Output {self.output}/{fittedOpt}MC.root --nEvents {self.nEvents * self.mcMult} {self.output}/fitted_{fittedOpt}.opt"
        print(runGen)
        os.system(runGen)
        self.IntegrationSample ="%s/%sMC.root" % (self.output, fittedOpt) 
        #runFit = "SignalOnlyFitter --DataSample %s --EventType \"%s\" --Plots %s/plots.root --IntegrationSample %s --nCores %i --LogFile %s/fit.log %s" % (self.DataSample, self.EventType, self.output, self.IntegrationSample, self.nCores, self.output, self.opt)
        runFit = f"SignalOnlyFitter --DataSample {self.DataSample} --EventType \"{self.EventType}\" --Plots {self.output}/plots.root --IntegrationSample {self.IntegrationSample} --nCores {self.nCores} --LogFile {self.output}/regenFit.log {self.opt}"
        #os.system(runFit)
        print(runFit)
        self.doPlots()
        




    def doPlots(self, doNorm=True):
        gROOT.SetBatch(1)
        objs = ["s01", "s02", "s12", "s01_vs_s02", "s01_vs_s12", "s02_vs_s12"]
        data = TFile.Open(self.DataSample)
        os.system(f"mkdir -p {self.output}/initial")
        apInit = ampplot(self.nEvents,"all", self.draw1D, self.draw2D, self.DataSample, f"{self.output}/initial/", self.imgtype, False, self.EventType)
        apReg = ampplot(self.nEvents,"all", self.draw1D, self.draw2D, self.IntegrationSample, f"{self.output}/regenerated/", self.imgtype, False, self.EventType)
        apInit.plot()
        apReg.plot()
        print(data)
        mc = TFile.Open(self.IntegrationSample)
        plots = TFile.Open(f"{self.output}/plots.root")
        print(mc)
        for obj in ["s01", "s02", "s12"]:
            c = TCanvas(f"c{obj}", f"c{obj}", 1500, 1000)
            x = plots.Get(f"Data_{obj}")
            xmc = plots.Get(f"Model_cat1_{obj}")
            if doNorm:
                x.Scale(1/x.GetEntries())
                xmc.Scale(1/x.GetEntries())
            diff = x.Clone("div")
            diff.Add(xmc, -1)
            draw = "SAME E1"
            drawmc="SAME C HIST"  
            gPad.SetLeftMargin(0.15)
            gPad.SetBottomMargin(0.15)

            xmc.SetLineWidth(4)
            xmc.SetLineColor(4)
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
            os.system(f"mkdir -p {self.output}/fitted")
            c.SaveAs(f"{self.output}/fitted/{obj}.{self.imgtype}")
            cdiff = TCanvas(f"c{obj}_fitted_difference" , f"c{obj}_fitted_difference", 1000, 1200)
            cdiff.cd()
            diff.SetStats(0)
            gPad.SetLeftMargin(0.15)
            gPad.SetBottomMargin(0.15)
            diff.SetTitle(f"Normalised {obj}(Data) - {obj}(Fit)" )
            diff.GetXaxis().SetTitleOffset(1.5)
            diff.GetYaxis().SetTitleOffset(2)
            diff.Draw(draw)
            os.system(f"mkdir -p {self.output}/difference")
            cdiff.SaveAs(f"{self.output}/difference/{obj}.{self.imgtype}")

       
        if self.imgtype=="eps":
            cmd = f"cd {self.output} ; rm -rf *.tar.gz ;tar cvfz plots.tar.gz *.eps; mogrify -format png *.eps; cd -"
            cmd_fitted = f"cd {self.output}/fitted ; rm -rf *.tar.gz ;tar cvfz plots.tar.gz *.eps; mogrify -format png *.eps; cd -"
            cmd_regenerated = f"cd {self.output}/regenerated ; rm -rf *.tar.gz ;tar cvfz plots.tar.gz *.eps; mogrify -format png *.eps; cd -"
            cmd_difference = f"cd {self.output}/difference ; rm -rf *.tar.gz ;tar cvfz plots.tar.gz *.eps; mogrify -format png *.eps; cd -"
            print(cmd)
    #        prc = subprocess.Popen(cmd, stdout=subprocess.PIPE, shell=True)
            os.system(cmd)
            os.system(cmd_fitted)
            os.system(cmd_regenerated)
            os.system(cmd_difference)
    #        stdout, err = prc.communicate()
        
        




def main():
    defaultOpt=  f"{os.environ['AMPGEN']}/kspipi/opts/belle.opt"
    parser = argparse.ArgumentParser(description="ampGen plotting script")
    parser.add_argument("--nEvents", metavar="nEvents", type=int, nargs='?', default=100, help="Number of events")
    parser.add_argument("--name", metavar="name", type=str, nargs='?', default="all", help="Variable to plot, options are: s01, s02, s12, s01_vs_s02, s01_vs_s12, s02_vs_s12")
    parser.add_argument("--draw1D", metavar="draw1D", type=str, nargs='?', default="", help="Draw options for 1D plots")
    parser.add_argument("--draw2D", metavar="draw2D", type=str, nargs='?', default="PCOLZ", help="Draw options for 2D plots")
    parser.add_argument("--opt", metavar="opt", type=str, nargs='?', default="%s" % (defaultOpt), help="options ")
    parser.add_argument("--output", metavar="out", type=str, nargs='?', default="output" , help="location for the output png ")
    parser.add_argument("--imgtype", metavar="imgtype", type=str, nargs='?', default="png", help="plot output picture type (eps) ")
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
           
