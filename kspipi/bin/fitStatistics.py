from toyfit import toyFit
import numpy as np
import matplotlib as mpl
mpl.use('Agg')
from matplotlib import pyplot as plt
import os, argparse
class fitStatistics:
    def __init__(self, model, output, sampleSize, EventType, generate):
        self.model = model
        self.output = output
        self.sampleSize = sampleSize
        self.fitStatus = np.array
        self.chisq = np.array
        self.nll = np.array
        self.EventType = EventType
        self.generate = generate
        self.Mother = self.EventType.split()[0] 

    
    def getStatFit(self, fitLog):
        _f = open(fitLog)
        _stats = []
        for line in _f.readlines():
            if "FitQuality" in line:
                _stats = line.split()[1:]
        return _stats
    
    def doFit(self, i):
        os.system(f"{self.output}/fit_{i}")
        _tf = toyFit(nEvents=10000, name=f"fit_{i}", draw1D="PCOL", draw2D="PCOLZ", opt=self.model, out=f"{self.output}/fit_{i}", imgtype="png", generate=True, EventType="D0 K0S0 pi+ pi-", DataSample="NONE", IntegrationSample="NONE", mcMult=10, nCores=10)
        if self.generate:
            _tf.fit()
    
    def getFitStats(self):
        i=0
        _statsArr   =   []
        _chisq      =   []
        _fitStatus  =   []
        _nll        =   []
        _ndof        =   []
        _nPar        =   []
        while i<self.sampleSize:
            self.doFit(i)
            _stats = self.getStatFit(f"{self.output}/fit_{i}/{self.Mother}/fit.log")
            _chisq.append(float(_stats[0]))
            _ndof.append(float(_stats[1]))
            _nPar.append(float(_stats[2]))
            _nll.append(float(_stats[3]))
            _fitStatus.append(float(_stats[4]))
            i+=1


            
        self.chisq = np.array(_chisq)
        self.ndof = np.array(_ndof)
        self.chisq = self.chisq/self.ndof
        self.nPar = np.array(_nPar)
        self.nll = np.array(_nll)
        self.fitStatus = np.array(_fitStatus)

    
    def plotFitStats(self):
        self.getFitStats()
        plt.ioff()
        _stats = {"chisq" : self.chisq, 
                "nPar" : self.nPar,
                "nll" : self.nll,
                "fitStatus" : self.fitStatus
                }
        for key in _stats:
            fig = plt.figure()
            ax = plt.hist(_stats[key])
            fig.savefig(f"{self.output}/{key}.png")


def main():
    parser = argparse.ArgumentParser(description="ampGen plotting script")
    parser.add_argument("--model", metavar="model", type=str, nargs='?', default="", help="model file")
    parser.add_argument("--output", metavar="output", type=str, nargs='?', default="", help="output file")
    parser.add_argument("--EventType", metavar="EventType", type=str, nargs='?', default="D0 K0S0 pi+ pi-", help="EventType file")
    parser.add_argument("--sampleSize", metavar="sampleSize", type=int, nargs='?', default=10, help="sampleSize file")
    parser.add_argument("--noGenerate", action='store_false') 
    args = parser.parse_args()
    fitStats = fitStatistics(args.model, args.output, args.sampleSize, args.EventType, args.noGenerate)
    fitStats.plotFitStats()

if __name__=='__main__':
    main()