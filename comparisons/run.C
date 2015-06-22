{
  gROOT->ProcessLine(".L dataMCplotMaker.cc+");
  gROOT->ProcessLine(".L compare.C+");
  TChain *ch = new TChain("Events");
  // ch->Add("/hadoop/cms/store/user/namin/MinimumBias/crab_metjob2_MinBias2015A/150620_043825/0000/ntuple_100.root");
  ch->Add("../skim/metgt100.root");
  compare(ch);
}
