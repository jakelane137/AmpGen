#!/usr/bin/python3
from ROOT import TGraph2D, TFile, TCanvas, gPad
import numpy as np
from matplotlib import pyplot as plt
from mpl_toolkits import mplot3d
import os, argparse
from ampplot import ampplot
from ampplot import set_palette

parser = argparse.ArgumentParser(description="ampGen difference script")
parser.add_argument("--nEvents", metavar="N", type=int, nargs='?', default=100, help="Number of events")
parser.add_argument("--name", metavar="name", type=str, nargs='?', default="all", help="Variable to plot, options are: s01, s02, s12, s01_vs_s02, s01_vs_s12, s02_vs_s12")
parser.add_argument("--draw1D", metavar="draw1D", type=str, nargs='?', default="C", help="Draw options for 1D plots")
parser.add_argument("--draw2D", metavar="draw2D", type=str, nargs='?', default="PCOL", help="Draw options for 2D plots")
parser.add_argument("opt1", metavar="opt1", type=str, nargs='?', default="belle", help="options ")
parser.add_argument("opt2", metavar="opt2", type=str, nargs='?', default="belle", help="options ")
parser.add_argument("--output", metavar="out", type=str, nargs='?', default="output", help="location for the output png ")
parser.add_argument("--output1", metavar="out1", type=str, nargs='?', default="output1", help="location for the output png ")
parser.add_argument("--output2", metavar="out2", type=str, nargs='?', default="output2", help="location for the output png ")
parser.add_argument("--imgtype", metavar="imgtype", type=str, nargs='?', default="eps", help="plot output picture type (eps) ")
parser.add_argument("--generate", action='store_true')
parser.add_argument("--QC", action='store_true')
parser.add_argument("--EventType1", metavar="EventType1", type=str, nargs='?', default="D0 K0S0 pi+ pi-")
parser.add_argument("--EventType2", metavar="EventType2", type=str, nargs='?', default="D0 K0S0 pi+ pi-")

args = parser.parse_args()
nEvents = args.nEvents
name = args.name
draw1D = args.draw1D
draw2D = args.draw2D
nEvents = args.nEvents
opt1 = args.opt1
opt2 = args.opt2
output = args.output
output1 = output + "/" + "1"
output1cc = output1+"CC"
output2 = output + "/" + "2"
output2cc = output2+"CC"
imgtype = args.imgtype
generate = args.generate
QC = args.QC
EventType1 = args.EventType1
EventType1CCarr = EventType1.split(" ")
EventType1CCarr[0] = "Dbar0"
EventType1CC = " ".join(EventType1CCarr)
EventType2 = args.EventType2
EventType2CCarr = EventType2.split(" ")
EventType2CCarr[0] = "Dbar0"
EventType2CC = " ".join(EventType2CCarr)
