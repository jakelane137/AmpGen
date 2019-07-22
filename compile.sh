#!/usr/bin/env bash
set -euo pipefail
NCORES=$(ls /sys/class/cpuid | wc -l)
#source $PWD/setup.sh
INSTALL_DIR=$PWD/install
if [ -d $INSTALL_DIR ]
then
    echo "Directory already present"
    echo "Rebuild? (y/n)"
    read REBUILD
    if [ $REBUILD = "y" ]
    then
        echo "Installing ampGen to $INSTALL_DIR using $NCORES cores"  
        rm -rf $INSTALL_DIR
        mkdir -p $INSTALL_DIR
        cd $INSTALL_DIR
        cmake -DCMAKE_CXX_STANDARD=17 ..
        make -j$NCORES
        cd -
    else
        echo "Leaving install directory alone"
    fi

else
    echo "Installing ampGen to $INSTALL_DIR using $NCORES cores"
    mkdir -p $INSTALL_DIR
    cd $INSTALL_DIR
    cmake -DCMAKE_CXX_STANDARD=17 ..
    make -j$NCORES
    cd -
fi