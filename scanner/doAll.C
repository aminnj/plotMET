{

  gROOT->ProcessLine(".L dataMCplotMaker.cc+");
  gROOT->ProcessLine(".L ScanChain.C+");
  gROOT->ProcessLine(".L Software/MiniFWLite/libMiniFWLite.so");

  TChain *ch = new TChain("Events"); 
  // ch->Add("../../ntuple2.root");
  // ch->Add("../skim/150702.root");
  // ch->Add("../skim/anymetgt200.root");
  // ch->Add("/hadoop/cms/store/user/namin/userjob_test/Run2015B_ExpressPhysics_FEVT_Express-v1/merged/merged_ntuple_0.root");
  // ch->Add("./merged*.root");
  
  // ch->Add("merged_ntuple_*.root");
  ch->Add("/hadoop/cms/store/user/namin/userjob_test/Run2015B_ExpressPhysics_FEVT_Express-v1/merged/*.root");

  ScanChain(ch); 
}
