#!/usr/bin/env bash
set -euo pipefail

if [ -z $AMPGENROOT ]
then
	echo "Can't find AmpGen installation - the AMPGENROOT variable is not set. Is ampGen installed?"
else
#	$AMPGENROOT/install/bin/QcGenerator --Output $AMPGENROOT/data/kspipi.root $AMPGENROOT/options/belleQC.opt
	python3 $AMPGENROOT/python/qcPlot.py --output $AMPGENROOT/data $AMPGENROOT/data/kspipi.root
fi

