#!/bin/bash
N=${1:-10000}
opt=${2:-"opts/babar.opt"}  
f=${opt%.*}
O=${f##*/}
#echo $O
diff.py --generate --output $O --nEvents $N $f $f
