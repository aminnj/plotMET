Draw more complex things via a looper. To create ScanChain, we do (with the appropriate filename modifications)
```
$ cd generate/
$ root
$ root [0] .L makeCMS3ClassFiles.C++
$ root [1] makeCMS3ClassFiles("../../ntuple.root", "Events")
```


IGNORE THIS IGNORE THIS
This creates CMS3.{cc,h}, ScanChain.C, doAll.C. Copy these into scanner/ unless you already have a ScanChain.C 
(which I will be including in this repository).

Use the official makeCMS3ClassFiles in the cmstas/Software repository. There's an issue with looping over a chain directly.
Need to loop over files in the TChain or else there are memory issues (?).

