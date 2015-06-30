{

  gROOT->ProcessLine(".L ScanChain.C+");

  TChain *ch = new TChain("Events"); 
  ch->Add("../../../ntuple.root");
  ScanChain(ch); 
}