{

  gROOT->ProcessLine(".L RunLumis.C+");
  TChain *ch = new TChain("Events"); 
  ch->Add("/hadoop/cms/store/user/namin/userjob_test/Run2015B_ExpressPhysics_FEVT_Express-v1/merged/*.root");

  RunLumis(ch); 
}
