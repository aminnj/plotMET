#!/bin/bash

if [ -z "$1" ]
then
    echo "Usage: ./getLumis.sh [lumis.json]"
    exit 1
fi


# up to date run lumi info
mkdir -p runcsv
rsync -rP --ignore-existing  lxplus.cern.ch:/afs/cern.ch/user/m/marlow/public/lcr2/runcsv/ runcsv

python lcr2.py -i $1
