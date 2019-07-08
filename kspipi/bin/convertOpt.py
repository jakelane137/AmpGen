#!/bin/python3
import multiprocessing
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
        self.D0Params = self.getParams("D0{")
        self.Dbar0Params = self.getParams("Dbar0{")
        self.PiPiParams = self.getParams("PiPi00[")
        self.allParams = []
        for params in [self.D0Params, self.Dbar0Params, self.PiPiParams]:
            for param in params:
                self.allParams.append(param)


    
    def getParams(self, delim):
        f = open(self.file)
        f.seek(0)
        params=[]
        for line in f.readlines():
            if delim in line:
                params.append(line.split())
        return params

    
    def convert(self, param):
        sum2 = lambda x : sqrt(sum([i**2 for i in x]))
        cos2 = lambda x : cos(x)**2
        tan2 = lambda x : tan(x)**2
        X = lambda r,phi : r * cos(phi)
        Y = lambda r,phi : r * sin(phi)
        R = lambda x,y   : sum2([x,y])
        Phi = lambda x,y : atan(y/x)
        
        newParam=[]
        if self.convertType=="cartesian":
            r = float(param[2])
            dr = float(param[3])
            phi = float(param[5])
            dphi = float(param[6])
            #print(dphi)

            if (self.angleType=="deg"):
                phi = radians(phi)
                dphi = radians(dphi)


            x = X(r, phi)
            y = Y(r, phi)
            dxr = x*dr/r
            dxphi = y*dphi
            dx = sum2([dxr,dxphi])
            dyr = y *dr / r
            dyphi = x * dphi
            dy = sum2([dyr, dyphi])
          

           


            x = ("{:.%if}" % self.ndp).format(x)
            y = ("{:.%if}" % self.ndp).format(y)
            dx = ("{:.%if}" % self.ndp).format(dx)
            dy = ("{:.%if}" % self.ndp).format(dy)

            newParam = [param[0], param[1], x, dx, param[4], y, dy]    
        elif self.convertType=="polar":
            #print(param)
            x = float(param[2])
            dx = float(param[3])
            y = float(param[5])
            dy = float(param[6])
            #print(dy)

            r = R(x,y)
            phi=0
            if (x!=0):
                phi = abs(Phi(x,y)) % (2 * pi)
            else:
                if (y>0):
                    phi = pi/2 
                else:
                    phi = -pi/2
            
            if (x>0 and y > 0):
                phi = phi
            elif (x>0 and y<0):
                phi = -phi
            elif (x<0 and y>0):
                phi = pi - phi
            elif (x<0 and y<0):
                phi = -pi + phi
            
            dr = sum2([dx*x/r, dy*y/r])
            
            if (sin(phi)!=0):
                dphix = (dx/r)/abs(sin(phi))
                dphiy = (x*dr/r**2)/abs(sin(phi))
            else:
                dphix = (dy/r)/abs(cos(phi))
                dphiy = (y*dr/r**2)/abs(cos(phi))


            dphi = sum2([dphix,dphiy]) 



            
            
            if (self.angleType=="deg"):
                phi = degrees(phi)
                dphi = degrees(dphi)

            r = ("{:.%if}" % self.ndp).format(r)
            phi = ("{:.%if}" % self.ndp).format(phi)
            dr = ("{:.%if}" % self.ndp).format(dr)
            dphi = ("{:.%if}" % self.ndp).format(dphi)


            newParam = [param[0], param[1], r, dr, param[4], phi, dphi]    
        
        return newParam

    def convertAll(self):
        newParams=[]
        newParam=[]
        for params in self.allParams:
            newParam = self.convert(params)
            newParams.append(newParam)
            #print(newParam)
        
        self.allParams = newParams
    
    def writeOpt(self):

        f = open(self.target, "w")
        f.write(f"CouplingConstant::Coordinates {self.convertType}\n")
        f.write(f"CouplingConstant::AngularUnits {self.angleType}\n")
            
        for param in self.allParams:
            line = " ".join(param) + "\n"
            f.write(line)
        f.close()

    def printParam(self):
        for param  in self.allParams:
            print(" ".join(param))


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
 #   co.printParam()
    co.convertAll()
#    co.printParam()
    co.writeOpt()

if __name__=="__main__":
    main()