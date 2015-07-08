Draw more complex things via a looper. To create ScanChain, we do (with the appropriate filename modifications)
```
$ cd generate/
$ root
$ root [0] .L makeCMS3ClassFiles.C++
$ root [1] makeCMS3ClassFiles("../../ntuple.root", "Events")
```

This creates CMS3.{cc,h}, ScanChain.C, doAll.C. Copy these into scanner/ unless you already have a ScanChain.C 
(which I will be including in this repository).

