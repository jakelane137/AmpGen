import matplotlib as mpl
mpl.use('Agg')
from convertOpt import convertOpt
from ampplot import ampplot
from toyfit import toyFit
import numpy as np
from cmath import exp, phase, pi
from matplotlib import pyplot as plt
import os, argparse
class phaseExplore:
    def __init__(self, output ,  model, nEvents, T, n, dr, tau, name, EventType):
        self.output     = output

        self.model      = model
        self.nEvents    = nEvents
        self.T          = T
        self.n          = n
        self.dr         = dr
        self.tau        = tau
        self.EventType  = EventType
        self.D          = EventType.split()[0]
        self.params     = self.readOpts()
        

        self.resNames ={f"K0_892_p"  : f"{self.D}{{K*(892)+{{K0S0,pi+}},pi-}}",
                   f"K0_1410_p" : f"{self.D}{{K*(1410)+{{K0S0,pi+}},pi-}}",
                   f"K0_1430_p" : f"{self.D}{{K(0)*(1430)+[GLASS]{{K0S0,pi+}},pi-}}",
                   f"K2_1430_p" : f"{self.D}{{K(2)*(1430)+{{K0S0,pi+}},pi-}}",
                   f"K0_892_m"  : f"{self.D}{{K(0)*(892)bar-{{K0S0,pi+}},pi-}}",
                   f"K0_1410_m" : f"{self.D}{{K*(1410)bar-{{K0S0,pi+}},pi-}}",
                   f"K0_1680_m" : f"{self.D}{{K*(1680)bar-{{K0S0,pi+}},pi-}}",
                   f"K0_1430_m" : f"{self.D}{{K(0)*(1430)bar-[GLASS]{{K0S0,pi+}},pi-}}",
                   f"K2_1430_m" : f"{self.D}{{K(2)*(1430)bar-{{K0S0,pi+}},pi-}}",
                   f"rho_770"   : f"{self.D}{{K0S0,rho(770)0{{pi+,pi-}}}}",
                   f"rho_1450"  : f"{self.D}{{K0S0,rho(1450)0{{pi+,pi-}}}}",
                   f"omega_782" : f"{self.D}{{K0S0,omega(782)0{{pi+,pi-}}}}",
                   f"f2_1270"   : f"{self.D}{{K0S0,f(2)(1270)0{{pi+,pi-}}}}",
                    }
        self.name = name
        self.fullName = "all"
        if (self.name != "all"):
            self.fullName = self.resNames[self.name]
        print(f"{self.name} \n {self.params}")
      
    def getFName(self, name):
        _fName = ""
        for key in self.resNames:
            if self.resNames[key]==name:
                _fName = key
        return _fName

    def readOpts(self):
        _f          = open(self.model)
        _co         = convertOpt(self.model, "", "polar", "deg", "2")
        _params     = _co.getParams()
        return _params
    
    def getParam(self, name):
        _n = len(self.params["names"])
        _names  =   self.params["names"]
       # print(_names)
        _param = {}
        #print(name in _names)
        for i in range(_n):
            if name in _names[i]:
         #       print(f"{_names[i]}\n {self.params['real'][i]}")
                _param = {"real" : self.params["real"][i],
                      "imag" : self.params["imag"][i],
                      "abs"  : self.params["abs"][i],
                      "phase" : self.params["phase"][i],
                      "dreal" : self.params["dreal"][i],
                      "dimag" : self.params["dimag"][i],
                      "dabs"  : self.params["dabs"][i],
                      "dphase" : self.params["dphase"][i]
                      }
        return _param
    def makeOpt(self, name):
        _n      = len(self.params["names"])
        print(_n)
        _names  =   self.params["names"]
        _real   =   self.params["real"]
        _imag   =   self.params["imag"]
        _abs    =   self.params["abs"]
        _phase  =   self.params["phase"]
        _dreal   =   self.params["dreal"]
        _dimag   =   self.params["dimag"]
        _dabs    =   self.params["dabs"]
        _dphase  =   self.params["dphase"]

        _fix    =   self.params["fix"]
        string  =   f"""CouplingConstant::Coordinates \"cartesian\" 
                        CouplingConstant::AngularUnits \"rad\" 
                        Particle::DefaultModifier BL 
                        Particle::SpinFormalism Canonical 
                        Import $AMPGENROOT/options/kMatrix.opt 
                        Import $AMPGENROOT/kspipi/opts/LASS.opt 
                        Import $AMPGENROOT/kspipi/opts/particleProperties.opt\n
                        """
        #print(f"name = {name}")
        folder=name.split("/")
        #print(folder)
        folder=folder[:len(folder)-1]
        #print(folder)
        folder="/".join(folder)
        #print(f"{folder}")
        os.system(f"mkdir -p {folder}")
        os.system(f"rm {name}")
        _f = open(name, "a")
        _f.write(string)
        print(f"{type(_fix)}, {type(_imag)}")
        
        for i in range(_n):
            string = f"{_names[i]}_Re {_fix[i]} {_real[i]} {_dreal[i]} \n {_names[i]}_Im {_fix[i]} {_imag[i]} {_dimag[i]} \n"
            _f.write(string)
        _f.close()
        return name
    def makeParam(self, name, val):
        _n      = len(self.params["names"])
        _names  = self.params["names"]
        _real   = val.real
        _imag   = val.imag
        _abs    = abs(val)
        _phase    = phase(val)
        #print(f"name = {self.name}")
        #print(f"fullname = {self.resNames[self.name]}")
        for i in range(_n):
            if self.resNames[self.name] == _names[i]:
                #print(f"""real = {self.params['real']}\n
                #          imag = {self.params['imag']} \n
                #          abs = {self.params['abs']} \n
                 #         phase= {self.params['phase']} \n
                 #       """)
                self.params["real"][i]  = _real
                self.params["imag"][i]  = _imag
                self.params["abs"][i]   = _abs
                self.params["phase"][i] = _phase
                self.params["dreal"][i]  = round(abs(_real/100), 3)
                self.params["dimag"][i]  = round(abs(_imag/100), 3)
                self.params["dabs"][i]   = round(abs(_abs/100), 3)
                self.params["dphase"][i] = round(abs(_phase/100), 3)
                #print(f"""real = {self.params['real']}\n
                #          imag = {self.params['imag']} \n
                #          abs = {self.params['abs']} \n
                #          phase= {self.params['phase']} \n
                #        """)
        
    def makeOpts(self, name, path):
        i       =0
        _files  = []
        n       =len(path)
        for i in range(n):
            z = path[i]
            self.makeParam(name, z)
            #print(f"{self.name}, z = {z}")
            _files.append(self.makeOpt(f"{self.name}/opt_{i}.opt"))
        return _files



    def plot(self, optfile):
        _title  = optfile.split(".")
        _title  = f"{_title[len(_title) - 2]}/ampPlot/"
        _output = f"{_title}"
        ap = ampplot(self.nEvents, "all", "PCOLZ", "PCOLZ", self.model, _output, "png", True, self.EventType)
        ap.plot()

    def fit(self, optfile):
        _title  = optfile.split(".")
        _title  = f"{_title[len(_title) - 2]}/toyFit/"
        _output = f"{_title}"
