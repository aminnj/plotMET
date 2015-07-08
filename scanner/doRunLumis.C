{

  gROOT->ProcessLine(".L RunLumis.C+");
  TChain *ch = new TChain("Events"); 
  ch->Add("merged_ntuple_*.root");

  RunLumis(ch); 
}
