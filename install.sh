### plotMET
# plotting stuff for MET study

cmsrel CMSSW_7_4_4_patch1
cd CMSSW_7_4_4_patch1
cmsenv
cd ..

git clone -b cmssw74x git@github.com:cmstas/CORE.git
git clone git@github.com:cmstas/Software.git
git clone https://github.com/cmstas/Tools.git

cd CORE/
make -j10
cd ..

# cd scanner/
# . all.sh
