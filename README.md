# plotMET
plotting stuff for MET study

# check out CORE:
git clone -b cmssw74x git@github.com:cmstas/CORE.git

# check out software:
git clone git@github.com:cmstas/Software.git

# check out tools:
git clone https://github.com/cmstas/Tools.git

# make CORE:
cd CORE/ && cmsenv && make -j10

# modify scanner/all.sh
cd scanner/
. all.sh
