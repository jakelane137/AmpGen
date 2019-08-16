#!/usr/bin/env python3
from ampGen import ampGen
import os, argparse, subprocess
def main():
    nEvents =10000
    EventType = "D0 K0S0 pi+ pi-"
    apps = ["Generator"]
    output = "output"
    model = "belle.opt"
    install=os.environ['AMPGENROOT']
    for app in apps:
        gen = ampGen(app, nEvents, EventType, model, output, install)
        gen.run()
        cmd=f"python3 plot.py --EventType \"{EventType}\"  --output {output} {output}/Generated.root"
        os.system(cmd)


if __name__=="__main__":
    main()
