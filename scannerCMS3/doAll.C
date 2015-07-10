{

  gROOT->ProcessLine(".L ../Software/dataMCplotMaker/dataMCplotMaker.cc+");
  // gROOT->ProcessLine(".L CMS3.cc+");
  gSystem->Load("../CORE/CMS3_CORE.so");
  // gROOT->ProcessLine(".L ../Software/MiniFWLite/libMiniFWLite.so");

  gROOT->ProcessLine(".L ScanChain.C+");

  TChain *ch = new TChain("Events"); 

  ch->Add("MET.root");

  ScanChain(ch); 
}
