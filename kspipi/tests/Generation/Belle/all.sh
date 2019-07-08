#!/bin/bash
N=${1:-10000}
rm slides.tex
cat << EOF >> slides.tex
\pdfminorversion=7
\DeclareUnicodeCharacter{2212}{-}
\documentclass{beamer}
\usepackage[utf8]{inputenc}
\usepackage{siunitx}
\usepackage{amsmath}
\usepackage{slashed}
\usepackage{fancyvrb}
\usepackage{epstopdf}
\usepackage{xcolor}
\hypersetup{
    colorlinks=true,
    linkcolor=blue,
    filecolor=magenta,      
    urlcolor=cyan,
}
\usetheme{boxes}
\newcommand{\ks}{\ensuremath{K_S^0}}
\newcommand{\strphdiff}{\ensuremath{\Delta \delta_D}}
\newcommand{\kspipi}[1]{\ensuremath{#1 \to \ks \pi^+ \pi^-}}
\newcommand{\diffDtokspipi}{\ensuremath{\kspipi{D^0}} \text{and} \ensuremath{\kspipi{\bar{D}^0}} }
\newcommand{\MP}{\ensuremath{m^2_+}}
\newcommand{\MM}{\ensuremath{m^2_-}}
\newcommand{\MZ}{\ensuremath{m^2_0}}
\newcommand{\phasePosition}{\ensuremath{m^2_+,m^2_-}}
\newcommand{\phasePositionT}{\ensuremath{m^2_-,m^2_+}}
\newcommand{\Dzbar}{\ensuremath{\bar{D}^0} }
\newcommand{\Dz}{\ensuremath{D^0} }
\newcommand{\Bzbar}{\ensuremath{\bar{B}^0} }
\newcommand{\Bz}{\ensuremath{B^0} }
%These macros are save time, usage
%\subAmp{particle}{component} -e.g \subAmp{\Dz}{L_{\pi^+\pi^-}=0}
\newcommand{\subAmp}[2]{\ensuremath{A_{#1}^{#2}\left(\phasePosition \right)}}
%\modelAmp{particle}{model name} - e.g. \modelAmp{\Dz}{Belle}
\newcommand{\modelAmp}[2]{\ensuremath{A_{#1}^{\text{#2}}\left(\phasePosition \right)}}
\newcommand{\genAmp}[2]{\ensuremath{A_{#1}^{\text{#2}}\left(\mathcal{P} \right)}}
%Generic input amp (actually you could use \modelAmp instead if you want
\newcommand{\inputAmp}[1]{\ensuremath{A_{#1}^{\text{input}}\left(\phasePosition\right)}}
%True model - what the decay really is
\newcommand{\trueAmp}[1]{\ensuremath{A_{#1}^{\text{True}}\left(\phasePosition\right)}}
%a_r and phi_r, again saves writing $, _, ^ everywhere
\newcommand{\magPar}[1]{\ensuremath{a_{#1}}}
\newcommand{\phPar}[1]{\ensuremath{\phi_{#1}}}
\author{Jake Lane}
\title{Implementation of the Belle Model for \diffDtokspipi decay in ampGen}
\begin{document}
\begin{frame}{}
    \maketitle
\end{frame}
EOF
for i in opts/*.opt
do
    f=${i%.*}
    O=${f##*/}


    A=$(echo $O | sed "s/\_/ /g")
   
   
    
    
    #echo $O
    echo \"$i\"
    echo $A
   #diff.py --generate --output $O --opt1 $i --nEvents $N
   cat << EOF >> slides.tex
\begin{frame}{$A}
\begin{tiny}
\VerbatimInput{$i}
\end{tiny}
\end{frame}
\begin{frame}{$A}
\begin{figure}
\includegraphics[width=.8\linewidth]{$O/Delta_gAbs.eps}
\caption{\$\left|\frac{\genAmp{\Dz}{}}{\genAmp{\Dz}{}}\right|\$ for $A}
\end{figure}
\end{frame}
\begin{frame}{$A}
\begin{figure}
\includegraphics[width=.8\linewidth]{$O/Delta_gArg.eps}
\caption{\strphdiff for $A}
\end{figure}
\end{frame}
\begin{frame}{$A}
\begin{figure}
\includegraphics[width=.8\linewidth]{$O/1D0/gArg.eps}
\caption{Argument for $A}
\end{figure}
\end{frame}
\begin{frame}{$A}
\begin{figure}
\includegraphics[width=.8\linewidth]{$O/1D0/gAbs.eps}
\caption{Magnitude for $A}
\end{figure}
\end{frame}
\begin{frame}{$A}
\begin{figure}
\includegraphics[width=.8\linewidth]{$O/1D0/s01.eps}
\caption{\MP for $A}
\end{figure}
\end{frame}
\begin{frame}{$A}
\begin{figure}
\includegraphics[width=.8\linewidth]{$O/1D0/s02.eps}
\caption{\MM for $A}
\end{figure}
\end{frame}
\begin{frame}{$A}
\begin{figure}
\includegraphics[width=.8\linewidth]{$O/1D0/s12.eps}
\caption{\MZ for $A}
\end{figure}
\end{frame}
\begin{frame}{$A}
\begin{figure}
\includegraphics[width=.8\linewidth]{$O/1D0/s01_vs_s02.eps}
\caption{\MP vs \MM for $A}
\end{figure}
\end{frame}
\begin{frame}{$A}
\begin{figure}
\includegraphics[width=.8\linewidth]{$O/1D0/s01_vs_s12.eps}
\caption{\MP vs \MZ for $A}
\end{figure}
\end{frame}
\begin{frame}{$A}
\begin{figure}
\includegraphics[width=.8\linewidth]{$O/1D0/s02_vs_s12.eps}
\caption{\MP vs \MZ for $A}
\end{figure}
\end{frame}

\begin{frame}{$A}
\begin{figure}
\includegraphics[width=.8\linewidth]{$O/1CCDbar0/gArg.eps}
\caption{Argument for $A}
\end{figure}
\end{frame}
\begin{frame}{$A}
\begin{figure}
\includegraphics[width=.8\linewidth]{$O/1CCDbar0/gAbs.eps}
\caption{Magnitude for $A}
\end{figure}
\end{frame}
\begin{frame}{$A}
\begin{figure}
\includegraphics[width=.8\linewidth]{$O/1CCDbar0/s01.eps}
\caption{\MP for $A}
\end{figure}
\end{frame}
\begin{frame}{$A}
\begin{figure}
\includegraphics[width=.8\linewidth]{$O/1CCDbar0/s02.eps}
\caption{\MM for $A}
\end{figure}
\end{frame}
\begin{frame}{$A}
\begin{figure}
\includegraphics[width=.8\linewidth]{$O/1CCDbar0/s12.eps}
\caption{\MZ for $A}
\end{figure}
\end{frame}
\begin{frame}{$A}
\begin{figure}
\includegraphics[width=.8\linewidth]{$O/1CCDbar0/s01_vs_s02.eps}
\caption{\MP vs \MM for $A}
\end{figure}
\end{frame}
\begin{frame}{$A}
\begin{figure}
\includegraphics[width=.8\linewidth]{$O/1CCDbar0/s01_vs_s12.eps}
\caption{\MP vs \MZ for $A}
\end{figure}
\end{frame}
\begin{frame}{$A}
\begin{figure}
\includegraphics[width=.8\linewidth]{$O/1CCDbar0/s02_vs_s12.eps}
\caption{\MP vs \MZ for $A}
\end{figure}
\end{frame}


EOF

done
cat << EOF >> slides.tex
\begin{frame}{To Do}
\begin{itemize}
\item Cartesian times Fit Fraction
\item Convert any model (Belle, BaBar) to Re,Im (use excel?)
\item Fitting is also done in Re-Im, it might be an ampGen error?
\end{itemize}
\end{frame}
\end{document}
EOF

