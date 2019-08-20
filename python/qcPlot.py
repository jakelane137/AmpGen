import uproot, os, subprocess, argparse
import matplotlib as mpl
mpl.use('Agg')
from matplotlib import pyplot as plt
import numpy as np
mpi = 0.135729
mK=0.43890
mD=1.8353
def mij(pi, pj):
        return (pi[0] + pj[0])**2 - (pi[1] + pj[1])**2 - (pi[2] + pj[2])**2 - (pi[3] + pj[3])**2

def plot1D(obj, name, output):
    fig = plt.figure(figsize=(10, 10))
    nbins = int(len(obj)/100)
    n, bins, patches = plt.hist(obj, nbins)
    bw=bins[1]-bins[0]
    bw = '{0:.3f}'.format(bw)
    plt.xlabel(f"{name}")
    plt.ylabel(f"Entries/{bw} ($GeV^2/c^4$)")
    fig.savefig(f"{output}")
    plt.close()

def plot2D(obj1, obj2, obj3,  xname, yname, output, proj="XY"):
    fig = plt.figure(figsize=(10,10))
    nbins = int(len(obj1)/1000)
    b = bound(obj1, obj2, obj3)
    if proj=="XY" or proj=="YX":
        plt.plot(b[0], b[1])
        plt.hold()
        counts, xedges, yedges, im = plt.hist2d(obj1, obj2, nbins)
    elif proj=="YZ" or proj=="ZY": 
        plt.plot(b[1], b[2])
        plt.hold()
        counts, xedges, yedges, im = plt.hist2d(obj2, obj3, nbins)       
    elif proj=="ZX" or proj=="XZ":
        plt.plot(b[2], b[0])
        plt.hold()
        counts, xedges, yedges, im = plt.hist2d(obj3, obj1, nbins)       
    


    fig.colorbar(im)
    plt.xlabel(f"{xname}")
    plt.ylabel(f"{yname}")
    fig.savefig(f"{output}")
    plt.close()

def bound(obj1, obj2, obj3,N=10000, lim=0.01):
    X = np.linspace(min(obj1), max(obj1), N)
    Y = np.linspace(min(obj2), max(obj2), N)
    Z = np.linspace(min(obj3), max(obj3), N)
    Xp=[]
    Yp=[]
    Zp=[]
    for x in X:
        for y in Y:
            for z in Z:
                c = x+y+z - mD**2 - mK**2 - mpi**2 - mpi**2
                if abs(c)>lim:
                    Xp.append(x)
                    Yp.append(y)
                    Zp.append(z)
    return [Xp,Yp,Zp]
    
    
class qcPlot:
    def __init__(self, file, output, EventType):
        self.file = uproot.open(file)
        #print(self.file)
        self.tags = self.file.allkeys()
        self.output = output
        self.EventType = EventType

    def getP(self,tag, part):
        E = self.file[tag].array(f"{part}_E")
        PX = self.file[tag].array(f"{part}_PX")
        PY = self.file[tag].array(f"{part}_PY")
        PZ = self.file[tag].array(f"{part}_PZ")
        P = [E, PX, PY, PZ]
        return P
    def plot(self):
        for tag in self.file:
            tagName = tag.decode().split(";")
            tagName = tagName[0]
            #print(f"{self.output}/{tagName}")
            os.system(f"mkdir -p {self.output}/{tagName}/")
            EventType = self.EventType.replace("+", "p")
            EventType = EventType.replace("-", "m")
            #print(EventType)
            particles = EventType.split()[1:]
            p1 = self.getP(tag, particles[0])
            p2 = self.getP(tag, particles[1])
            p3 = self.getP(tag, particles[2])
            m12 = mij(p1, p2)
            m13 = mij(p1, p3)
            m23 = mij(p2, p3)
            plot1D(m12, "$m^2_{12}$", f"{self.output}/{tagName}/m12.png")
            plot1D(m13, "$m^2_{13}$", f"{self.output}/{tagName}/m13.png")
            plot1D(m23, "$m^2_{23}$", f"{self.output}/{tagName}/m23.png")
            plot2D(m12, m13, m23, "$m^2_{+}$", "$m^2_{-}$", f"{self.output}/{tagName}/m12_vs_m13.png")
            plot2D(m12, m13, m23, "$m^2_{+}$", "$m^2_{0}$", f"{self.output}/{tagName}/m12_vs_m23.png")
            plot2D(m12, m13, m23, "$m^2_{-}$", "$m^2_{0}$", f"{self.output}/{tagName}/m13_vs_m23.png")

    

        

        
def main():
    parser = argparse.ArgumentParser("Plotting utility for QcGenerator")
    parser.add_argument("file", metavar="file", nargs="?", type=str, default="ToyMC.root", help="input root file")
    parser.add_argument("--output", metavar="output", nargs="?", type=str, default="output", help="output directory")
    parser.add_argument("--EventType", metavar="EventType", nargs="?", type=str, default="D0 K0S0 pi- pi+", help="EventType (in ampGen format) default: D0 K0S0 pi+ pi-")
    args = parser.parse_args()
    q = qcPlot(args.file, args.output, args.EventType)
    q.plot()

if __name__=="__main__":
    main()
