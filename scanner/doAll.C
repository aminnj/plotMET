{
  gROOT->ProcessLine(".L dataMCplotMaker.cc+");
  gROOT->ProcessLine(".L ScanChain.C+");

  TChain *ch = new TChain("Events"); 

  ch->Add("/hadoop/cms/store/user/namin/userjob_test/Run2015B_MET_RECO_PromptReco-v1/merged/merged_ntuple_0.root");


  // ch->Add("/hadoop/cms/store/user/namin/userjob_test/Run2015B_MET_RECO_PromptReco-v1/*.root");

  // ch->Add("/hadoop/cms/store/user/namin/userjob_test/Run2015B_MET_RECO_PromptReco-v1/merged/*.root");
  // ch->Add("/hadoop/cms/store/user/namin/userjob_test/Run2015B_SingleMuon_RECO_PromptReco-v1/merged/*.root");
  // ch->Add("/hadoop/cms/store/user/namin/userjob_test/Run2015B_JetHT_RECO_PromptReco-v1/merged/*.root");

  ScanChain(ch); 
}
