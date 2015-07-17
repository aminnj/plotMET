{

  gROOT->ProcessLine(".L dataMCplotMaker.cc+");
  gROOT->ProcessLine(".L ScanChain.C+");
  // gSystem->Load("/home/users/namin/2015/met/dcscore/CORE/CMS3_CORE.so");
  // gROOT->ProcessLine(".L Software/MiniFWLite/libMiniFWLite.so");

  TChain *ch = new TChain("Events"); 
  // ch->Add("../../ntuple2.root");
  // ch->Add("../skim/150702.root");
  // ch->Add("../skim/anymetgt200.root");
  // ch->Add("/hadoop/cms/store/user/namin/userjob_test/Run2015B_ExpressPhysics_FEVT_Express-v1/merged/merged_ntuple_0.root");
  // ch->Add("./merged*.root");
  
  // ch->Add("/hadoop/cms/store/user/namin/userjob_test/Run2015B_ExpressPhysics_FEVT_Express-v1/merged/*.root");
  // ch->Add("/hadoop/cms/store/user/namin/userjob_test/Run2015B_ExpressPhysics_FEVT_Express-v1/merged/merged_ntuple_0.root");
  // ch->Add("/hadoop/cms/store/user/namin/userjob_test/Run2015B_ExpressPhysics_FEVT_Express-v1/merged/merged_ntuple_7.root");
  // ch->Add("/hadoop/cms/store/user/namin/userjob_test/Run2015B_MET_RECO_PromptReco-v1/*.root");

  // ch->Add("/hadoop/cms/store/user/namin/userjob_test/Run2015B_MET_RECO_PromptReco-v1/merged/merged_ntuple_0.root");


  // ch->Add("/hadoop/cms/store/user/namin/userjob_test/Run2015B_MET_RECO_PromptReco-v1/*.root");

  ch->Add("/hadoop/cms/store/user/namin/userjob_test/Run2015B_MET_RECO_PromptReco-v1/merged/*.root");
  // ch->Add("/hadoop/cms/store/user/namin/userjob_test/Run2015B_SingleMuon_RECO_PromptReco-v1/merged/*.root");
  // ch->Add("/hadoop/cms/store/user/namin/userjob_test/Run2015B_JetHT_RECO_PromptReco-v1/merged/*.root");

  ScanChain(ch); 
}
