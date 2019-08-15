#!/bin/bash
  
f=${1%.*}
O=${f##*/}

#echo $O
toyfit --opt $1 --output $O "$@"

