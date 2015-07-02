{
    TChain *ch = new TChain("Events");
    // ch->Add("/hadoop/cms/store/user/namin/MinimumBias/crab_metjob2_MinBias2015A/150620_043825/0000/ntuple_*.root");
    ch->Add("/hadoop/cms/store/user/namin/MinimumBias/crab_metjob3_MinBias2015A/150701_221023/0000/ntuple_*.root");

    TFile *newfile = new TFile("150702.root","RECREATE");
    TTree *newtree = ch->CopyTree("evt_met>100");
    newfile->Write();
    newfile->Close();
}
