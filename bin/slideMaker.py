import os, argparse, subprocess
from glob import glob
class slideMaker:
    def __init__(self, _input, _output):
        self.input = _input
        self.output = _output

    def makeSlides(self):
        _head = f"{os.environ['AMPGENROOT']}/kspipi/tests/Fitting/SelfFit/slides.head"
        os.system(f"cat {_head} > {self.output}")
        folders = glob(f"{self.input}/*/D0/")
        for folder in folders:
            self.makeFrame(folder)
            print(folder)


        _output = open(self.output, "a")
        _output.write("\\end{document}")

    def makeFrame(self, folder):
        GeVc2 = "GeV ^{2}/#it{c} ^{4}"
        kspip = "\MP"
        kspim = "\MM"
        pippim = "\MZ"
        names = {"s01"  : f"{kspip}",
                "s02"  : f"{kspim}",
                "s12"  : f"{pippim}",
                "s01_vs_s02"  : f"{kspip} vs {kspim}",
                "s01_vs_s12"  : f"{kspip} vs {pippim}", 
                "s02_vs_s12"  : f"{kspim} vs {pippim}" 
                }

        titles = {"D0_PiPi00" : "$\\pi^+ \\pi^-$ S-wave",
               "f2_1270" : "$f_2(1270)^0$",
               "K0_892m" :  "$K_0^*(892)^-$",
               "K0_1410m" :  "$K_0^*(1410)^-$",
               "K0_1430m" :  "$K_0^*(1430)^-$",
               "K2_1430m" :  "$K_2^*(1430)^-$",
               "K0_1680m" :  "$K_0^*(1680)^-$",
               "K0_892p" :  "$K_0^*(892)^+$",
               "K0_1410p" :  "$K_0^*(1410)^+$",
               "K0_1430p" :  "$K_0^*(1430)^+$",
               "K2_1430p" :  "$K_2^*(1430)^+$",
               "rho_770"  : "$\\rho(770)^0$",
               "rho_1450"  : "$\\rho(1450)^0$",
               "omega_782" : "$\\omega(782)^0$",
               "timBelle"  : "Belle\ Model\ (Tim)",
               "myBelle"   : "My\ Belle\ Model",
               "timBellePol" : "Tim's\ Belle\ Model\ \(in\ Polar\)",
               "myBellePol" : "My\ Belle\ Model\ \(in\ Polar\)"

               }
        print(titles["myBelle"])

        #folders = os.system(f"ls {self.input}*/").split()
        folders = glob(f"{folder}/*/") 
        #print(folders)
        _plots = ["s01", "s02", "s12"]#",s01_vs_s02", "s01_vs_s12", "s02_vs_s12"]
        _2dplots = ["s01_vs_s02", "s01_vs_s12", "s02_vs_s12"]

        _output = open(self.output, "a")

        folderNameArr = folder.split('/')
        folderName = folderNameArr[1]
        #print(folderName)
        for plot in _plots:
            _figure = f"""
\\begin{{frame}}{{{names[plot]} for {titles[folderName]}}}
\\begin{{columns}}[t]
\\column{{{.5}\\textwidth}}
\\centering
\\includegraphics[width=.7\\linewidth]{{{folder}/regenerated/{plot}.png}}
\\column{{{.5}\\textwidth}}
\\centering
\\includegraphics[width=.7\\linewidth]{{{folder}/fitted/{plot}.png}}
\\end{{columns}}
    \\centering
    Left ``Regenerated Model'', right ``Original Model (with fit line)''
\\end{{frame}}                   
"""
           # print(_figure)
            _output.write(_figure)

        for plot in _2dplots:

            _frame=f"""

\\begin{{frame}}{{{names[plot]} for {titles[folderName]}}}
\\begin{{columns}}[t]
\\column{{{.5}\\textwidth}}
\\centering
\\includegraphics[width=.7\\linewidth]{{{folder}/regenerated/{plot}.png}}
\\column{{{.5}\\textwidth}}
\\centering
\\includegraphics[width=.7\\linewidth]{{{folder}/initial/{plot}.png}}
\\end{{columns}}
    \\centering
    Left ``Regenerated'', right ``Original''
\\end{{frame}} 
"""
#            print(_frame)
            _output.write(_frame)
 #       print("\\end{document}")
      #  _output.write("\\end{document}")

def main():

    parser = argparse.ArgumentParser(description="ampGen plotting script")
    parser.add_argument("--output", metavar="output", type=str, nargs='?', default="slides.tex", help="location for the output png ")
    parser.add_argument("--input", metavar="input", type=str, nargs='?', default="", help="options ")
    args = parser.parse_args()
    _input = args.input
    _output = args.output
    ms = slideMaker(_input, _output)
    ms.makeSlides()

if __name__=="__main__" : 
    main()