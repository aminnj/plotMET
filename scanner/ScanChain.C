#include <iostream>
#include <vector>
#include "TBenchmark.h"
#include "TChain.h"
#include "TDirectory.h"
#include "TFile.h"
#include "TTreeCache.h"
#include "TROOT.h"
#include "TCanvas.h"

#include "CMS3.cc"
#include "dataMCplotMaker.h"

using namespace std;
using namespace tas;

int ScanChain( TChain* chain) {
    TH1F* null = new TH1F("","",1,0,1);

    // met
    std::vector<TH1F*> hists;
    std::vector<std::string> titles;
    titles.push_back("pfCaloMet");
    titles.push_back("caloMet");
    TH1F *h1D_pfCaloMet = new TH1F("h1D_pfCaloMet", "", 20,0,200);
    TH1F *h1D_caloMet = new TH1F("h1D_caloMet", "", 20,0,200);
    hists.push_back(h1D_pfCaloMet);
    hists.push_back(h1D_caloMet);

    unsigned int nEventsTotal = 0;
    unsigned int nEventsChain = chain->GetEntries();

    cms3.Init(chain);
    for( unsigned int event = 0; event < nEventsChain; ++event) {
        cms3.GetEntry(event);
        ++nEventsTotal;
        CMS3::progress( nEventsTotal, nEventsChain );

        h1D_pfCaloMet->Fill(pfCaloMet_met(), 2.0);
        h1D_caloMet->Fill(evt_met(), 2.0);

    }

    std::string common = "--noStack --drawDots --xAxisOverride [GeV] --type ";
    dataMCplotMaker(null, hists, titles, "", "", common+" --overrideHeader MET --outputName met.pdf");

    return 0;
}
