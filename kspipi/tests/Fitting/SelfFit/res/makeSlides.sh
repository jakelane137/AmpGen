#!/bin/bash
set -euo pipefail
cat slides.head > slides.tex
for i in opts/*
do
    f=${i%.*}
    O=${f##*/}
    for j in output/$O/D0/*.png
    do
        t=${j%.*}
        q=${j##*/}
        q=$(echo $q | cut -f 1 -d '.' | sed 's/_/ /g')
        cat << EOF >> slides.tex

\begin{frame}{$q for $(echo $O | sed 's/_/ /g')}
\begin{figure}
\includegraphics[width=0.75\linewidth]{$j}
\end{figure}
\end{frame}
EOF
done 
done
cat << EOF >> slides.tex
\end{document}
EOF
