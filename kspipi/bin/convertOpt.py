#!/bin/python3
import multiprocessing
import decimal
from ROOT import TGraph2D, TFile, TCanvas, gPad, TH1D, gStyle, TLegend
import numpy as np
from matplotlib import pyplot as plt
from mpl_toolkits import mplot3d
import os, argparse, pickle
from ampplot import ampplot
from ampplot import set_palette, subprocess
from math import sqrt, sin, asin, cos, acos, tan, atan, radians, degrees, pi
class convertOpt:
    def __init__(self, file, target, convertType, angleType, ndp):
        self.file = file
        self.target = target
        self.convertType = convertType
        self.angleType = angleType
        self.ndp = ndp
        self.couplingType=""
        _file = open(self.file).read()
        if "cartesian" in _file:
            self.couplingType = "cartesian"
        elif "polar" in _file:
            self.couplingType = "polar"
        if "deg" in _file:
            self.angleType = "deg"
        elif "rad" in _file:
            self.angleType = "rad"


        self.params = self.getParams()
        self.names = self.params["names"]
        self.fix = self.params["fix"]
        self.real = self.params["real"]
        self.imag = self.params["imag"]
        self.abs = self.params["abs"]
        self.phase = self.params["phase"]
        self.dreal = self.params["dreal"]
        self.dimag = self.params["dimag"]
        self.dabs = self.params["dabs"]
        self.dphase = self.params["dphase"]

        self.nComp = len(self.names)
    
    def getParams(self):
        f = open(self.file)
        f.seek(0)
       
        _names = []
        _fix=[]
        _real = []
        _imag = []
        _abs = []
        _phase = []
        _dreal = []
        _dimag = []
        _dabs = []
        _dphase = []
        _err = 5 * 10**(-float(self.ndp))
        for line in f.readlines():
           lineArr = line.split()
           #print(lineArr)
           nP = len(lineArr)
           if (nP == 7):
                _names.append(lineArr[0])
                if self.couplingType=="cartesian":
                    fix = int(lineArr[1])
                    x = float(lineArr[2])
                    dx = float(lineArr[3])
                    y = float(lineArr[5])
                    dy = float(lineArr[6])
                    r = x**2 + y**2
                    dr = _err * r
                    phi=0
                   
                    if abs(x)>0:
                        phi = atan(y/x)
                    else:
                        if abs(y)>0:
                            phi = (y/abs(y)) * pi/2
                        else:
                            phi=0
                    dphi = _err * phi

                    if (dr == 0):
                        dr = _err
                    if (dphi==0):
                        dphi = _err


                    _fix.append(f"{fix}")
                    _real.append(f"%.{self.ndp}f" % x)
                    _imag.append(f"%.{self.ndp}f" % y)
                    _abs.append(f"%.{self.ndp}f" % r)
                    _phase.append(f"%.{self.ndp}f" % phi)
                    _dreal.append(f"%.{self.ndp}f" % dx)
                    _dimag.append(f"%.{self.ndp}f" % dy)
                    _dabs.append(f"%.{self.ndp}f" % dr)
                    _dphase.append(f"%.{self.ndp}f" % dphi)

                    
                elif self.couplingType == "polar":
                    fix = int(lineArr[1])
                    r = float(lineArr[2])
                    dr = float(lineArr[3])
                    phi = float(lineArr[5])
                    dphi = float(lineArr[6])
                    if self.angleType=="deg":
                        phi = radians(phi)
                        dphi = radians(dphi)
                    x = r * cos(phi)
                    dx = _err * abs(x)
                    if (dx ==0):
                        dx = _err
                    y = r * sin(phi)
                    dy = _err * abs(y)
                    if (dy==0):
                        dy = _err

                    

                    _fix.append(f"{fix}")
                    _real.append(f"%.{self.ndp}f" % x)
                    _imag.append(f"%.{self.ndp}f" % y)
                    _abs.append(f"%.{self.ndp}f" % r)
                    _phase.append(f"%.{self.ndp}f" % phi)
                    _dreal.append(f"%.{self.ndp}f" % dx)
                    _dimag.append(f"%.{self.ndp}f" % dy)
                    _dabs.append(f"%.{self.ndp}f" % dr)
                    _dphase.append(f"%.{self.ndp}f" % dphi)



        params = {"names" : _names, "real": _real, "imag" : _imag, "abs" : _abs, "phase" : _phase, "dreal" : _dreal, "dimag" : _dimag, "dabs" : _dabs, "dphase" : _dphase, "fix" : _fix}
        return params

    def printOpts(self):
        _N = len(self.real)
        print(f"Using {self.couplingType} with {self.angleType}") 
        print("{:<50} {:<20} {:<20} {:<20} {:<20}".format('Name', "Real", "Imag", "Abs", "Phase"))

        for i in range(_N):
            print("{:<50} {:<20} {:<20} {:<20} {:<20}".format(self.names[i], self.real[i], self.imag[i], self.abs[i], self.phase[i]))
    
    def makeOpts(self):
        nPolar = f"{self.target}_Polar.opt"
        nCart = f"{self.target}_Cart.opt"
        _fPolar = open(nPolar, "w")
        _fCart = open(nCart, "w")

        _fPolar.write(f"CouplingConstant::Coordinates \"polar\"\nCouplingConstant::AngularUnits \"rad\"\nParticle::DefaultModifier BL\nParticle::SpinFormalism Canonical \n")
        _fCart.write(f"CouplingConstant::Coordinates \"cartesian\" \nCouplingConstant::AngularUnits \"rad\" \nParticle::DefaultModifier BL\nParticle::SpinFormalism   Canonical \n")
        for i in range(self.nComp):

            _fPolar.write(f"{self.names[i]}\t {self.fix[i]}\t {self.abs[i]} \t {self.dabs[i]} \t {self.fix[i]} \t {self.phase[i]} \t {self.dphase[i]} \n")           
            _fCart.write(f"{self.names[i]}_Re \t {self.fix[i]} \t {self.real[i]} \t {self.dreal[i]}\n")
            _fCart.write(f"{self.names[i]}_Im \t {self.fix[i]} \t {self.imag[i]} \t {self.dimag[i]} \n")
        
        _fCart.close()
        _fPolar.close()
        print(f"Made options files {nPolar} and {nCart}")
            

        
        
   
def main():
    defaultOpt= os.environ['AMPGEN'] + "/kspipi/opts/belle.opt"
    defaultTarget = defaultOpt.split(".")[0] + "_polar.opt"
    parser = argparse.ArgumentParser(description="ampGen plotting script")
    parser.add_argument("--file", metavar="file", type=str, nargs='?', default="%s" % (defaultOpt), help="options ")
    parser.add_argument("--target", metavar="target", type=str, nargs='?', default="%s" % (defaultTarget), help="options ")
    parser.add_argument("--convertType", metavar="convertType", type=str, nargs='?', default="polar", help="options ")
    parser.add_argument("--angleType", metavar="angleType", type=str, nargs='?', default="deg", help="options ")
    parser.add_argument("--ndp", metavar="ndp", type=int, nargs='?', default=3, help="options ")
    args = parser.parse_args()
    file = args.file
    convertType = args.convertType
    angleType = args.angleType
    ndp = args.ndp
    target = args.target
    co = convertOpt(file, target, convertType, angleType, ndp)
    co.printOpts()
    co.makeOpts()


if __name__=="__main__":
    main()