{
  gROOT->ProcessLine(".L dataMCplotMaker.cc+");
  gROOT->ProcessLine(".L compare.C+");
  TChain *ch = new TChain("Events");
  // ch->Add("/hadoop/cms/store/user/namin/MinimumBias/crab_metjob2_MinBias2015A/150620_043825/0000/*.root");
  ch->Add("/hadoop/cms/store/user/namin/MinimumBias/crab_metjob2_MinBias2015A/150620_043825/0000/ntuple_*.root");
  // ch->Add("/hadoop/cms/store/user/namin/MinimumBias/crab_metjob2_MinBias2015A/150620_043825/0000/ntuple_100.root");
  // gROOT->ProcessLine("compare(\"/home/users/namin/2015/met/CMSSW_7_4_4_patch1/src/DataSleuth/DataSleuth/test/ntuple.root\")");
  // gROOT->ProcessLine("compare(\"/hadoop/cms/store/user/namin/MinimumBias/crab_metjob2_MinBias2015A/150620_043825/0000/ntuple_9.root\")");


  compare(ch);
}
