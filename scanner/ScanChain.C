#pragma GCC diagnostic ignored "-Wsign-compare"
#include <iostream>
#include <vector>
#include "TBenchmark.h"
#include "TChain.h"
#include "TDirectory.h"
#include "TFile.h"
#include "TTreeCache.h"
#include "TROOT.h"
#include "TCanvas.h"
#include "TH2.h"
#include "utils.C"

#include "CMS3.cc"
#include "dataMCplotMaker.h"

using namespace std;
using namespace tas;

int ScanChain( TChain* chain) {
    TH1F* null = new TH1F("","",1,0,1);

    // comparison of METs
    std::vector<std::string> titlesMet;
    titlesMet.push_back("pfCaloMet");
    titlesMet.push_back("pfMet");
    titlesMet.push_back("caloMet");

    std::vector<TH1F*> h1D_met_vec;
    TH1F *h1D_pfCaloMet = new TH1F("h1D_pfCaloMet", "", 20,0,200);
    TH1F *h1D_pfMet = new TH1F("h1D_pfMet", "", 20,0,200);
    TH1F *h1D_caloMet = new TH1F("h1D_caloMet", "", 20,0,200);
    h1D_met_vec.push_back(h1D_pfCaloMet);
    h1D_met_vec.push_back(h1D_pfMet);
    h1D_met_vec.push_back(h1D_caloMet);

    // 2d plots of met
    TH2F* h2D_pfCaloMet_pfMet = new TH2F("h2D_pfCaloMet_pfMet","", 20,0,200, 20,0,200);
    TH2F* h2D_pfCaloMet_caloMet = new TH2F("h2D_pfCaloMet_caloMet","", 20,0,200, 20,0,200);
    TH2F* h2D_caloMet_pfMet = new TH2F("h2D_caloMet_pfMet","", 20,0,200, 20,0,200);

    // filters
    std::vector<std::string> titlesFilters;
    titlesFilters.push_back(" NO filter");
    titlesFilters.push_back("+cscTightHalo");
    titlesFilters.push_back("+hcalNoise");
    titlesFilters.push_back("+hbheRun2Tight");

    // caloMet with filters layered
    std::vector<TH1F*> h1D_caloMet_filters_vec;
    TH1F *h1D_caloMet_halo = new TH1F("h1D_caloMet_halo", "", 20,0,200);
    TH1F *h1D_caloMet_halonoise = new TH1F("h1D_caloMet_halonoise", "", 20,0,200);
    TH1F *h1D_caloMet_halonoisehbhe = new TH1F("h1D_caloMet_halonoisehbhe", "", 20,0,200);
    h1D_caloMet_filters_vec.push_back(h1D_caloMet);
    h1D_caloMet_filters_vec.push_back(h1D_caloMet_halo);
    h1D_caloMet_filters_vec.push_back(h1D_caloMet_halonoise);
    h1D_caloMet_filters_vec.push_back(h1D_caloMet_halonoisehbhe);

    // pfCaloMet with filters layered
    std::vector<TH1F*> h1D_pfCaloMet_filters_vec;
    TH1F *h1D_pfCaloMet_halo = new TH1F("h1D_pfCaloMet_halo", "", 20,0,200);
    TH1F *h1D_pfCaloMet_halonoise = new TH1F("h1D_pfCaloMet_halonoise", "", 20,0,200);
    TH1F *h1D_pfCaloMet_halonoisehbhe = new TH1F("h1D_pfCaloMet_halonoisehbhe", "", 20,0,200);
    h1D_pfCaloMet_filters_vec.push_back(h1D_pfCaloMet);
    h1D_pfCaloMet_filters_vec.push_back(h1D_pfCaloMet_halo);
    h1D_pfCaloMet_filters_vec.push_back(h1D_pfCaloMet_halonoise);
    h1D_pfCaloMet_filters_vec.push_back(h1D_pfCaloMet_halonoisehbhe);

    // dPhi(leading jet,caloMet)
    std::vector<TH1F*> h1D_jetCaloMetPhi_filters_vec;
    TH1F *h1D_jetCaloMetPhi               = new TH1F("h1D_jetCaloMetPhi", "",               30,0,8.3);
    TH1F *h1D_jetCaloMetPhi_halo          = new TH1F("h1D_jetCaloMetPhi_halo", "",          30,0,8.3);
    TH1F *h1D_jetCaloMetPhi_halonoise     = new TH1F("h1D_jetCaloMetPhi_halonoise", "",     30,0,8.3);
    TH1F *h1D_jetCaloMetPhi_halonoisehbhe = new TH1F("h1D_jetCaloMetPhi_halonoisehbhe", "", 30,0,8.3);
    h1D_jetCaloMetPhi_filters_vec.push_back(h1D_jetCaloMetPhi);
    h1D_jetCaloMetPhi_filters_vec.push_back(h1D_jetCaloMetPhi_halo);
    h1D_jetCaloMetPhi_filters_vec.push_back(h1D_jetCaloMetPhi_halonoise);
    h1D_jetCaloMetPhi_filters_vec.push_back(h1D_jetCaloMetPhi_halonoisehbhe);

    unsigned int nEventsTotal = 0;
    unsigned int nEventsChain = chain->GetEntries();

    std::cout << "Running over " << nEventsChain << " events." << std::endl;

    cms3.Init(chain);
    for( unsigned int event = 0; event < nEventsChain; ++event) {
        cms3.GetEntry(event);
        ++nEventsTotal;
        CMS3::progress( nEventsTotal, nEventsChain );

        h1D_pfCaloMet->Fill(pfCaloMet_met());
        h1D_pfMet->Fill(pfMet_met());
        h1D_caloMet->Fill(evt_met());

        float leadingJetPhi = 999.0;
        float leadingJetPt = -999.0;
        for(int iJet = 0; iJet < calojets_pt().size(); iJet++) {
            if (calojets_pt().at(iJet) > leadingJetPt) {
                leadingJetPt = calojets_pt().at(iJet);
                leadingJetPhi = calojets_phi().at(iJet);
            }
        }

        float dPhiCaloMet = deltaPhi(leadingJetPhi, evt_metPhi());

        if(dPhiCaloMet < M_PI) h1D_jetCaloMetPhi->Fill(dPhiCaloMet);
        // h1D_jetCaloMetPhi->Fill(leadingJetPhi+M_PI);

        h2D_pfCaloMet_pfMet->Fill(pfCaloMet_met(), pfMet_met());
        h2D_pfCaloMet_caloMet->Fill(pfCaloMet_met(), evt_met());
        h2D_caloMet_pfMet->Fill(evt_met(), pfMet_met());


        if ( !evt_cscTightHaloFilter() ) continue; // XXX

        h1D_pfCaloMet_halo->Fill(pfCaloMet_met());
        h1D_pfMet->Fill(pfMet_met());
        h1D_caloMet_halo->Fill(evt_met());
        if(dPhiCaloMet < M_PI) h1D_jetCaloMetPhi_halo->Fill(dPhiCaloMet);

        if (  hcalnoise_HasBadRBXTS4TS5() ) continue; // XXX

        h1D_pfCaloMet_halonoise->Fill(pfCaloMet_met());
        h1D_pfMet->Fill(pfMet_met());
        h1D_caloMet_halonoise->Fill(evt_met());
        if(dPhiCaloMet < M_PI) h1D_jetCaloMetPhi_halonoise->Fill(dPhiCaloMet);

        if ( !evt_hbheFilterRun2Tight() ) continue; // XXX

        h1D_pfCaloMet_halonoisehbhe->Fill(pfCaloMet_met());
        h1D_pfMet->Fill(pfMet_met());
        h1D_caloMet_halonoisehbhe->Fill(evt_met());
        if(dPhiCaloMet < M_PI) h1D_jetCaloMetPhi_halonoisehbhe->Fill(dPhiCaloMet);

    }

    std::string common = "--noStack --noFill --drawDots --xAxisOverride [GeV] --type --preserveBackgroundOrder --legendTextSize 0.03 --legendRight -0.05";
    dataMCplotMaker(null, h1D_met_vec, titlesMet, "", "", common+" --overrideHeader MET --outputName h1D_met.pdf");
    dataMCplotMaker(null, h1D_caloMet_filters_vec, titlesFilters, "", "", common+" --overrideHeader caloMet (cumulative filters) --outputName h1D_caloMet_filters.pdf");
    dataMCplotMaker(null, h1D_pfCaloMet_filters_vec, titlesFilters, "", "", common+" --overrideHeader pfCaloMet (cumulative filters) --outputName h1D_pfCaloMet_filters.pdf");
    dataMCplotMaker(null, h1D_jetCaloMetPhi_filters_vec, titlesFilters, "", "", common+"  --overrideHeader #Delta#phi(j,caloMet) (cumulative filters) --outputName h1D_jetCaloMetPhi_filters.pdf");


    drawHist2D(h2D_pfCaloMet_pfMet,"h2D_pfCaloMet_pfMet.pdf",    "--logscale --title pfCaloMet vs pfMet --xlabel pfCaloMet_met --ylabel pfMet_met");
    drawHist2D(h2D_pfCaloMet_caloMet,"h2D_pfCaloMet_caloMet.pdf","--logscale --xlabel pfCaloMet vs caloMet --xlabel pfCaloMet_met --ylabel caloMet");
    drawHist2D(h2D_caloMet_pfMet,"h2D_caloMet_pfMet.pdf","--logscale --xlabel caloMet vs pfMet --xlabel  caloMet --ylabel pfMet");





    return 0;
}
