import uproot, os, argparse, decimal
import numpy as np
from matplotlib import pyplot as plt


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

def plot2D(obj1, obj2, xname, yname, output):
    fig = plt.figure(figsize=(10,10))
    nbins = int(len(obj1)/100)
    counts, xedges, yedges, im = plt.hist2d(obj1, obj2, nbins)
    plt.colorbar(im)
    plt.xlabel(f"{xname}")
    plt.ylabel(f"{yname}")
    fig.savefig(f"{output}")
    plt.close()


def plots(file, EventType, output):
    f = uproot.open(file)
    events = f["DalitzEventList"]
    EventType=EventType.replace("+","~")
    EventType=EventType.replace("-","#")
    
    parts = EventType.split()
    params = ["E", "Px", "Py", "Pz"]

    p1 = []
    p2 = []
    p3 = []

    p = {parts[1]: p1, parts[2]:p2, parts[3]:p3}

    for i in range(1, len(parts)):
        for param in params:
            #print(f"_{i}_{parts[i]}_{param}")
            p[parts[i]].append(events.array(f"_{i}_{parts[i]}_{param}"))
    m1  = np.sqrt(mij(p1, p1))/2.
    m2  = np.sqrt(mij(p2, p2))/2.
    m3  = np.sqrt(mij(p3, p3))/2.



    m12 = mij(p1, p2)
    m13 = mij(p1, p3)
    m23 = mij(p2, p3)
    objs = {"m12":m12, "m13":m13, "m23":m23}
    names= {"m12":"$m^2_{12} (GeV^2/c^4)$", "m13":"$m^2_{13} (GeV^2/c^4)$", "m23":"$m^2_{23}(GeV^2/c^4)$"}

    for key1 in objs:
        for key2 in objs:
            if key1!=key2:
                plot2D(objs[key1], objs[key2], f"{names[key1]}",f"{names[key2]}", f"{output}/{key1}_vs_{key2}.png")

    for key in objs:
        plot1D(objs[key], names[key], f"{output}/{key}.png")

def main():
    parser = argparse.ArgumentParser("Plotting tool to plot ampGen files as pngs")
    parser.add_argument("file", metavar="file", type=str, nargs="?",default="output/Generated.root", help="location of input root file")
    parser.add_argument("--output", metavar="output", type=str, nargs="?", default="output", help="Output location")
    parser.add_argument("--EventType", metavar="EventType", type=str, nargs="?", default="D0 K0S0 pi+ pi-", help="Decay type")
    args = parser.parse_args()
    plots(args.file, args.EventType, args.output)
    print(f"Made plots in {args.output}")

if __name__=="__main__":
    main()