#     def __init__(self, nEvents, name, draw1D, draw2D, opt, out, imgtype, generate, EventType, DataSample, IntegrationSample, mcMult, nCores):

        tf = toyFit(self.nEvents, self.name, "PCOLZ", "PCOLZ", self.model, _output, "png", True, self.EventType, f"{_title}/data.root" , f"{_title}/mc.root", 10, 10)
        #tf.fit()

    def explore(self):
        if self.fullName == "all":
            names = self.params["names"]
        else: 
            names = [self.resNames[self.name]]

        for name in names:
#            print(name)
            _initial = self.getParam(name)
 #           print(_initial)
            _abs    = float(_initial["abs"])
            _phase  = float(_initial["phase"])
            _real   = float(_initial["real"])
            _imag   = float(_initial["imag"])

            _z0 = _real + 1j * _imag
            self.plotPath(_z0)
            #print(f"n = {self.n} \n T = {self.T}")
            _t = np.linspace(-self.T, self.T, self.n)
            
            _path = list(map(lambda t: self.path(t, _z0), _t))
            #print(f"ts = {_t} \n z0 = {_z0} \n z1 = {self.path(0.4, _z0)} \n zs = {len(_path)}")
            
            _folder = self.getFName(name).split("/")[0]
            #print(f"{_folder}")
            os.system(f"mkdir -p {self.output}/{_folder}")
            _files = self.makeOpts(self.getFName(name), _path)
            for _file in _files:
                self.plot(_file)
                self.fit(_file)
    
    def path(self, t, z0):
        _tau    = self.tau
        _dr     = self.dr
        _r0     = abs(z0)
        _phase0 = phase(z0)
        #print(f"tau is {type(_tau)}\n dr is {type(_dr)}\n r0 is {type(_r0)} \n t is {type(t)}")
        _phase  = _phase0 + 2 * pi * t/_tau
        #print(int(t/_tau))
        _r      = _r0 + _dr * int(t/_tau)
        _z      = _r * exp(1j * _phase)
        return _z


    def plotPath(self, z0):

        _t0 = -self.T
        _tn = self.T
        _n  = self.n
        _t   = np.linspace(_t0, _tn, _n*_tn)
        _z = list(map(lambda t : self.path(t, z0), _t))
        _x = list(map(lambda z: z.real, _z))
        _y = list(map(lambda z: z.imag, _z))
        
        #print(f"plotting now \n {_x} \n {_y}")
        fig = plt.figure()
        plt.plot(_x, _y, 'c*')
        os.system(f"mkdir -p {self.output}")
        fig.savefig(f"{self.output}/path.png")





        
def main():
    parser = argparse.ArgumentParser(description="ampGen plotting script")
    parser.add_argument("--nEvents", metavar="nEvents", type=float, nargs='?', default=1000, help="Event type of form X a b c ")

    parser.add_argument("--T", metavar="T", type=float, nargs='?', default=10, help="Event type of form X a b c ")
    parser.add_argument("--n", metavar="n", type=float, nargs='?', default=100, help="Event type of form X a b c ")
    parser.add_argument("--tau", metavar="n", type=float, nargs='?', default=1, help="Event type of form X a b c ")
    parser.add_argument("--dr", metavar="n", type=float, nargs='?', default=1, help="Event type of form X a b c ")
    parser.add_argument("--output", metavar="n", type=str, nargs='?', default="output", help="Event type of form X a b c ")
    parser.add_argument("--model", metavar="n", type=str, nargs='?', default="opts/myBelle.opt", help="Event type of form X a b c ")
    parser.add_argument("--name", metavar="n", type=str, nargs='?', default="", help="Event type of form X a b c ")
    parser.add_argument("--EventType", metavar="n", type=str, nargs='?', default="D0 K0S0 pi+ pi-", help="Event type of form X a b c ")


    args = parser.parse_args()
    print("Starting phaseExplore")
    pe = phaseExplore(args.output, args.model, args.nEvents, args.T, args.n, args.dr, args.tau, args.name, args.EventType)
    print("Plotting path")

    pe.explore()
   

if __name__=='__main__':
    main()