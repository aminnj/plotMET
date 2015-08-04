#pragma GCC diagnostic ignored "-Wsign-compare"
#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <stdlib.h>
#include <map>
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
#include "../Tools/goodrun.cc"

using namespace std;
using namespace tas;

std::map<int, int> runToBinMap; // map run to bin in histogram
std::map<int, int> binToRunMap; // map bin to run in histogram
int iRunBin = 0;
void addRunToMap(int run) {
    if(runToBinMap.find(run) == runToBinMap.end() ) {
        runToBinMap[run] = iRunBin;
        binToRunMap[iRunBin] = run;
        iRunBin++;
        cout << "added new run " << run << " to bin " << iRunBin << endl;
    }
}

struct Tower {
    std::vector<float> eta, phi, emEnergy, hadEnergy, outerEnergy;
    int detid; //twrs_detid-1375730000
};
std::map<int, Tower> detToTower;

bool haveFunctionalDCS() {
    // defined in https://cmssdt.cern.ch/SDT/doxygen/CMSSW_6_1_1/doc/html/d1/d05/DcsStatus_8h_source.html#l00084. Ignore CASTOR and ZDC.
    std::vector<int> detectors = { 0, 1, 2, 3, 5, 6, 7, 8, 9, 12, 13, 14, 15, 16, 17, 24, 25, 26, 27, 28, 29, 30, 31 };
    for(unsigned int iDet = 0; iDet < detectors.size(); iDet++) {
        if( ! ( evt_detectorStatus() & (1 << detectors[iDet]  ) ) ) return false;
    }
    return true;
}
bool hbheIsoNoiseFilter() {
    if( hcalnoise_numIsolatedNoiseChannels() >=10 ) return false;
    if( hcalnoise_isolatedNoiseSumE() >=50        ) return false;
    if( hcalnoise_isolatedNoiseSumEt() >=25       ) return false;
    return true;
}
bool hbheNoiseFilter() {
    if(hcalnoise_minE2Over10TS()<-999.0) return false;
    if(hcalnoise_maxE2Over10TS()>999.0) return false;
    if(hcalnoise_maxRBXHits()>=999) return false;
    if(hcalnoise_min25GeVHitTime()<-9999.0) return false;
    if(hcalnoise_max25GeVHitTime()>9999.0) return false;
    if(hcalnoise_minRBXEMF()<-999.0) return false;
    if(hcalnoise_maxHPDHits()>=17) return false;
    if(hcalnoise_maxHPDNoOtherHits()>=10) return false;
    if(hcalnoise_numIsolatedNoiseChannels()>=10) return false;
    if(hcalnoise_isolatedNoiseSumE()>=50.0) return false;
    if(hcalnoise_isolatedNoiseSumEt()>=25.0) return false;
    return true;
}

bool passesLoosePFJetID(int pfJetIdx) {
    float pfjet_chf_  = pfjets_chargedHadronE()[pfJetIdx] / (pfjets_undoJEC().at(pfJetIdx)*pfjets_p4()[pfJetIdx].energy());
    float pfjet_nhf_  = pfjets_neutralHadronE()[pfJetIdx] / (pfjets_undoJEC().at(pfJetIdx)*pfjets_p4()[pfJetIdx].energy());
    float pfjet_cef_  = pfjets_chargedEmE()[pfJetIdx] / (pfjets_undoJEC().at(pfJetIdx)*pfjets_p4()[pfJetIdx].energy());
    float pfjet_nef_  = pfjets_neutralEmE()[pfJetIdx] / (pfjets_undoJEC().at(pfJetIdx)*pfjets_p4()[pfJetIdx].energy());
    int   pfjet_cm_  = pfjets_chargedMultiplicity()[pfJetIdx];
    float pfjet_eta  = fabs(pfjets_p4()[pfJetIdx].eta());

    if (pfjets_pfcandIndicies()[pfJetIdx].size() < 2) return false;
    if (pfjet_nef_ >= 0.99) return false;
    if (pfjet_nhf_ >= 0.99) return false;

    if (pfjet_eta < 2.4){
        if (pfjet_cm_ < 1) return false;
        if (pfjet_chf_ < 1e-6) return false;
        if (pfjet_cef_ >= 0.99) return false;
    }

    return true;
}

int ScanChain( TChain* chain) {
    ofstream runLumiOutput;
    ofstream debug;
    TFile f("histos.root", "new");
    runLumiOutput.open("runLumiOutput.txt");
    debug.open("debug.txt");
    initCounter();

    TH1F* null = new TH1F("","",1,0,1);

    float lowerMet = 0.0;
    float upperMet = 800.0;
    int metBins = 50;

    // met with no filters
    TH1F *h1D_pfCaloMet = new TH1F("h1D_pfCaloMet", "", metBins,lowerMet,upperMet);
    TH1F *h1D_pfMet = new TH1F("h1D_pfMet", "", metBins,lowerMet,upperMet);
    TH1F *h1D_caloMet = new TH1F("h1D_caloMet", "", metBins,lowerMet,upperMet);
    TH1F *h1D_pfClusterMet = new TH1F("h1D_pfClusterMet", "", metBins,lowerMet,upperMet);
    TH1F *h1D_pfChMet = new TH1F("h1D_pfChMet", "", metBins,lowerMet,upperMet);

    // 2d plots of met
    TH2F* h2D_pfCaloMet_pfMet = new TH2F("h2D_pfCaloMet_pfMet","", metBins,lowerMet,upperMet, metBins,lowerMet,upperMet);
    TH2F* h2D_pfCaloMet_caloMet = new TH2F("h2D_pfCaloMet_caloMet","", metBins,lowerMet,upperMet, metBins,lowerMet,upperMet);
    TH2F* h2D_caloMet_pfMet = new TH2F("h2D_caloMet_pfMet","", metBins,lowerMet,upperMet, metBins,lowerMet,upperMet);
    TH2F* h2D_pfClusterMet_pfMet = new TH2F("h2D_pfClusterMet_pfMet","", metBins,lowerMet,upperMet, metBins,lowerMet,upperMet);
    TH2F* h2D_pfClusterMet_caloMet = new TH2F("h2D_pfClusterMet_caloMet","", metBins,lowerMet,upperMet, metBins,lowerMet,upperMet);
    TH2F* h2D_pfClusterMet_pfCaloMet = new TH2F("h2D_pfClusterMet_pfCaloMet","", metBins,lowerMet,upperMet, metBins,lowerMet,upperMet);

    // other 2d plots
    TH2F* h2D_jetPt_caloMet = new TH2F("h2D_jetPt_caloMet","", metBins,lowerMet,upperMet, metBins,lowerMet,upperMet);

    // eta-phi of towers, pfclusters, and calojets
    float maxEta = 4.5;
    TH2F* h2D_towers_etaphi = new TH2F("h2D_towers_etaphi","",             50 ,-maxEta,maxEta, 50 ,-3.15,3.15);
    TH2F* h2D_towers_etaphi_em = new TH2F("h2D_towers_etaphi_em","",       50 ,-maxEta,maxEta, 50 ,-3.15,3.15);
    TH2F* h2D_towers_etaphi_had = new TH2F("h2D_towers_etaphi_had","",     50 ,-maxEta,maxEta, 50 ,-3.15,3.15);
    TH2F* h2D_towers_etaphi_outer = new TH2F("h2D_towers_etaphi_outer","", 50 ,-maxEta,maxEta, 50 ,-3.15,3.15);
    TH2F* h2D_pfclusters_etaphi = new TH2F("h2D_pfclusters_etaphi","",     50 ,-maxEta,maxEta, 50 ,-3.15,3.15);
    TH2F* h2D_calojets_etaphi = new TH2F("h2D_calojets_etaphi","",         50 ,-maxEta,maxEta, 50 ,-3.15,3.15);


    // filters
    std::vector<std::string> titlesFilters;
    titlesFilters.push_back(" NO filter");
    titlesFilters.push_back("+cscTightHalo");
    titlesFilters.push_back("+hcalNoise");
    titlesFilters.push_back("+hbheFilter");
    titlesFilters.push_back("+ecalDeadCell");
    titlesFilters.push_back("+jetID");

    // caloMet with filters layered
    std::vector<TH1F*> h1D_caloMet_filters_vec;
    TH1F *h1D_caloMet_halo = new TH1F("h1D_caloMet_halo", "", metBins,lowerMet,upperMet);
    TH1F *h1D_caloMet_halonoise = new TH1F("h1D_caloMet_halonoise", "", metBins,lowerMet,upperMet);
    TH1F *h1D_caloMet_halonoisehbhe = new TH1F("h1D_caloMet_halonoisehbhe", "", metBins,lowerMet,upperMet);
    TH1F *h1D_caloMet_halonoisehbheecal = new TH1F("h1D_caloMet_halonoisehbheecal", "", metBins,lowerMet,upperMet);
    TH1F *h1D_caloMet_halonoisehbheecaljet = new TH1F("h1D_caloMet_halonoisehbheecaljet", "", metBins,lowerMet,upperMet);
    h1D_caloMet_filters_vec.push_back(h1D_caloMet);
    h1D_caloMet_filters_vec.push_back(h1D_caloMet_halo);
    h1D_caloMet_filters_vec.push_back(h1D_caloMet_halonoise);
    h1D_caloMet_filters_vec.push_back(h1D_caloMet_halonoisehbhe);
    h1D_caloMet_filters_vec.push_back(h1D_caloMet_halonoisehbheecal);
    h1D_caloMet_filters_vec.push_back(h1D_caloMet_halonoisehbheecaljet);

    // caloMetPhi with filters layered
    std::vector<TH1F*> h1D_caloMetPhi_filters_vec;
    TH1F *h1D_caloMetPhi = new TH1F("h1D_caloMetPhi", "",                                           100,-3.14,3.14);
    TH1F *h1D_caloMetPhi_halo = new TH1F("h1D_caloMetPhi_halo", "",                                 100,-3.14,3.14);
    TH1F *h1D_caloMetPhi_halonoise = new TH1F("h1D_caloMetPhi_halonoise", "",                       100,-3.14,3.14);
    TH1F *h1D_caloMetPhi_halonoisehbhe = new TH1F("h1D_caloMetPhi_halonoisehbhe", "",               100,-3.14,3.14);
    TH1F *h1D_caloMetPhi_halonoisehbheecal = new TH1F("h1D_caloMetPhi_halonoisehbheecal", "",       100,-3.14,3.14);
    TH1F *h1D_caloMetPhi_halonoisehbheecaljet = new TH1F("h1D_caloMetPhi_halonoisehbheecaljet", "", 100,-3.14,3.14);
    h1D_caloMetPhi_filters_vec.push_back(h1D_caloMetPhi);
    h1D_caloMetPhi_filters_vec.push_back(h1D_caloMetPhi_halo);
    h1D_caloMetPhi_filters_vec.push_back(h1D_caloMetPhi_halonoise);
    h1D_caloMetPhi_filters_vec.push_back(h1D_caloMetPhi_halonoisehbhe);
    h1D_caloMetPhi_filters_vec.push_back(h1D_caloMetPhi_halonoisehbheecal);
    h1D_caloMetPhi_filters_vec.push_back(h1D_caloMetPhi_halonoisehbheecaljet);

    // pfMetPhi with filters layered
    std::vector<TH1F*> h1D_pfMetPhi_filters_vec;
    TH1F *h1D_pfMetPhi = new TH1F("h1D_pfMetPhi", "",                                           100,-3.14,3.14);
    TH1F *h1D_pfMetPhi_halo = new TH1F("h1D_pfMetPhi_halo", "",                                 100,-3.14,3.14);
    TH1F *h1D_pfMetPhi_halonoise = new TH1F("h1D_pfMetPhi_halonoise", "",                       100,-3.14,3.14);
    TH1F *h1D_pfMetPhi_halonoisehbhe = new TH1F("h1D_pfMetPhi_halonoisehbhe", "",               100,-3.14,3.14);
    TH1F *h1D_pfMetPhi_halonoisehbheecal = new TH1F("h1D_pfMetPhi_halonoisehbheecal", "",       100,-3.14,3.14);
    TH1F *h1D_pfMetPhi_halonoisehbheecaljet = new TH1F("h1D_pfMetPhi_halonoisehbheecaljet", "", 100,-3.14,3.14);
    h1D_pfMetPhi_filters_vec.push_back(h1D_pfMetPhi);
    h1D_pfMetPhi_filters_vec.push_back(h1D_pfMetPhi_halo);
    h1D_pfMetPhi_filters_vec.push_back(h1D_pfMetPhi_halonoise);
    h1D_pfMetPhi_filters_vec.push_back(h1D_pfMetPhi_halonoisehbhe);
    h1D_pfMetPhi_filters_vec.push_back(h1D_pfMetPhi_halonoisehbheecal);
    h1D_pfMetPhi_filters_vec.push_back(h1D_pfMetPhi_halonoisehbheecaljet);

    // pfCaloMet with filters layered
    std::vector<TH1F*> h1D_pfCaloMet_filters_vec;
    TH1F *h1D_pfCaloMet_halo = new TH1F("h1D_pfCaloMet_halo", "", metBins,lowerMet,upperMet);
    TH1F *h1D_pfCaloMet_halonoise = new TH1F("h1D_pfCaloMet_halonoise", "", metBins,lowerMet,upperMet);
    TH1F *h1D_pfCaloMet_halonoisehbhe = new TH1F("h1D_pfCaloMet_halonoisehbhe", "", metBins,lowerMet,upperMet);
    TH1F *h1D_pfCaloMet_halonoisehbheecal = new TH1F("h1D_pfCaloMet_halonoisehbheecal", "", metBins,lowerMet,upperMet);
    TH1F *h1D_pfCaloMet_halonoisehbheecaljet = new TH1F("h1D_pfCaloMet_halonoisehbheecaljet", "", metBins,lowerMet,upperMet);
    h1D_pfCaloMet_filters_vec.push_back(h1D_pfCaloMet);
    h1D_pfCaloMet_filters_vec.push_back(h1D_pfCaloMet_halo);
    h1D_pfCaloMet_filters_vec.push_back(h1D_pfCaloMet_halonoise);
    h1D_pfCaloMet_filters_vec.push_back(h1D_pfCaloMet_halonoisehbhe);
    h1D_pfCaloMet_filters_vec.push_back(h1D_pfCaloMet_halonoisehbheecal);
    h1D_pfCaloMet_filters_vec.push_back(h1D_pfCaloMet_halonoisehbheecaljet);

    // pfChMet with filters layered
    std::vector<TH1F*> h1D_pfChMet_filters_vec;
    TH1F *h1D_pfChMet_halo = new TH1F("h1D_pfChMet_halo", "", metBins,lowerMet,upperMet);
    TH1F *h1D_pfChMet_halonoise = new TH1F("h1D_pfChMet_halonoise", "", metBins,lowerMet,upperMet);
    TH1F *h1D_pfChMet_halonoisehbhe = new TH1F("h1D_pfChMet_halonoisehbhe", "", metBins,lowerMet,upperMet);
    TH1F *h1D_pfChMet_halonoisehbheecal = new TH1F("h1D_pfChMet_halonoisehbheecal", "", metBins,lowerMet,upperMet);
    TH1F *h1D_pfChMet_halonoisehbheecaljet = new TH1F("h1D_pfChMet_halonoisehbheecaljet", "", metBins,lowerMet,upperMet);
    h1D_pfChMet_filters_vec.push_back(h1D_pfChMet);
    h1D_pfChMet_filters_vec.push_back(h1D_pfChMet_halo);
    h1D_pfChMet_filters_vec.push_back(h1D_pfChMet_halonoise);
    h1D_pfChMet_filters_vec.push_back(h1D_pfChMet_halonoisehbhe);
    h1D_pfChMet_filters_vec.push_back(h1D_pfChMet_halonoisehbheecal);
    h1D_pfChMet_filters_vec.push_back(h1D_pfChMet_halonoisehbheecaljet);

    // pfMet with filters layered
    std::vector<TH1F*> h1D_pfMet_filters_vec;
    TH1F *h1D_pfMet_halo = new TH1F("h1D_pfMet_halo", "", metBins,lowerMet,upperMet);
    TH1F *h1D_pfMet_halonoise = new TH1F("h1D_pfMet_halonoise", "", metBins,lowerMet,upperMet);
    TH1F *h1D_pfMet_halonoisehbhe = new TH1F("h1D_pfMet_halonoisehbhe", "", metBins,lowerMet,upperMet);
    TH1F *h1D_pfMet_halonoisehbheecal = new TH1F("h1D_pfMet_halonoisehbheecal", "", metBins,lowerMet,upperMet);
    TH1F *h1D_pfMet_halonoisehbheecaljet = new TH1F("h1D_pfMet_halonoisehbheecaljet", "", metBins,lowerMet,upperMet);
    h1D_pfMet_filters_vec.push_back(h1D_pfMet);
    h1D_pfMet_filters_vec.push_back(h1D_pfMet_halo);
    h1D_pfMet_filters_vec.push_back(h1D_pfMet_halonoise);
    h1D_pfMet_filters_vec.push_back(h1D_pfMet_halonoisehbhe);
    h1D_pfMet_filters_vec.push_back(h1D_pfMet_halonoisehbheecal);
    h1D_pfMet_filters_vec.push_back(h1D_pfMet_halonoisehbheecaljet);

    // pfClusterMet with filters layered
    std::vector<TH1F*> h1D_pfClusterMet_filters_vec;
    TH1F *h1D_pfClusterMet_halo = new TH1F("h1D_pfClusterMet_halo", "", metBins,lowerMet,upperMet);
    TH1F *h1D_pfClusterMet_halonoise = new TH1F("h1D_pfClusterMet_halonoise", "", metBins,lowerMet,upperMet);
    TH1F *h1D_pfClusterMet_halonoisehbhe = new TH1F("h1D_pfClusterMet_halonoisehbhe", "", metBins,lowerMet,upperMet);
    TH1F *h1D_pfClusterMet_halonoisehbheecal = new TH1F("h1D_pfClusterMet_halonoisehbheecal", "", metBins,lowerMet,upperMet);
    TH1F *h1D_pfClusterMet_halonoisehbheecaljet = new TH1F("h1D_pfClusterMet_halonoisehbheecaljet", "", metBins,lowerMet,upperMet);
    h1D_pfClusterMet_filters_vec.push_back(h1D_pfClusterMet);
    h1D_pfClusterMet_filters_vec.push_back(h1D_pfClusterMet_halo);
    h1D_pfClusterMet_filters_vec.push_back(h1D_pfClusterMet_halonoise);
    h1D_pfClusterMet_filters_vec.push_back(h1D_pfClusterMet_halonoisehbhe);
    h1D_pfClusterMet_filters_vec.push_back(h1D_pfClusterMet_halonoisehbheecal);
    h1D_pfClusterMet_filters_vec.push_back(h1D_pfClusterMet_halonoisehbheecaljet);

    // comparison of METs
    std::vector<std::string> titlesMet;
    titlesMet.push_back("pfCaloMet");
    titlesMet.push_back("pfMet");
    titlesMet.push_back("caloMet");
    titlesMet.push_back("pfClusterMet");
    titlesMet.push_back("pfChMet");

    // all met after filters
    std::vector<TH1F*> h1D_met_vec;
    h1D_met_vec.push_back(h1D_pfCaloMet_halonoisehbheecaljet);
    h1D_met_vec.push_back(h1D_pfMet_halonoisehbheecaljet);
    h1D_met_vec.push_back(h1D_caloMet_halonoisehbheecaljet);
    h1D_met_vec.push_back(h1D_pfClusterMet_halonoisehbheecaljet);
    h1D_met_vec.push_back(h1D_pfChMet_halonoisehbheecaljet);


    // dPhi(leading jet,caloMet)
    std::vector<TH1F*> h1D_jetCaloMetPhi_filters_vec;
    TH1F *h1D_jetCaloMetPhi               = new TH1F("h1D_jetCaloMetPhi", "",               70,0,3.5);
    TH1F *h1D_jetCaloMetPhi_halo          = new TH1F("h1D_jetCaloMetPhi_halo", "",          70,0,3.5);
    TH1F *h1D_jetCaloMetPhi_halonoise     = new TH1F("h1D_jetCaloMetPhi_halonoise", "",     70,0,3.5);
    TH1F *h1D_jetCaloMetPhi_halonoisehbhe = new TH1F("h1D_jetCaloMetPhi_halonoisehbhe", "", 70,0,3.5);
    TH1F *h1D_jetCaloMetPhi_halonoisehbheecal = new TH1F("h1D_jetCaloMetPhi_halonoisehbheecal", "", 70,0,3.5);
    TH1F *h1D_jetCaloMetPhi_halonoisehbheecaljet = new TH1F("h1D_jetCaloMetPhi_halonoisehbheecaljet", "", 70,0,3.5);
    h1D_jetCaloMetPhi_filters_vec.push_back(h1D_jetCaloMetPhi);
    h1D_jetCaloMetPhi_filters_vec.push_back(h1D_jetCaloMetPhi_halo);
    h1D_jetCaloMetPhi_filters_vec.push_back(h1D_jetCaloMetPhi_halonoise);
    h1D_jetCaloMetPhi_filters_vec.push_back(h1D_jetCaloMetPhi_halonoisehbhe);
    h1D_jetCaloMetPhi_filters_vec.push_back(h1D_jetCaloMetPhi_halonoisehbheecal);
    h1D_jetCaloMetPhi_filters_vec.push_back(h1D_jetCaloMetPhi_halonoisehbheecaljet);

    // leading jet characterization
    std::vector<std::string> titlesLeadingJet; titlesLeadingJet.push_back("leading PF jet");
    std::vector<TH1F*> h1D_leadingJet_chf_vec;
    std::vector<TH1F*> h1D_leadingJet_nhf_vec;
    std::vector<TH1F*> h1D_leadingJet_cef_vec;
    std::vector<TH1F*> h1D_leadingJet_nef_vec;
    std::vector<TH1F*> h1D_leadingJet_cm_vec;

    TH1F *h1D_leadingJet_chf = new TH1F("h1D_leadingJet_chf", "", 50, 0, 1);
    TH1F *h1D_leadingJet_nhf = new TH1F("h1D_leadingJet_nhf", "", 50, 0, 1);
    TH1F *h1D_leadingJet_cef = new TH1F("h1D_leadingJet_cef", "", 50, 0, 1);
    TH1F *h1D_leadingJet_nef = new TH1F("h1D_leadingJet_nef", "", 50, 0, 1);
    TH1F *h1D_leadingJet_cm = new TH1F("h1D_leadingJet_cm", "", 60, 0, 60);

    h1D_leadingJet_chf_vec.push_back(h1D_leadingJet_chf);
    h1D_leadingJet_nhf_vec.push_back(h1D_leadingJet_nhf);
    h1D_leadingJet_cef_vec.push_back(h1D_leadingJet_cef);
    h1D_leadingJet_nef_vec.push_back(h1D_leadingJet_nef);
    h1D_leadingJet_cm_vec.push_back(h1D_leadingJet_cm);

    // N-1 plots for HCAL Tight Noise Filter
    std::vector<std::string> titlesNm1; titlesNm1.push_back("N-1");
    std::vector<TH1F*> h1D_nm1_maxHPDHits_vec;
    std::vector<TH1F*> h1D_nm1_maxHPDNoOtherHits_vec;
    std::vector<TH1F*> h1D_nm1_numIsolatedNoiseChannels_vec;
    std::vector<TH1F*> h1D_nm1_isolatedNoiseSumE_vec;
    std::vector<TH1F*> h1D_nm1_isolatedNoiseSumEt_vec;

    TH1F *h1D_nm1_maxHPDHits = new TH1F("h1D_nm1_maxHPDHits","",                             50 ,0,100);
    TH1F *h1D_nm1_maxHPDNoOtherHits = new TH1F("h1D_nm1_maxHPDNoOtherHits","",               50 ,0,100);
    TH1F *h1D_nm1_numIsolatedNoiseChannels = new TH1F("h1D_nm1_numIsolatedNoiseChannels","", 50 ,0,100);
    TH1F *h1D_nm1_isolatedNoiseSumE = new TH1F("h1D_nm1_isolatedNoiseSumE","",               50 ,0,100);
    TH1F *h1D_nm1_isolatedNoiseSumEt = new TH1F("h1D_nm1_isolatedNoiseSumEt","",             50 ,0,100);

    h1D_nm1_maxHPDHits_vec.push_back(h1D_nm1_maxHPDHits);
    h1D_nm1_maxHPDNoOtherHits_vec.push_back(h1D_nm1_maxHPDNoOtherHits);
    h1D_nm1_numIsolatedNoiseChannels_vec.push_back(h1D_nm1_numIsolatedNoiseChannels);
    h1D_nm1_isolatedNoiseSumE_vec.push_back(h1D_nm1_isolatedNoiseSumE);
    h1D_nm1_isolatedNoiseSumEt_vec.push_back(h1D_nm1_isolatedNoiseSumEt);


    // caloMet with and without each filter
    std::vector<std::string> titlesOneFilt = {"without filter", "with filter"};
    std::vector<std::string> titlesOnesFilt = {"without filters", "with filters"};

    std::vector<TH1F*> h1D_caloMet_filt_halo_vec; h1D_caloMet_filt_halo_vec.push_back(h1D_caloMet);
    TH1F *h1D_caloMet_filt_halo = new TH1F("h1D_caloMet_filt_halo", "", metBins,lowerMet,upperMet);
    h1D_caloMet_filt_halo_vec.push_back(h1D_caloMet_filt_halo);

    std::vector<TH1F*> h1D_caloMet_filt_track_vec; h1D_caloMet_filt_track_vec.push_back(h1D_caloMet);
    TH1F *h1D_caloMet_filt_track = new TH1F("h1D_caloMet_filt_track", "", metBins,lowerMet,upperMet);
    h1D_caloMet_filt_track_vec.push_back(h1D_caloMet_filt_track);

    std::vector<TH1F*> h1D_caloMet_filt_isonoise_vec; h1D_caloMet_filt_isonoise_vec.push_back(h1D_caloMet);
    TH1F *h1D_caloMet_filt_isonoise = new TH1F("h1D_caloMet_filt_isonoise", "", metBins,lowerMet,upperMet);
    h1D_caloMet_filt_isonoise_vec.push_back(h1D_caloMet_filt_isonoise);

    std::vector<TH1F*> h1D_caloMet_filt_tightnoise_vec; h1D_caloMet_filt_tightnoise_vec.push_back(h1D_caloMet);
    TH1F *h1D_caloMet_filt_tightnoise = new TH1F("h1D_caloMet_filt_tightnoise", "", metBins,lowerMet,upperMet);
    h1D_caloMet_filt_tightnoise_vec.push_back(h1D_caloMet_filt_tightnoise);

    std::vector<TH1F*> h1D_caloMet_filt_hbherun1_vec; h1D_caloMet_filt_hbherun1_vec.push_back(h1D_caloMet);
    TH1F *h1D_caloMet_filt_hbherun1 = new TH1F("h1D_caloMet_filt_hbherun1", "", metBins,lowerMet,upperMet);
    h1D_caloMet_filt_hbherun1_vec.push_back(h1D_caloMet_filt_hbherun1);

    std::vector<TH1F*> h1D_caloMet_filt_ecalcell_vec; h1D_caloMet_filt_ecalcell_vec.push_back(h1D_caloMet);
    TH1F *h1D_caloMet_filt_ecalcell = new TH1F("h1D_caloMet_filt_ecalcell", "", metBins,lowerMet,upperMet);
    h1D_caloMet_filt_ecalcell_vec.push_back(h1D_caloMet_filt_ecalcell);

    std::vector<TH1F*> h1D_caloMet_filt_eebadsc_vec; h1D_caloMet_filt_eebadsc_vec.push_back(h1D_caloMet);
    TH1F *h1D_caloMet_filt_eebadsc = new TH1F("h1D_caloMet_filt_eebadsc", "", metBins,lowerMet,upperMet);
    h1D_caloMet_filt_eebadsc_vec.push_back(h1D_caloMet_filt_eebadsc);


    // detector status
    std::vector<TH1F*> h1D_detectorStatus_vec;
    std::vector<std::string> titlesDCS;
    TH1F *h1D_detectorStatus = new TH1F("h1D_detectorStatus","", 32,0,32);
    TH1F *h1D_detectorStatus_filt = new TH1F("h1D_detectorStatus_filt","", 32,0,32);
    h1D_detectorStatus_vec.push_back(h1D_detectorStatus);
    h1D_detectorStatus_vec.push_back(h1D_detectorStatus_filt);
    titlesDCS.push_back("DCS bits (no filters)");
    titlesDCS.push_back("DCS bits (filters)");

    // eff by run
    std::vector<TH1F*> h1D_effbyrun_vec;
    int nRuns = 50;
    TH1F *h1D_effbyrun = new TH1F("h1D_effbyrun","", nRuns,0,nRuns);
    TH1F *h1D_effbyrun_filt = new TH1F("h1D_effbyrun_filt","", nRuns,0,nRuns);
    h1D_effbyrun_vec.push_back(h1D_effbyrun);
    h1D_effbyrun_vec.push_back(h1D_effbyrun_filt);

    // maxZeros
    std::vector<TH1F*> h1D_maxZeros_vec;
    TH1F *h1D_maxZeros = new TH1F("h1D_maxZeros","", 40,0,40);
    TH1F *h1D_maxZeros_filt = new TH1F("h1D_maxZeros_filt","", 40,0,40);
    h1D_maxZeros_vec.push_back(h1D_maxZeros);
    h1D_maxZeros_vec.push_back(h1D_maxZeros_filt);

    // dominick trigger check
    std::vector<TH1F*> h1D_trig_pfMet_vec;
    std::vector<std::string> titlesTrig;
    TH1F *h1D_trig_pfMet = new TH1F("h1D_trig_pfMet","",             metBins,lowerMet,upperMet); titlesTrig.push_back("PFMET170 (normal)"); 
    TH1F *h1D_trig_pfMet_clean = new TH1F("h1D_trig_pfMet_clean","", metBins,lowerMet,upperMet); titlesTrig.push_back("NoiseCleaned"); 
    TH1F *h1D_trig_pfMet_both = new TH1F("h1D_trig_pfMet_both","", metBins,lowerMet,upperMet); titlesTrig.push_back("both"); 
    h1D_trig_pfMet_vec.push_back(h1D_trig_pfMet);
    h1D_trig_pfMet_vec.push_back(h1D_trig_pfMet_clean);
    h1D_trig_pfMet_vec.push_back(h1D_trig_pfMet_both);

    // single plots
    TH1F* h1D_towers_phi = new TH1F("h2D_towers_phi","",              30 ,-3.15,3.15);
    TH1F* h1D_towers_phi_em = new TH1F("h2D_towers_phi_em","",        30 ,-3.15,3.15);
    TH1F* h1D_towers_phi_had = new TH1F("h2D_towers_phi_had","",      30 ,-3.15,3.15);
    TH1F* h1D_towers_phi_outer = new TH1F("h2D_towers_phi_outer","",  30 ,-3.15,3.15);
    TH1F* h1D_pfclusters_phi = new TH1F("h2D_pfclusters_phi","",      30 ,-3.15,3.15);
    TH1F* h1D_calojets_phi = new TH1F("h2D_calojets_phi","",          30 ,-3.15,3.15);
    TH1F* h1D_caloMetNew = new TH1F("h1D_caloMetNew", "", metBins, lowerMet, upperMet);
    TH1F* h1D_caloMetPhiNew = new TH1F("h1D_caloMetPhiNew","",       100,-3.14,3.14 );

    // hcalnoise
    std::vector<std::string> titlesHcalnoise = {"passes all filters", "fails JetID"};
    std::vector<TH1F*> h1D_hcalnoise_HasBadRBXTS4TS5_vec;
    std::vector<TH1F*> h1D_hcalnoise_GetRecHitEnergy_vec;
    std::vector<TH1F*> h1D_hcalnoise_GetRecHitEnergy15_vec;
    std::vector<TH1F*> h1D_hcalnoise_GetTotalCalibCharge_vec;
    std::vector<TH1F*> h1D_hcalnoise_TS4TS5NoiseSumE_vec;
    std::vector<TH1F*> h1D_hcalnoise_TS4TS5NoiseSumEt_vec;
    std::vector<TH1F*> h1D_hcalnoise_eventChargeFraction_vec;
    std::vector<TH1F*> h1D_hcalnoise_eventEMEnergy_vec;
    std::vector<TH1F*> h1D_hcalnoise_eventEMFraction_vec;
    std::vector<TH1F*> h1D_hcalnoise_eventHadEnergy_vec;
    std::vector<TH1F*> h1D_hcalnoise_eventTrackEnergy_vec;
    std::vector<TH1F*> h1D_hcalnoise_flatNoiseSumE_vec;
    std::vector<TH1F*> h1D_hcalnoise_flatNoiseSumEt_vec;
    std::vector<TH1F*> h1D_hcalnoise_isolatedNoiseSumE_vec;
    std::vector<TH1F*> h1D_hcalnoise_isolatedNoiseSumEt_vec;
    std::vector<TH1F*> h1D_hcalnoise_max10GeVHitTime_vec;
    std::vector<TH1F*> h1D_hcalnoise_max25GeVHitTime_vec;
    std::vector<TH1F*> h1D_hcalnoise_maxE10TS_vec;
    std::vector<TH1F*> h1D_hcalnoise_maxE2Over10TS_vec;
    std::vector<TH1F*> h1D_hcalnoise_maxE2TS_vec;
    std::vector<TH1F*> h1D_hcalnoise_min10GeVHitTime_vec;
    std::vector<TH1F*> h1D_hcalnoise_min25GeVHitTime_vec;
    std::vector<TH1F*> h1D_hcalnoise_minE10TS_vec;
    std::vector<TH1F*> h1D_hcalnoise_minE2Over10TS_vec;
    std::vector<TH1F*> h1D_hcalnoise_minE2TS_vec;
    std::vector<TH1F*> h1D_hcalnoise_minHPDEMF_vec;
    std::vector<TH1F*> h1D_hcalnoise_minRBXEMF_vec;
    std::vector<TH1F*> h1D_hcalnoise_rms10GeVHitTime_vec;
    std::vector<TH1F*> h1D_hcalnoise_rms25GeVHitTime_vec;
    std::vector<TH1F*> h1D_hcalnoise_spikeNoiseSumE_vec;
    std::vector<TH1F*> h1D_hcalnoise_spikeNoiseSumEt_vec;
    std::vector<TH1F*> h1D_hcalnoise_triangleNoiseSumE_vec;
    std::vector<TH1F*> h1D_hcalnoise_triangleNoiseSumEt_vec;
    std::vector<TH1F*> h1D_hcalnoise_GetRecHitCount_vec;
    std::vector<TH1F*> h1D_hcalnoise_GetRecHitCount15_vec;
    std::vector<TH1F*> h1D_hcalnoise_hbheIsoNoiseFilter_vec;
    std::vector<TH1F*> h1D_hcalnoise_maxHPDHits_vec;
    std::vector<TH1F*> h1D_hcalnoise_maxHPDNoOtherHits_vec;
    std::vector<TH1F*> h1D_hcalnoise_maxRBXHits_vec;
    std::vector<TH1F*> h1D_hcalnoise_maxZeros_vec;
    std::vector<TH1F*> h1D_hcalnoise_noiseFilterStatus_vec;
    std::vector<TH1F*> h1D_hcalnoise_noiseType_vec;
    std::vector<TH1F*> h1D_hcalnoise_num10GeVHits_vec;
    std::vector<TH1F*> h1D_hcalnoise_num25GeVHits_vec;
    std::vector<TH1F*> h1D_hcalnoise_numFlatNoiseChannels_vec;
    std::vector<TH1F*> h1D_hcalnoise_numIsolatedNoiseChannels_vec;
    std::vector<TH1F*> h1D_hcalnoise_numProblematicRBXs_vec;
    std::vector<TH1F*> h1D_hcalnoise_numSpikeNoiseChannels_vec;
    std::vector<TH1F*> h1D_hcalnoise_numTS4TS5NoiseChannels_vec;
    std::vector<TH1F*> h1D_hcalnoise_numTriangleNoiseChannels_vec;
    std::vector<TH1F*> h1D_hcalnoise_passHighLevelNoiseFilter_vec;
    std::vector<TH1F*> h1D_hcalnoise_passLooseNoiseFilter_vec;
    std::vector<TH1F*> h1D_hcalnoise_passTightNoiseFilter_vec;

    std::vector<TH1F*> h1D_twrs_numBadEcalCells_vec;
    std::vector<TH1F*> h1D_twrs_numRecoveredEcalCells_vec;
    std::vector<TH1F*> h1D_twrs_numProblematicEcalCells_vec;
    std::vector<TH1F*> h1D_twrs_numBadHcalCells_vec;
    std::vector<TH1F*> h1D_twrs_numRecoveredHcalCells_vec;
    std::vector<TH1F*> h1D_twrs_numProblematicHcalCells_vec;
    std::vector<TH1F*> h1D_twrs_numCrystals_vec;

    // _jet means it doesn't pass jet id
    TH1F *h1D_hcalnoise_HasBadRBXTS4TS5 = new TH1F("h1D_hcalnoise_HasBadRBXTS4TS5","", 2,0,2);
    TH1F *h1D_hcalnoise_HasBadRBXTS4TS5_jet = new TH1F("h1D_hcalnoise_HasBadRBXTS4TS5_jet","", 2,0,2);
    h1D_hcalnoise_HasBadRBXTS4TS5_vec.push_back(h1D_hcalnoise_HasBadRBXTS4TS5);
    h1D_hcalnoise_HasBadRBXTS4TS5_vec.push_back(h1D_hcalnoise_HasBadRBXTS4TS5_jet);
    TH1F *h1D_hcalnoise_GetRecHitEnergy = new TH1F("h1D_hcalnoise_GetRecHitEnergy","", 100,0,9100);
    TH1F *h1D_hcalnoise_GetRecHitEnergy_jet = new TH1F("h1D_hcalnoise_GetRecHitEnergy_jet","", 100,0,9100);
    h1D_hcalnoise_GetRecHitEnergy_vec.push_back(h1D_hcalnoise_GetRecHitEnergy);
    h1D_hcalnoise_GetRecHitEnergy_vec.push_back(h1D_hcalnoise_GetRecHitEnergy_jet);
    TH1F *h1D_hcalnoise_GetRecHitEnergy15 = new TH1F("h1D_hcalnoise_GetRecHitEnergy15","", 100,0,8600);
    TH1F *h1D_hcalnoise_GetRecHitEnergy15_jet = new TH1F("h1D_hcalnoise_GetRecHitEnergy15_jet","", 100,0,8600);
    h1D_hcalnoise_GetRecHitEnergy15_vec.push_back(h1D_hcalnoise_GetRecHitEnergy15);
    h1D_hcalnoise_GetRecHitEnergy15_vec.push_back(h1D_hcalnoise_GetRecHitEnergy15_jet);
    TH1F *h1D_hcalnoise_GetTotalCalibCharge = new TH1F("h1D_hcalnoise_GetTotalCalibCharge","", 100,0,200);
    TH1F *h1D_hcalnoise_GetTotalCalibCharge_jet = new TH1F("h1D_hcalnoise_GetTotalCalibCharge_jet","", 100,0,200);
    h1D_hcalnoise_GetTotalCalibCharge_vec.push_back(h1D_hcalnoise_GetTotalCalibCharge);
    h1D_hcalnoise_GetTotalCalibCharge_vec.push_back(h1D_hcalnoise_GetTotalCalibCharge_jet);
    TH1F *h1D_hcalnoise_TS4TS5NoiseSumE = new TH1F("h1D_hcalnoise_TS4TS5NoiseSumE","", 100,0,6400);
    TH1F *h1D_hcalnoise_TS4TS5NoiseSumE_jet = new TH1F("h1D_hcalnoise_TS4TS5NoiseSumE_jet","", 100,0,6400);
    h1D_hcalnoise_TS4TS5NoiseSumE_vec.push_back(h1D_hcalnoise_TS4TS5NoiseSumE);
    h1D_hcalnoise_TS4TS5NoiseSumE_vec.push_back(h1D_hcalnoise_TS4TS5NoiseSumE_jet);
    TH1F *h1D_hcalnoise_TS4TS5NoiseSumEt = new TH1F("h1D_hcalnoise_TS4TS5NoiseSumEt","", 100,0,6100);
    TH1F *h1D_hcalnoise_TS4TS5NoiseSumEt_jet = new TH1F("h1D_hcalnoise_TS4TS5NoiseSumEt_jet","", 100,0,6100);
    h1D_hcalnoise_TS4TS5NoiseSumEt_vec.push_back(h1D_hcalnoise_TS4TS5NoiseSumEt);
    h1D_hcalnoise_TS4TS5NoiseSumEt_vec.push_back(h1D_hcalnoise_TS4TS5NoiseSumEt_jet);
    TH1F *h1D_hcalnoise_eventChargeFraction = new TH1F("h1D_hcalnoise_eventChargeFraction","", 100,0,9.5);
    TH1F *h1D_hcalnoise_eventChargeFraction_jet = new TH1F("h1D_hcalnoise_eventChargeFraction_jet","", 100,0,9.5);
    h1D_hcalnoise_eventChargeFraction_vec.push_back(h1D_hcalnoise_eventChargeFraction);
    h1D_hcalnoise_eventChargeFraction_vec.push_back(h1D_hcalnoise_eventChargeFraction_jet);
    TH1F *h1D_hcalnoise_eventEMEnergy = new TH1F("h1D_hcalnoise_eventEMEnergy","", 100,0,29500);
    TH1F *h1D_hcalnoise_eventEMEnergy_jet = new TH1F("h1D_hcalnoise_eventEMEnergy_jet","", 100,0,29500);
    h1D_hcalnoise_eventEMEnergy_vec.push_back(h1D_hcalnoise_eventEMEnergy);
    h1D_hcalnoise_eventEMEnergy_vec.push_back(h1D_hcalnoise_eventEMEnergy_jet);
    TH1F *h1D_hcalnoise_eventEMFraction = new TH1F("h1D_hcalnoise_eventEMFraction","", 100,0,1.08);
    TH1F *h1D_hcalnoise_eventEMFraction_jet = new TH1F("h1D_hcalnoise_eventEMFraction_jet","", 100,0,1.08);
    h1D_hcalnoise_eventEMFraction_vec.push_back(h1D_hcalnoise_eventEMFraction);
    h1D_hcalnoise_eventEMFraction_vec.push_back(h1D_hcalnoise_eventEMFraction_jet);
    TH1F *h1D_hcalnoise_eventHadEnergy = new TH1F("h1D_hcalnoise_eventHadEnergy","", 100,0,19400);
    TH1F *h1D_hcalnoise_eventHadEnergy_jet = new TH1F("h1D_hcalnoise_eventHadEnergy_jet","", 100,0,19400);
    h1D_hcalnoise_eventHadEnergy_vec.push_back(h1D_hcalnoise_eventHadEnergy);
    h1D_hcalnoise_eventHadEnergy_vec.push_back(h1D_hcalnoise_eventHadEnergy_jet);
    TH1F *h1D_hcalnoise_eventTrackEnergy = new TH1F("h1D_hcalnoise_eventTrackEnergy","", 100,0,87000);
    TH1F *h1D_hcalnoise_eventTrackEnergy_jet = new TH1F("h1D_hcalnoise_eventTrackEnergy_jet","", 100,0,87000);
    h1D_hcalnoise_eventTrackEnergy_vec.push_back(h1D_hcalnoise_eventTrackEnergy);
    h1D_hcalnoise_eventTrackEnergy_vec.push_back(h1D_hcalnoise_eventTrackEnergy_jet);
    TH1F *h1D_hcalnoise_flatNoiseSumE = new TH1F("h1D_hcalnoise_flatNoiseSumE","", 100,0,20);
    TH1F *h1D_hcalnoise_flatNoiseSumE_jet = new TH1F("h1D_hcalnoise_flatNoiseSumE_jet","", 100,0,20);
    h1D_hcalnoise_flatNoiseSumE_vec.push_back(h1D_hcalnoise_flatNoiseSumE);
    h1D_hcalnoise_flatNoiseSumE_vec.push_back(h1D_hcalnoise_flatNoiseSumE_jet);
    TH1F *h1D_hcalnoise_flatNoiseSumEt = new TH1F("h1D_hcalnoise_flatNoiseSumEt","", 100,0,20);
    TH1F *h1D_hcalnoise_flatNoiseSumEt_jet = new TH1F("h1D_hcalnoise_flatNoiseSumEt_jet","", 100,0,20);
    h1D_hcalnoise_flatNoiseSumEt_vec.push_back(h1D_hcalnoise_flatNoiseSumEt);
    h1D_hcalnoise_flatNoiseSumEt_vec.push_back(h1D_hcalnoise_flatNoiseSumEt_jet);
    TH1F *h1D_hcalnoise_isolatedNoiseSumE = new TH1F("h1D_hcalnoise_isolatedNoiseSumE","", 100,0,200);
    TH1F *h1D_hcalnoise_isolatedNoiseSumE_jet = new TH1F("h1D_hcalnoise_isolatedNoiseSumE_jet","", 100,0,200);
    h1D_hcalnoise_isolatedNoiseSumE_vec.push_back(h1D_hcalnoise_isolatedNoiseSumE);
    h1D_hcalnoise_isolatedNoiseSumE_vec.push_back(h1D_hcalnoise_isolatedNoiseSumE_jet);
    TH1F *h1D_hcalnoise_isolatedNoiseSumEt = new TH1F("h1D_hcalnoise_isolatedNoiseSumEt","", 100,0,200);
    TH1F *h1D_hcalnoise_isolatedNoiseSumEt_jet = new TH1F("h1D_hcalnoise_isolatedNoiseSumEt_jet","", 100,0,200);
    h1D_hcalnoise_isolatedNoiseSumEt_vec.push_back(h1D_hcalnoise_isolatedNoiseSumEt);
    h1D_hcalnoise_isolatedNoiseSumEt_vec.push_back(h1D_hcalnoise_isolatedNoiseSumEt_jet);
    TH1F *h1D_hcalnoise_max10GeVHitTime = new TH1F("h1D_hcalnoise_max10GeVHitTime","", 100,-1,20);
    TH1F *h1D_hcalnoise_max10GeVHitTime_jet = new TH1F("h1D_hcalnoise_max10GeVHitTime_jet","", 100,-1,20);
    h1D_hcalnoise_max10GeVHitTime_vec.push_back(h1D_hcalnoise_max10GeVHitTime);
    h1D_hcalnoise_max10GeVHitTime_vec.push_back(h1D_hcalnoise_max10GeVHitTime_jet);
    TH1F *h1D_hcalnoise_max25GeVHitTime = new TH1F("h1D_hcalnoise_max25GeVHitTime","", 100,-1,20);
    TH1F *h1D_hcalnoise_max25GeVHitTime_jet = new TH1F("h1D_hcalnoise_max25GeVHitTime_jet","", 100,-1,20);
    h1D_hcalnoise_max25GeVHitTime_vec.push_back(h1D_hcalnoise_max25GeVHitTime);
    h1D_hcalnoise_max25GeVHitTime_vec.push_back(h1D_hcalnoise_max25GeVHitTime_jet);
    TH1F *h1D_hcalnoise_maxE10TS = new TH1F("h1D_hcalnoise_maxE10TS","", 100,0,5000);
    TH1F *h1D_hcalnoise_maxE10TS_jet = new TH1F("h1D_hcalnoise_maxE10TS_jet","", 100,0,5000);
    h1D_hcalnoise_maxE10TS_vec.push_back(h1D_hcalnoise_maxE10TS);
    h1D_hcalnoise_maxE10TS_vec.push_back(h1D_hcalnoise_maxE10TS_jet);
    TH1F *h1D_hcalnoise_maxE2Over10TS = new TH1F("h1D_hcalnoise_maxE2Over10TS","", 100,0,1);
    TH1F *h1D_hcalnoise_maxE2Over10TS_jet = new TH1F("h1D_hcalnoise_maxE2Over10TS_jet","", 100,0,1);
    h1D_hcalnoise_maxE2Over10TS_vec.push_back(h1D_hcalnoise_maxE2Over10TS);
    h1D_hcalnoise_maxE2Over10TS_vec.push_back(h1D_hcalnoise_maxE2Over10TS_jet);
    TH1F *h1D_hcalnoise_maxE2TS = new TH1F("h1D_hcalnoise_maxE2TS","", 100,0,5000);
    TH1F *h1D_hcalnoise_maxE2TS_jet = new TH1F("h1D_hcalnoise_maxE2TS_jet","", 100,0,5000);
    h1D_hcalnoise_maxE2TS_vec.push_back(h1D_hcalnoise_maxE2TS);
    h1D_hcalnoise_maxE2TS_vec.push_back(h1D_hcalnoise_maxE2TS_jet);
    TH1F *h1D_hcalnoise_min10GeVHitTime = new TH1F("h1D_hcalnoise_min10GeVHitTime","", 100,-1,20);
    TH1F *h1D_hcalnoise_min10GeVHitTime_jet = new TH1F("h1D_hcalnoise_min10GeVHitTime_jet","", 100,-1,20);
    h1D_hcalnoise_min10GeVHitTime_vec.push_back(h1D_hcalnoise_min10GeVHitTime);
    h1D_hcalnoise_min10GeVHitTime_vec.push_back(h1D_hcalnoise_min10GeVHitTime_jet);
    TH1F *h1D_hcalnoise_min25GeVHitTime = new TH1F("h1D_hcalnoise_min25GeVHitTime","", 100,-1,20);
    TH1F *h1D_hcalnoise_min25GeVHitTime_jet = new TH1F("h1D_hcalnoise_min25GeVHitTime_jet","", 100,-1,20);
    h1D_hcalnoise_min25GeVHitTime_vec.push_back(h1D_hcalnoise_min25GeVHitTime);
    h1D_hcalnoise_min25GeVHitTime_vec.push_back(h1D_hcalnoise_min25GeVHitTime_jet);
    TH1F *h1D_hcalnoise_minE10TS = new TH1F("h1D_hcalnoise_minE10TS","", 100,0,5000);
    TH1F *h1D_hcalnoise_minE10TS_jet = new TH1F("h1D_hcalnoise_minE10TS_jet","", 100,0,5000);
    h1D_hcalnoise_minE10TS_vec.push_back(h1D_hcalnoise_minE10TS);
    h1D_hcalnoise_minE10TS_vec.push_back(h1D_hcalnoise_minE10TS_jet);
    TH1F *h1D_hcalnoise_minE2Over10TS = new TH1F("h1D_hcalnoise_minE2Over10TS","", 100,0,3);
    TH1F *h1D_hcalnoise_minE2Over10TS_jet = new TH1F("h1D_hcalnoise_minE2Over10TS_jet","", 100,0,3);
    h1D_hcalnoise_minE2Over10TS_vec.push_back(h1D_hcalnoise_minE2Over10TS);
    h1D_hcalnoise_minE2Over10TS_vec.push_back(h1D_hcalnoise_minE2Over10TS_jet);
    TH1F *h1D_hcalnoise_minE2TS = new TH1F("h1D_hcalnoise_minE2TS","", 100,0,5000);
    TH1F *h1D_hcalnoise_minE2TS_jet = new TH1F("h1D_hcalnoise_minE2TS_jet","", 100,0,5000);
    h1D_hcalnoise_minE2TS_vec.push_back(h1D_hcalnoise_minE2TS);
    h1D_hcalnoise_minE2TS_vec.push_back(h1D_hcalnoise_minE2TS_jet);
    TH1F *h1D_hcalnoise_minHPDEMF = new TH1F("h1D_hcalnoise_minHPDEMF","", 100,0,1.1);
    TH1F *h1D_hcalnoise_minHPDEMF_jet = new TH1F("h1D_hcalnoise_minHPDEMF_jet","", 100,0,1.1);
    h1D_hcalnoise_minHPDEMF_vec.push_back(h1D_hcalnoise_minHPDEMF);
    h1D_hcalnoise_minHPDEMF_vec.push_back(h1D_hcalnoise_minHPDEMF_jet);
    TH1F *h1D_hcalnoise_minRBXEMF = new TH1F("h1D_hcalnoise_minRBXEMF","", 100,0,1.1);
    TH1F *h1D_hcalnoise_minRBXEMF_jet = new TH1F("h1D_hcalnoise_minRBXEMF_jet","", 100,0,1.1);
    h1D_hcalnoise_minRBXEMF_vec.push_back(h1D_hcalnoise_minRBXEMF);
    h1D_hcalnoise_minRBXEMF_vec.push_back(h1D_hcalnoise_minRBXEMF_jet);
    TH1F *h1D_hcalnoise_rms10GeVHitTime = new TH1F("h1D_hcalnoise_rms10GeVHitTime","", 100,0,1080);
    TH1F *h1D_hcalnoise_rms10GeVHitTime_jet = new TH1F("h1D_hcalnoise_rms10GeVHitTime_jet","", 100,0,1080);
    h1D_hcalnoise_rms10GeVHitTime_vec.push_back(h1D_hcalnoise_rms10GeVHitTime);
    h1D_hcalnoise_rms10GeVHitTime_vec.push_back(h1D_hcalnoise_rms10GeVHitTime_jet);
    TH1F *h1D_hcalnoise_rms25GeVHitTime = new TH1F("h1D_hcalnoise_rms25GeVHitTime","", 100,0,1080);
    TH1F *h1D_hcalnoise_rms25GeVHitTime_jet = new TH1F("h1D_hcalnoise_rms25GeVHitTime_jet","", 100,0,1080);
    h1D_hcalnoise_rms25GeVHitTime_vec.push_back(h1D_hcalnoise_rms25GeVHitTime);
    h1D_hcalnoise_rms25GeVHitTime_vec.push_back(h1D_hcalnoise_rms25GeVHitTime_jet);
    TH1F *h1D_hcalnoise_spikeNoiseSumE = new TH1F("h1D_hcalnoise_spikeNoiseSumE","", 100,0,6300);
    TH1F *h1D_hcalnoise_spikeNoiseSumE_jet = new TH1F("h1D_hcalnoise_spikeNoiseSumE_jet","", 100,0,6300);
    h1D_hcalnoise_spikeNoiseSumE_vec.push_back(h1D_hcalnoise_spikeNoiseSumE);
    h1D_hcalnoise_spikeNoiseSumE_vec.push_back(h1D_hcalnoise_spikeNoiseSumE_jet);
    TH1F *h1D_hcalnoise_spikeNoiseSumEt = new TH1F("h1D_hcalnoise_spikeNoiseSumEt","", 100,0,6000);
    TH1F *h1D_hcalnoise_spikeNoiseSumEt_jet = new TH1F("h1D_hcalnoise_spikeNoiseSumEt_jet","", 100,0,6000);
    h1D_hcalnoise_spikeNoiseSumEt_vec.push_back(h1D_hcalnoise_spikeNoiseSumEt);
    h1D_hcalnoise_spikeNoiseSumEt_vec.push_back(h1D_hcalnoise_spikeNoiseSumEt_jet);
    TH1F *h1D_hcalnoise_triangleNoiseSumE = new TH1F("h1D_hcalnoise_triangleNoiseSumE","", 100,0,4050);
    TH1F *h1D_hcalnoise_triangleNoiseSumE_jet = new TH1F("h1D_hcalnoise_triangleNoiseSumE_jet","", 100,0,4050);
    h1D_hcalnoise_triangleNoiseSumE_vec.push_back(h1D_hcalnoise_triangleNoiseSumE);
    h1D_hcalnoise_triangleNoiseSumE_vec.push_back(h1D_hcalnoise_triangleNoiseSumE_jet);
    TH1F *h1D_hcalnoise_triangleNoiseSumEt = new TH1F("h1D_hcalnoise_triangleNoiseSumEt","", 100,0,2100);
    TH1F *h1D_hcalnoise_triangleNoiseSumEt_jet = new TH1F("h1D_hcalnoise_triangleNoiseSumEt_jet","", 100,0,2100);
    h1D_hcalnoise_triangleNoiseSumEt_vec.push_back(h1D_hcalnoise_triangleNoiseSumEt);
    h1D_hcalnoise_triangleNoiseSumEt_vec.push_back(h1D_hcalnoise_triangleNoiseSumEt_jet);
    TH1F *h1D_hcalnoise_GetRecHitCount = new TH1F("h1D_hcalnoise_GetRecHitCount","", 107,685,2290);
    TH1F *h1D_hcalnoise_GetRecHitCount_jet = new TH1F("h1D_hcalnoise_GetRecHitCount_jet","", 107,685,2290);
    h1D_hcalnoise_GetRecHitCount_vec.push_back(h1D_hcalnoise_GetRecHitCount);
    h1D_hcalnoise_GetRecHitCount_vec.push_back(h1D_hcalnoise_GetRecHitCount_jet);
    TH1F *h1D_hcalnoise_GetRecHitCount15 = new TH1F("h1D_hcalnoise_GetRecHitCount15","", 114,0,684);
    TH1F *h1D_hcalnoise_GetRecHitCount15_jet = new TH1F("h1D_hcalnoise_GetRecHitCount15_jet","", 114,0,684);
    h1D_hcalnoise_GetRecHitCount15_vec.push_back(h1D_hcalnoise_GetRecHitCount15);
    h1D_hcalnoise_GetRecHitCount15_vec.push_back(h1D_hcalnoise_GetRecHitCount15_jet);
    TH1F *h1D_hcalnoise_hbheIsoNoiseFilter = new TH1F("h1D_hcalnoise_hbheIsoNoiseFilter","", 2,0,2);
    TH1F *h1D_hcalnoise_hbheIsoNoiseFilter_jet = new TH1F("h1D_hcalnoise_hbheIsoNoiseFilter_jet","", 2,0,2);
    h1D_hcalnoise_hbheIsoNoiseFilter_vec.push_back(h1D_hcalnoise_hbheIsoNoiseFilter);
    h1D_hcalnoise_hbheIsoNoiseFilter_vec.push_back(h1D_hcalnoise_hbheIsoNoiseFilter_jet);
    TH1F *h1D_hcalnoise_maxHPDHits = new TH1F("h1D_hcalnoise_maxHPDHits","", 19,0,19);
    TH1F *h1D_hcalnoise_maxHPDHits_jet = new TH1F("h1D_hcalnoise_maxHPDHits_jet","", 19,0,19);
    h1D_hcalnoise_maxHPDHits_vec.push_back(h1D_hcalnoise_maxHPDHits);
    h1D_hcalnoise_maxHPDHits_vec.push_back(h1D_hcalnoise_maxHPDHits_jet);
    TH1F *h1D_hcalnoise_maxHPDNoOtherHits = new TH1F("h1D_hcalnoise_maxHPDNoOtherHits","", 19,0,19);
    TH1F *h1D_hcalnoise_maxHPDNoOtherHits_jet = new TH1F("h1D_hcalnoise_maxHPDNoOtherHits_jet","", 19,0,19);
    h1D_hcalnoise_maxHPDNoOtherHits_vec.push_back(h1D_hcalnoise_maxHPDNoOtherHits);
    h1D_hcalnoise_maxHPDNoOtherHits_vec.push_back(h1D_hcalnoise_maxHPDNoOtherHits_jet);
    TH1F *h1D_hcalnoise_maxRBXHits = new TH1F("h1D_hcalnoise_maxRBXHits","", 76,0,76);
    TH1F *h1D_hcalnoise_maxRBXHits_jet = new TH1F("h1D_hcalnoise_maxRBXHits_jet","", 76,0,76);
    h1D_hcalnoise_maxRBXHits_vec.push_back(h1D_hcalnoise_maxRBXHits);
    h1D_hcalnoise_maxRBXHits_vec.push_back(h1D_hcalnoise_maxRBXHits_jet);
    TH1F *h1D_hcalnoise_maxZeros = new TH1F("h1D_hcalnoise_maxZeros","", 40,0,40);
    TH1F *h1D_hcalnoise_maxZeros_jet = new TH1F("h1D_hcalnoise_maxZeros_jet","", 40,0,40);
    h1D_hcalnoise_maxZeros_vec.push_back(h1D_hcalnoise_maxZeros);
    h1D_hcalnoise_maxZeros_vec.push_back(h1D_hcalnoise_maxZeros_jet);
    TH1F *h1D_hcalnoise_noiseFilterStatus = new TH1F("h1D_hcalnoise_noiseFilterStatus","", 101,0,72720);
    TH1F *h1D_hcalnoise_noiseFilterStatus_jet = new TH1F("h1D_hcalnoise_noiseFilterStatus_jet","", 101,0,72720);
    h1D_hcalnoise_noiseFilterStatus_vec.push_back(h1D_hcalnoise_noiseFilterStatus);
    h1D_hcalnoise_noiseFilterStatus_vec.push_back(h1D_hcalnoise_noiseFilterStatus_jet);
    TH1F *h1D_hcalnoise_noiseType = new TH1F("h1D_hcalnoise_noiseType","", 4,0,4);
    TH1F *h1D_hcalnoise_noiseType_jet = new TH1F("h1D_hcalnoise_noiseType_jet","", 4,0,4);
    h1D_hcalnoise_noiseType_vec.push_back(h1D_hcalnoise_noiseType);
    h1D_hcalnoise_noiseType_vec.push_back(h1D_hcalnoise_noiseType_jet);
    TH1F *h1D_hcalnoise_num10GeVHits = new TH1F("h1D_hcalnoise_num10GeVHits","", 45,0,45);
    TH1F *h1D_hcalnoise_num10GeVHits_jet = new TH1F("h1D_hcalnoise_num10GeVHits_jet","", 45,0,45);
    h1D_hcalnoise_num10GeVHits_vec.push_back(h1D_hcalnoise_num10GeVHits);
    h1D_hcalnoise_num10GeVHits_vec.push_back(h1D_hcalnoise_num10GeVHits_jet);
    TH1F *h1D_hcalnoise_num25GeVHits = new TH1F("h1D_hcalnoise_num25GeVHits","", 20,0,20);
    TH1F *h1D_hcalnoise_num25GeVHits_jet = new TH1F("h1D_hcalnoise_num25GeVHits_jet","", 20,0,20);
    h1D_hcalnoise_num25GeVHits_vec.push_back(h1D_hcalnoise_num25GeVHits);
    h1D_hcalnoise_num25GeVHits_vec.push_back(h1D_hcalnoise_num25GeVHits_jet);
    TH1F *h1D_hcalnoise_numFlatNoiseChannels = new TH1F("h1D_hcalnoise_numFlatNoiseChannels","", 72,0,72);
    TH1F *h1D_hcalnoise_numFlatNoiseChannels_jet = new TH1F("h1D_hcalnoise_numFlatNoiseChannels_jet","", 72,0,72);
    h1D_hcalnoise_numFlatNoiseChannels_vec.push_back(h1D_hcalnoise_numFlatNoiseChannels);
    h1D_hcalnoise_numFlatNoiseChannels_vec.push_back(h1D_hcalnoise_numFlatNoiseChannels_jet);
    TH1F *h1D_hcalnoise_numIsolatedNoiseChannels = new TH1F("h1D_hcalnoise_numIsolatedNoiseChannels","", 30,0,30);
    TH1F *h1D_hcalnoise_numIsolatedNoiseChannels_jet = new TH1F("h1D_hcalnoise_numIsolatedNoiseChannels_jet","", 30,0,30);
    h1D_hcalnoise_numIsolatedNoiseChannels_vec.push_back(h1D_hcalnoise_numIsolatedNoiseChannels);
    h1D_hcalnoise_numIsolatedNoiseChannels_vec.push_back(h1D_hcalnoise_numIsolatedNoiseChannels_jet);
    TH1F *h1D_hcalnoise_numProblematicRBXs = new TH1F("h1D_hcalnoise_numProblematicRBXs","", 4,70,74);
    TH1F *h1D_hcalnoise_numProblematicRBXs_jet = new TH1F("h1D_hcalnoise_numProblematicRBXs_jet","", 4,70,74);
    h1D_hcalnoise_numProblematicRBXs_vec.push_back(h1D_hcalnoise_numProblematicRBXs);
    h1D_hcalnoise_numProblematicRBXs_vec.push_back(h1D_hcalnoise_numProblematicRBXs_jet);
    TH1F *h1D_hcalnoise_numSpikeNoiseChannels = new TH1F("h1D_hcalnoise_numSpikeNoiseChannels","", 17,0,17);
    TH1F *h1D_hcalnoise_numSpikeNoiseChannels_jet = new TH1F("h1D_hcalnoise_numSpikeNoiseChannels_jet","", 17,0,17);
    h1D_hcalnoise_numSpikeNoiseChannels_vec.push_back(h1D_hcalnoise_numSpikeNoiseChannels);
    h1D_hcalnoise_numSpikeNoiseChannels_vec.push_back(h1D_hcalnoise_numSpikeNoiseChannels_jet);
    TH1F *h1D_hcalnoise_numTS4TS5NoiseChannels = new TH1F("h1D_hcalnoise_numTS4TS5NoiseChannels","", 20,0,20);
    TH1F *h1D_hcalnoise_numTS4TS5NoiseChannels_jet = new TH1F("h1D_hcalnoise_numTS4TS5NoiseChannels_jet","", 20,0,20);
    h1D_hcalnoise_numTS4TS5NoiseChannels_vec.push_back(h1D_hcalnoise_numTS4TS5NoiseChannels);
    h1D_hcalnoise_numTS4TS5NoiseChannels_vec.push_back(h1D_hcalnoise_numTS4TS5NoiseChannels_jet);
    TH1F *h1D_hcalnoise_numTriangleNoiseChannels = new TH1F("h1D_hcalnoise_numTriangleNoiseChannels","", 4,0,4);
    TH1F *h1D_hcalnoise_numTriangleNoiseChannels_jet = new TH1F("h1D_hcalnoise_numTriangleNoiseChannels_jet","", 4,0,4);
    h1D_hcalnoise_numTriangleNoiseChannels_vec.push_back(h1D_hcalnoise_numTriangleNoiseChannels);
    h1D_hcalnoise_numTriangleNoiseChannels_vec.push_back(h1D_hcalnoise_numTriangleNoiseChannels_jet);
    TH1F *h1D_hcalnoise_passHighLevelNoiseFilter = new TH1F("h1D_hcalnoise_passHighLevelNoiseFilter","", 2,0,2);
    TH1F *h1D_hcalnoise_passHighLevelNoiseFilter_jet = new TH1F("h1D_hcalnoise_passHighLevelNoiseFilter_jet","", 2,0,2);
    h1D_hcalnoise_passHighLevelNoiseFilter_vec.push_back(h1D_hcalnoise_passHighLevelNoiseFilter);
    h1D_hcalnoise_passHighLevelNoiseFilter_vec.push_back(h1D_hcalnoise_passHighLevelNoiseFilter_jet);
    TH1F *h1D_hcalnoise_passLooseNoiseFilter = new TH1F("h1D_hcalnoise_passLooseNoiseFilter","", 2,0,2);
    TH1F *h1D_hcalnoise_passLooseNoiseFilter_jet = new TH1F("h1D_hcalnoise_passLooseNoiseFilter_jet","", 2,0,2);
    h1D_hcalnoise_passLooseNoiseFilter_vec.push_back(h1D_hcalnoise_passLooseNoiseFilter);
    h1D_hcalnoise_passLooseNoiseFilter_vec.push_back(h1D_hcalnoise_passLooseNoiseFilter_jet);
    TH1F *h1D_hcalnoise_passTightNoiseFilter = new TH1F("h1D_hcalnoise_passTightNoiseFilter","", 2,0,2);
    TH1F *h1D_hcalnoise_passTightNoiseFilter_jet = new TH1F("h1D_hcalnoise_passTightNoiseFilter_jet","", 2,0,2);
    h1D_hcalnoise_passTightNoiseFilter_vec.push_back(h1D_hcalnoise_passTightNoiseFilter);
    h1D_hcalnoise_passTightNoiseFilter_vec.push_back(h1D_hcalnoise_passTightNoiseFilter_jet);

    TH1F *h1D_twrs_numBadEcalCells = new TH1F("h1D_twrs_numBadEcalCells","",100,0,30);
    TH1F *h1D_twrs_numBadEcalCells_jet = new TH1F("h1D_twrs_numBadEcalCells_jet","",100,0,30);
    h1D_twrs_numBadEcalCells_vec.push_back(h1D_twrs_numBadEcalCells);
    h1D_twrs_numBadEcalCells_vec.push_back(h1D_twrs_numBadEcalCells_jet);
    TH1F *h1D_twrs_numRecoveredEcalCells = new TH1F("h1D_twrs_numRecoveredEcalCells","",100,0,30);
    TH1F *h1D_twrs_numRecoveredEcalCells_jet = new TH1F("h1D_twrs_numRecoveredEcalCells_jet","",100,0,30);
    h1D_twrs_numRecoveredEcalCells_vec.push_back(h1D_twrs_numRecoveredEcalCells);
    h1D_twrs_numRecoveredEcalCells_vec.push_back(h1D_twrs_numRecoveredEcalCells_jet);
    TH1F *h1D_twrs_numProblematicEcalCells = new TH1F("h1D_twrs_numProblematicEcalCells","",100,0,30);
    TH1F *h1D_twrs_numProblematicEcalCells_jet = new TH1F("h1D_twrs_numProblematicEcalCells_jet","",100,0,30);
    h1D_twrs_numProblematicEcalCells_vec.push_back(h1D_twrs_numProblematicEcalCells);
    h1D_twrs_numProblematicEcalCells_vec.push_back(h1D_twrs_numProblematicEcalCells_jet);
    TH1F *h1D_twrs_numBadHcalCells = new TH1F("h1D_twrs_numBadHcalCells","",100,0,30);
    TH1F *h1D_twrs_numBadHcalCells_jet = new TH1F("h1D_twrs_numBadHcalCells_jet","",100,0,30);
    h1D_twrs_numBadHcalCells_vec.push_back(h1D_twrs_numBadHcalCells);
    h1D_twrs_numBadHcalCells_vec.push_back(h1D_twrs_numBadHcalCells_jet);
    TH1F *h1D_twrs_numRecoveredHcalCells = new TH1F("h1D_twrs_numRecoveredHcalCells","",100,0,30);
    TH1F *h1D_twrs_numRecoveredHcalCells_jet = new TH1F("h1D_twrs_numRecoveredHcalCells_jet","",100,0,30);
    h1D_twrs_numRecoveredHcalCells_vec.push_back(h1D_twrs_numRecoveredHcalCells);
    h1D_twrs_numRecoveredHcalCells_vec.push_back(h1D_twrs_numRecoveredHcalCells_jet);
    TH1F *h1D_twrs_numProblematicHcalCells = new TH1F("h1D_twrs_numProblematicHcalCells","",100,0,30);
    TH1F *h1D_twrs_numProblematicHcalCells_jet = new TH1F("h1D_twrs_numProblematicHcalCells_jet","",100,0,30);
    h1D_twrs_numProblematicHcalCells_vec.push_back(h1D_twrs_numProblematicHcalCells);
    h1D_twrs_numProblematicHcalCells_vec.push_back(h1D_twrs_numProblematicHcalCells_jet);
    TH1F *h1D_twrs_numCrystals = new TH1F("h1D_twrs_numCrystals","",100,0,30);
    TH1F *h1D_twrs_numCrystals_jet = new TH1F("h1D_twrs_numCrystals_jet","",100,0,30);
    h1D_twrs_numCrystals_vec.push_back(h1D_twrs_numCrystals);
    h1D_twrs_numCrystals_vec.push_back(h1D_twrs_numCrystals_jet);

    TH2F *h2D_twrs_numBadEcalCells = new TH2F("h2D_twrs_numBadEcalCells"                 , "" , 50, -maxEta,maxEta, 50, -3.15,3.15);
    TH2F *h2D_twrs_numRecoveredEcalCells = new TH2F("h2D_twrs_numRecoveredEcalCells"     , "" , 50, -maxEta,maxEta, 50, -3.15,3.15);
    TH2F *h2D_twrs_numProblematicEcalCells = new TH2F("h2D_twrs_numProblematicEcalCells" , "" , 50, -maxEta,maxEta, 50, -3.15,3.15);
    TH2F *h2D_twrs_numBadHcalCells = new TH2F("h2D_twrs_numBadHcalCells"                 , "" , 50, -maxEta,maxEta, 50, -3.15,3.15);
    TH2F *h2D_twrs_numRecoveredHcalCells = new TH2F("h2D_twrs_numRecoveredHcalCells"     , "" , 50, -maxEta,maxEta, 50, -3.15,3.15);
    TH2F *h2D_twrs_numProblematicHcalCells = new TH2F("h2D_twrs_numProblematicHcalCells" , "" , 50, -maxEta,maxEta, 50, -3.15,3.15);
    TH2F *h2D_twrs_numCrystals = new TH2F("h2D_twrs_numCrystals"                         , "" , 50, -maxEta,maxEta, 50, -3.15,3.15);

    // max length of bad hcal cells
    std::vector<std::string> titlesBadCells = {"match", "no match", "either"};
    std::vector<TH1F*> h1D_lengthBadCells_vec;
    TH1F *h1D_lengthBadCells_match = new TH1F("h1D_lengthBadCells_match","",30,0,30);
    TH1F *h1D_lengthBadCells_nomatch = new TH1F("h1D_lengthBadCells_nomatch","",30,0,30);
    TH1F *h1D_lengthBadCells_either = new TH1F("h1D_lengthBadCells_either","",30,0,30);
    h1D_lengthBadCells_vec.push_back(h1D_lengthBadCells_match);
    h1D_lengthBadCells_vec.push_back(h1D_lengthBadCells_nomatch);
    h1D_lengthBadCells_vec.push_back(h1D_lengthBadCells_either);


    const char* json_file = "Run2015BGoldenPlus_v2.txt";
    // const char* json_file = "Run2015BGolden.txt";
    set_goodrun_file(json_file);

    std::vector<int> passFilters = { 0, 0, 0, 0, 0, 0, 0, 0 };

    unsigned int nEventsTotal = 0;
    unsigned int nEventsChain = chain->GetEntries();
    unsigned int nEventsFiltered = 0;

    TObjArray *listOfFiles = chain->GetListOfFiles();
    TIter fileIter(listOfFiles);
    TFile *currentFile = 0;

    // File Loop
    int prevRun = -1; int prevLumi = -1;
    while ( (currentFile = (TFile*)fileIter.Next()) ) {

        std::cout << nEventsFiltered << " " << currentFile->GetTitle() << std::endl;

        // Get File Content
        TFile *file = new TFile( currentFile->GetTitle() );
        TTree *tree = (TTree*)file->Get("Events");
        TTreeCache::SetLearnEntries(10);
        tree->SetCacheSize(128*1024*1024);
        cms3.Init(tree);

        bool fast = false;
        int iCut = 0;

        // Loop over Events in current file
        if( nEventsTotal >= nEventsChain ) continue;
        unsigned int nEventsTree = tree->GetEntriesFast();

        for( unsigned int event = 0; event < nEventsTree; ++event) {

            // Get Event Content
            if( nEventsTotal >= nEventsChain ) continue;
            tree->LoadTree(event);
            cms3.GetEntry(event);
            ++nEventsTotal;
            CMS3::progress( nEventsTotal, nEventsChain );

            // Analysis Code
            float pfCaloMet = pfCaloMet_met();
            float pfCaloMetPhi = pfCaloMet_metPhi();

            float pfMet = pfMet_met();
            float pfMetPhi = pfMet_metPhi();

            float pfChMet = pfChMet_met();
            float pfChMetPhi = pfChMet_metPhi();

            // float caloMet = evt_met();
            // float caloMetPhi = evt_metPhi();
            float caloMet = evt_metMuonCorr();
            float caloMetPhi = evt_metMuonCorrPhi();

            float pfClusterMet = pfcluster_met();
            float pfClusterMetPhi = pfcluster_metphi();

            iCut = 0;

            // use golden json file 
            if ( evt_isRealData() && !goodrun(evt_run(), evt_lumiBlock()) ) continue;


            // if ( evt_event() != 17498195 ) continue;
            // if ( evt_trackingFailureFilter() && evt_cscTightHaloFilter() && hbheIsoNoiseFilter() && evt_EcalDeadCellTriggerPrimitiveFilter() && evt_eeBadScFilter() && hbheNoiseFilter() ) {
            //     // passed the filters
            // } else {
            //     debug << evt_run() << ":" << evt_lumiBlock() << ":" << evt_event() << endl;
            //     // didn't pass
            // }

            int maxIPhiHad = -1, maxIEtaHad = -1;
            float maxHadEnergy = -1;
            vector<int> badCellsPerPhiStrip(150,0); // there shouldn't be more than 150 iphi vals...
            for(int i = 0; i < twrs_eta().size(); i++) {
                float eta = twrs_etacorr().at(i);
                float phi = twrs_phicorr().at(i);
                int ieta = twrs_ieta().at(i);
                int iphi = twrs_iphi().at(i);
                int numProbHcalCells = twrs_numProblematicHcalCells().at(i);
                if( abs(eta) > 3.0) continue; // don't deal with HF

                if(twrs_hadEnergy().at(i) > maxHadEnergy) {
                    maxIPhiHad = iphi;
                    maxIEtaHad = ieta;
                    maxHadEnergy = twrs_hadEnergy().at(i);
                }
                if(twrs_numProblematicHcalCells().at(i) > 0) {
                    badCellsPerPhiStrip[iphi] += numProbHcalCells;
                }
            }

            int maxIPhiBad = -1;
            int maxBadCells = -1;
            for(int iphi = 0; iphi < badCellsPerPhiStrip.size(); iphi++) {
                if(badCellsPerPhiStrip[iphi] > maxBadCells) {
                    maxBadCells = badCellsPerPhiStrip[iphi];
                    maxIPhiBad = iphi;
                }
            }

            // at this point, if maxIPhiBad != maxIPhiHad, then it's not a phi strip event
            vector<int> badCellsAlongWorstPhiStrip(150,0); // there shouldn't be more than 150 ieta vals...
            for(int i = 0; i < twrs_eta().size(); i++) {
                int ieta = twrs_ieta().at(i);
                int iphi = twrs_iphi().at(i);
                if( abs(twrs_etacorr().at(i)) > 3.0) continue; // don't deal with HF
                if( iphi != maxIPhiBad ) continue;


                int numProbHcalCells = twrs_numProblematicHcalCells().at(i);

                if(ieta > 0) ieta--; //ieta is never 0, so there will be a gap between negative ieta and positive ieta
                badCellsAlongWorstPhiStrip.at(ieta+50) = numProbHcalCells;

            }
            // find length of longest contiguous segment of bad cells along the worst phi strip
            int maxLengthBad = 0, maxEndingHere = 0;
            for(int ieta = 0; ieta < badCellsAlongWorstPhiStrip.size(); ieta++) {
                maxEndingHere += badCellsAlongWorstPhiStrip.at(ieta);
                if(maxLengthBad < maxEndingHere) maxLengthBad = maxEndingHere;
            }
            // maxIPhiBad maxIPhiHad maxLengthBad
            // std::cout << " maxIPhiBad: " << maxIPhiBad << " maxIPhiHad: " << maxIPhiHad << " maxLengthBad: " << maxLengthBad << std::endl;
            if(maxIPhiHad == maxIPhiBad) {
                // want to compare distribution of bad cell length when we match
                // the two max phi strips and when we don't
                h1D_lengthBadCells_match->Fill(maxLengthBad);
            } else {
                h1D_lengthBadCells_nomatch->Fill(maxLengthBad);
            }
            h1D_lengthBadCells_either->Fill(maxLengthBad);


            h1D_pfCaloMet->Fill(pfCaloMet);
            h1D_pfMet->Fill(pfMet);
            h1D_caloMet->Fill(caloMet);
            h1D_pfClusterMet->Fill(pfClusterMet);
            h1D_pfChMet->Fill(pfChMet);

            h1D_caloMetPhi->Fill(caloMetPhi);
            h1D_pfMetPhi->Fill(pfMetPhi);

            addRunToMap(evt_run());
            h1D_effbyrun->Fill(runToBinMap[evt_run()]);
            h1D_maxZeros->Fill(hcalnoise_maxZeros());

            int iPass = 0;
            passFilters.at(iPass)++; iPass++;


            if ( evt_trackingFailureFilter() ) {
                h1D_caloMet_filt_track->Fill(caloMet);
                passFilters.at(iPass)++;
            }
            iPass++;
            if ( evt_cscTightHaloFilter() ) {
                h1D_caloMet_filt_halo->Fill(caloMet);
                passFilters.at(iPass)++;
            }
            iPass++;
            if ( hbheIsoNoiseFilter() ) {
                h1D_caloMet_filt_isonoise->Fill(caloMet);
                passFilters.at(iPass)++;
            }
            iPass++;
            if ( evt_hbheFilterRun1() ) {
                h1D_caloMet_filt_hbherun1->Fill(caloMet);
                passFilters.at(iPass)++;
            }
            iPass++;
            if ( evt_EcalDeadCellTriggerPrimitiveFilter() ) {
                h1D_caloMet_filt_ecalcell->Fill(caloMet);
                passFilters.at(iPass)++;
            }
            iPass++;
            if ( evt_eeBadScFilter() ) {
                h1D_caloMet_filt_eebadsc->Fill(caloMet);
                passFilters.at(iPass)++;
            }
            iPass++;
            // if ( hcalnoise_passTightNoiseFilter() ) {
            if ( hbheNoiseFilter() ) { // IGNORE MAXZEROS
                h1D_caloMet_filt_tightnoise->Fill(caloMet);
                passFilters.at(iPass)++;

            }

            if( !fast ) {
                float caloMetNewX = 0;
                float caloMetNewY = 0;
                for(int i = 0; i < twrs_eta().size(); i++) {

                    float twrEta = twrs_etacorr().at(i);
                    float twrPhi = twrs_phicorr().at(i);
                    if(twrs_emEtcorr().at(i) + twrs_hadEtcorr().at(i) > 0.3) {
                        caloMetNewX -= (twrs_hadEtcorr().at(i) + twrs_emEtcorr().at(i))*cos(twrPhi);
                        caloMetNewY -= (twrs_hadEtcorr().at(i) + twrs_emEtcorr().at(i))*sin(twrPhi);
                    }

                    h2D_towers_etaphi->Fill(twrEta, twrPhi);
                    h2D_towers_etaphi_em->Fill(twrEta, twrPhi, twrs_emEnergy().at(i));
                    h2D_towers_etaphi_had->Fill(twrEta, twrPhi, twrs_hadEnergy().at(i));
                    h2D_towers_etaphi_outer->Fill(twrEta, twrPhi, twrs_outerEnergy().at(i));

                    h1D_towers_phi->Fill(twrPhi);
                    h1D_towers_phi_em->Fill(twrPhi, twrs_emEnergy().at(i));
                    h1D_towers_phi_had->Fill(twrPhi, twrs_hadEnergy().at(i));
                    h1D_towers_phi_outer->Fill(twrPhi, twrs_outerEnergy().at(i));

                }   

                for(int i = 0; i < pfcluster_eta().size(); i++) {
                    h2D_pfclusters_etaphi->Fill(pfcluster_eta().at(i), pfcluster_phi().at(i));
                    h1D_pfclusters_phi->Fill(pfcluster_phi().at(i));
                }
                for(int i = 0; i < calojets_eta().size(); i++) {
                    h2D_calojets_etaphi->Fill(calojets_eta().at(i), calojets_phi().at(i));
                    h1D_calojets_phi->Fill(calojets_phi().at(i));
                }

                float caloMetNew = sqrt(caloMetNewX*caloMetNewX + caloMetNewY*caloMetNewY);
                float caloMetPhiNew = atan2(caloMetNewY,caloMetNewX);
                h1D_caloMetNew->Fill(caloMetNew);
                h1D_caloMetPhiNew->Fill(caloMetPhiNew);

            }

            float leadingJetPhi = 999.0;
            float leadingJetPt = -999.0;
            for(int iJet = 0; iJet < calojets_pt().size(); iJet++) {
                if (calojets_pt().at(iJet) > leadingJetPt) {
                    leadingJetPt = calojets_pt().at(iJet);
                    leadingJetPhi = calojets_phi().at(iJet);
                }
            }

            float pfJetIdx = -1;
            float leadingPFJetPt = -1;
            for(int iJet = 0; iJet < pfjets_p4().size(); iJet++) {
                if (pfjets_p4().at(iJet).pt() > leadingPFJetPt) {
                    leadingPFJetPt = pfjets_p4().at(iJet).pt();
                    pfJetIdx = iJet;
                }
            }
            if(leadingPFJetPt > -1) {
                h1D_leadingJet_chf->Fill(pfjets_chargedHadronE()[pfJetIdx] / (pfjets_undoJEC().at(pfJetIdx)*pfjets_p4()[pfJetIdx].energy()));
                h1D_leadingJet_nhf->Fill(pfjets_neutralHadronE()[pfJetIdx] / (pfjets_undoJEC().at(pfJetIdx)*pfjets_p4()[pfJetIdx].energy()));
                h1D_leadingJet_cef->Fill(pfjets_chargedEmE()[pfJetIdx] / (pfjets_undoJEC().at(pfJetIdx)*pfjets_p4()[pfJetIdx].energy()));
                h1D_leadingJet_nef->Fill(pfjets_neutralEmE()[pfJetIdx] / (pfjets_undoJEC().at(pfJetIdx)*pfjets_p4()[pfJetIdx].energy()));
                h1D_leadingJet_cm->Fill(pfjets_chargedMultiplicity()[pfJetIdx]);
            }

            for(int iDet = 0; iDet < 32; iDet++) {
                if( evt_detectorStatus() & (1 << iDet) ) h1D_detectorStatus->Fill(iDet);
            }

            float dPhiCaloMet = deltaPhi(leadingJetPhi, caloMetPhi);
            if(dPhiCaloMet < M_PI) h1D_jetCaloMetPhi->Fill(dPhiCaloMet);

            if( !(hcalnoise_maxHPDHits()>=17) &&
                    !(hcalnoise_maxHPDNoOtherHits()>=10) &&
                    !(hcalnoise_numIsolatedNoiseChannels()>=10) &&
                    !(hcalnoise_isolatedNoiseSumE()>=50.0) )
                h1D_nm1_isolatedNoiseSumEt->Fill(hcalnoise_isolatedNoiseSumEt());

            if( !(hcalnoise_maxHPDHits()>=17) &&
                    !(hcalnoise_maxHPDNoOtherHits()>=10) &&
                    !(hcalnoise_numIsolatedNoiseChannels()>=10) &&
                    !(hcalnoise_isolatedNoiseSumEt()>=25.0) )
                h1D_nm1_isolatedNoiseSumE->Fill(hcalnoise_isolatedNoiseSumE());

            if( !(hcalnoise_maxHPDHits()>=17) &&
                    !(hcalnoise_maxHPDNoOtherHits()>=10) &&
                    !(hcalnoise_isolatedNoiseSumE()>=50.0) &&
                    !(hcalnoise_isolatedNoiseSumEt()>=25.0) ) 
                h1D_nm1_numIsolatedNoiseChannels->Fill(hcalnoise_numIsolatedNoiseChannels());

            if( !(hcalnoise_maxHPDHits()>=17) &&
                    !(hcalnoise_numIsolatedNoiseChannels()>=10) &&
                    !(hcalnoise_isolatedNoiseSumE()>=50.0) &&
                    !(hcalnoise_isolatedNoiseSumEt()>=25.0) ) 
                h1D_nm1_maxHPDNoOtherHits->Fill(hcalnoise_maxHPDNoOtherHits());

            if( !(hcalnoise_maxHPDNoOtherHits()>=10) &&
                    !(hcalnoise_numIsolatedNoiseChannels()>=10) &&
                    !(hcalnoise_isolatedNoiseSumE()>=50.0) &&
                    !(hcalnoise_isolatedNoiseSumEt()>=25.0) ) 
                h1D_nm1_maxHPDHits->Fill(hcalnoise_maxHPDHits());

            /// XXX START FILTERING

            addToCounter(to_string(++iCut)+" ALL"); // iCut will be 1
            // DCS AND TRACKS FILTER
            if ( ! haveFunctionalDCS() ) continue;
            addToCounter(to_string(++iCut)+" haveFunctionalDCS()"); // iCut will be 2

            if ( ! evt_trackingFailureFilter() ) continue;
            addToCounter(to_string(++iCut)+" evt_trackingFailureFilter()");

            if ( evt_ntracks() < 4 ) continue;
            addToCounter(to_string(++iCut)+" evt_ntracks()<4");

            // CSC HALO FILTER
            if ( !evt_cscTightHaloFilter() ) continue;
            addToCounter(to_string(++iCut)+" evt_cscTightHaloFilter()");

            h1D_pfCaloMet_halo->Fill(pfCaloMet);
            h1D_pfMet_halo->Fill(pfMet);
            h1D_caloMet_halo->Fill(caloMet);
            h1D_caloMetPhi_halo->Fill(caloMetPhi);
            h1D_pfMetPhi_halo->Fill(pfMetPhi);
            h1D_pfClusterMet_halo->Fill(pfClusterMet);
            h1D_pfChMet_halo->Fill(pfChMet);
            if(dPhiCaloMet < M_PI) h1D_jetCaloMetPhi_halo->Fill(dPhiCaloMet);


            // HCAL NOISE FILTERS
            if ( !hbheIsoNoiseFilter() ) continue;
            addToCounter(to_string(++iCut)+" hbheIsoNoiseFilter()");

            // if ( !hcalnoise_passTightNoiseFilter() ) continue; 
            if ( !hbheNoiseFilter() ) continue; // IGNORE MAXZEROS
            addToCounter(to_string(++iCut)+" hcalnoise_passTightNoiseFilter()");

            h1D_pfCaloMet_halonoise->Fill(pfCaloMet);
            h1D_pfMet_halonoise->Fill(pfMet);
            h1D_caloMet_halonoise->Fill(caloMet);
            h1D_caloMetPhi_halonoise->Fill(caloMetPhi);
            h1D_pfMetPhi_halonoise->Fill(pfMetPhi);
            h1D_pfClusterMet_halonoise->Fill(pfClusterMet);
            h1D_pfChMet_halonoise->Fill(pfChMet);
            if(dPhiCaloMet < M_PI) h1D_jetCaloMetPhi_halonoise->Fill(dPhiCaloMet);


            // HCAL FILTER 50NS
            // if ( !evt_hbheFilterRun1() ) continue;
            if ( false ) continue; // IGNORE MAXZEROS
            addToCounter(to_string(++iCut)+" evt_hbheFilterRun1()");

            h1D_pfCaloMet_halonoisehbhe->Fill(pfCaloMet);
            h1D_pfMet_halonoisehbhe->Fill(pfMet);
            h1D_caloMet_halonoisehbhe->Fill(caloMet);
            h1D_caloMetPhi_halonoisehbhe->Fill(caloMetPhi);
            h1D_pfMetPhi_halonoisehbhe->Fill(pfMetPhi);
            h1D_pfClusterMet_halonoisehbhe->Fill(pfClusterMet);
            h1D_pfChMet_halonoisehbhe->Fill(pfChMet);
            if(dPhiCaloMet < M_PI) h1D_jetCaloMetPhi_halonoisehbhe->Fill(dPhiCaloMet);


            // ECAL FILTERS
            if ( !evt_EcalDeadCellTriggerPrimitiveFilter() ) continue;
            addToCounter(to_string(++iCut)+" evt_EcalDeadCellTriggerPrimitiveFilter()");

            if ( !evt_eeBadScFilter() ) continue;
            addToCounter(to_string(++iCut)+" evt_eeBadScFilter()");

            h1D_pfCaloMet_halonoisehbheecal->Fill(pfCaloMet);
            h1D_pfMet_halonoisehbheecal->Fill(pfMet);
            h1D_caloMet_halonoisehbheecal->Fill(caloMet);
            h1D_caloMetPhi_halonoisehbheecal->Fill(caloMetPhi);
            h1D_pfMetPhi_halonoisehbheecal->Fill(pfMetPhi);
            h1D_pfClusterMet_halonoisehbheecal->Fill(pfClusterMet);
            h1D_pfChMet_halonoisehbheecal->Fill(pfChMet);
            if(dPhiCaloMet < M_PI) h1D_jetCaloMetPhi_halonoisehbheecal->Fill(dPhiCaloMet);

            bool passJetID = true;
            for(int iJet = 0; iJet < pfjets_p4().size(); iJet++) {
                if(pfjets_p4().at(iJet).pt() > 100) {
                    if(!passesLoosePFJetID(iJet)) {
                        passJetID = false;
                        break;
                    }
                }
            }

            if (! passJetID ) {
                // passed all the other filters, but not JetID
                // print out these events


                h1D_hcalnoise_HasBadRBXTS4TS5_jet->Fill(hcalnoise_HasBadRBXTS4TS5());
                h1D_hcalnoise_GetRecHitEnergy_jet->Fill(hcalnoise_GetRecHitEnergy());
                h1D_hcalnoise_GetRecHitEnergy15_jet->Fill(hcalnoise_GetRecHitEnergy15());
                h1D_hcalnoise_GetTotalCalibCharge_jet->Fill(hcalnoise_GetTotalCalibCharge());
                h1D_hcalnoise_TS4TS5NoiseSumE_jet->Fill(hcalnoise_TS4TS5NoiseSumE());
                h1D_hcalnoise_TS4TS5NoiseSumEt_jet->Fill(hcalnoise_TS4TS5NoiseSumEt());
                h1D_hcalnoise_eventChargeFraction_jet->Fill(hcalnoise_eventChargeFraction());
                h1D_hcalnoise_eventEMEnergy_jet->Fill(hcalnoise_eventEMEnergy());
                h1D_hcalnoise_eventEMFraction_jet->Fill(hcalnoise_eventEMFraction());
                h1D_hcalnoise_eventHadEnergy_jet->Fill(hcalnoise_eventHadEnergy());
                h1D_hcalnoise_eventTrackEnergy_jet->Fill(hcalnoise_eventTrackEnergy());
                h1D_hcalnoise_flatNoiseSumE_jet->Fill(hcalnoise_flatNoiseSumE());
                h1D_hcalnoise_flatNoiseSumEt_jet->Fill(hcalnoise_flatNoiseSumEt());
                h1D_hcalnoise_isolatedNoiseSumE_jet->Fill(hcalnoise_isolatedNoiseSumE());
                h1D_hcalnoise_isolatedNoiseSumEt_jet->Fill(hcalnoise_isolatedNoiseSumEt());
                h1D_hcalnoise_max10GeVHitTime_jet->Fill(hcalnoise_max10GeVHitTime());
                h1D_hcalnoise_max25GeVHitTime_jet->Fill(hcalnoise_max25GeVHitTime());
                h1D_hcalnoise_maxE10TS_jet->Fill(hcalnoise_maxE10TS());
                h1D_hcalnoise_maxE2Over10TS_jet->Fill(hcalnoise_maxE2Over10TS());
                h1D_hcalnoise_maxE2TS_jet->Fill(hcalnoise_maxE2TS());
                h1D_hcalnoise_min10GeVHitTime_jet->Fill(hcalnoise_min10GeVHitTime());
                h1D_hcalnoise_min25GeVHitTime_jet->Fill(hcalnoise_min25GeVHitTime());
                h1D_hcalnoise_minE10TS_jet->Fill(hcalnoise_minE10TS());
                h1D_hcalnoise_minE2Over10TS_jet->Fill(hcalnoise_minE2Over10TS());
                h1D_hcalnoise_minE2TS_jet->Fill(hcalnoise_minE2TS());
                h1D_hcalnoise_minHPDEMF_jet->Fill(hcalnoise_minHPDEMF());
                h1D_hcalnoise_minRBXEMF_jet->Fill(hcalnoise_minRBXEMF());
                h1D_hcalnoise_rms10GeVHitTime_jet->Fill(hcalnoise_rms10GeVHitTime());
                h1D_hcalnoise_rms25GeVHitTime_jet->Fill(hcalnoise_rms25GeVHitTime());
                h1D_hcalnoise_spikeNoiseSumE_jet->Fill(hcalnoise_spikeNoiseSumE());
                h1D_hcalnoise_spikeNoiseSumEt_jet->Fill(hcalnoise_spikeNoiseSumEt());
                h1D_hcalnoise_triangleNoiseSumE_jet->Fill(hcalnoise_triangleNoiseSumE());
                h1D_hcalnoise_triangleNoiseSumEt_jet->Fill(hcalnoise_triangleNoiseSumEt());
                h1D_hcalnoise_GetRecHitCount_jet->Fill(hcalnoise_GetRecHitCount());
                h1D_hcalnoise_GetRecHitCount15_jet->Fill(hcalnoise_GetRecHitCount15());
                h1D_hcalnoise_hbheIsoNoiseFilter_jet->Fill(hcalnoise_hbheIsoNoiseFilter());
                h1D_hcalnoise_maxHPDHits_jet->Fill(hcalnoise_maxHPDHits());
                h1D_hcalnoise_maxHPDNoOtherHits_jet->Fill(hcalnoise_maxHPDNoOtherHits());
                h1D_hcalnoise_maxRBXHits_jet->Fill(hcalnoise_maxRBXHits());
                h1D_hcalnoise_maxZeros_jet->Fill(hcalnoise_maxZeros());
                h1D_hcalnoise_noiseFilterStatus_jet->Fill(hcalnoise_noiseFilterStatus());
                h1D_hcalnoise_noiseType_jet->Fill(hcalnoise_noiseType());
                h1D_hcalnoise_num10GeVHits_jet->Fill(hcalnoise_num10GeVHits());
                h1D_hcalnoise_num25GeVHits_jet->Fill(hcalnoise_num25GeVHits());
                h1D_hcalnoise_numFlatNoiseChannels_jet->Fill(hcalnoise_numFlatNoiseChannels());
                h1D_hcalnoise_numIsolatedNoiseChannels_jet->Fill(hcalnoise_numIsolatedNoiseChannels());
                h1D_hcalnoise_numProblematicRBXs_jet->Fill(hcalnoise_numProblematicRBXs());
                h1D_hcalnoise_numSpikeNoiseChannels_jet->Fill(hcalnoise_numSpikeNoiseChannels());
                h1D_hcalnoise_numTS4TS5NoiseChannels_jet->Fill(hcalnoise_numTS4TS5NoiseChannels());
                h1D_hcalnoise_numTriangleNoiseChannels_jet->Fill(hcalnoise_numTriangleNoiseChannels());
                h1D_hcalnoise_passHighLevelNoiseFilter_jet->Fill(hcalnoise_passHighLevelNoiseFilter());
                h1D_hcalnoise_passLooseNoiseFilter_jet->Fill(hcalnoise_passLooseNoiseFilter());
                h1D_hcalnoise_passTightNoiseFilter_jet->Fill(hcalnoise_passTightNoiseFilter());


                for(int i = 0; i < twrs_eta().size(); i++) {
                    float twrEta = twrs_etacorr().at(i);
                    float twrPhi = twrs_phicorr().at(i);
                    // h2D_towers_etaphi->Fill(twrEta, twrPhi);

                    h2D_twrs_numBadEcalCells->Fill(twrEta,twrPhi,twrs_numBadEcalCells().at(i));
                    h2D_twrs_numRecoveredEcalCells->Fill(twrEta,twrPhi,twrs_numRecoveredEcalCells().at(i));
                    h2D_twrs_numProblematicEcalCells->Fill(twrEta,twrPhi,twrs_numProblematicEcalCells().at(i));
                    h2D_twrs_numBadHcalCells->Fill(twrEta,twrPhi,twrs_numBadHcalCells().at(i));
                    h2D_twrs_numRecoveredHcalCells->Fill(twrEta,twrPhi,twrs_numRecoveredHcalCells().at(i));
                    h2D_twrs_numProblematicHcalCells->Fill(twrEta,twrPhi,twrs_numProblematicHcalCells().at(i));
                    h2D_twrs_numCrystals->Fill(twrEta,twrPhi,twrs_numCrystals().at(i));

                    h1D_twrs_numBadEcalCells_jet->Fill(twrs_numBadEcalCells().at(i));
                    h1D_twrs_numRecoveredEcalCells_jet->Fill(twrs_numRecoveredEcalCells().at(i));
                    h1D_twrs_numProblematicEcalCells_jet->Fill(twrs_numProblematicEcalCells().at(i));
                    h1D_twrs_numBadHcalCells_jet->Fill(twrs_numBadHcalCells().at(i));
                    h1D_twrs_numRecoveredHcalCells_jet->Fill(twrs_numRecoveredHcalCells().at(i));
                    h1D_twrs_numProblematicHcalCells_jet->Fill(twrs_numProblematicHcalCells().at(i));
                    h1D_twrs_numCrystals_jet->Fill(twrs_numCrystals().at(i));
                }   


                if(pfMet > 500) {
                    std::cout << evt_run() << ":" << evt_lumiBlock() << ":" << evt_event() << " pfCaloMet: " << pfCaloMet << " pfMet: " << pfMet << " pfChMet: " << pfChMet << " caloMet: " << caloMet << " pfClusterMet: " << pfClusterMet << std::endl;

                }

            } 

            if( !passJetID ) continue;
            addToCounter(to_string(++iCut)+" passJetID");

            h1D_pfCaloMet_halonoisehbheecaljet->Fill(pfCaloMet);
            h1D_pfMet_halonoisehbheecaljet->Fill(pfMet);
            h1D_caloMet_halonoisehbheecaljet->Fill(caloMet);
            h1D_caloMetPhi_halonoisehbheecaljet->Fill(caloMetPhi);
            h1D_pfMetPhi_halonoisehbheecaljet->Fill(pfMetPhi);
            h1D_pfClusterMet_halonoisehbheecaljet->Fill(pfClusterMet);
            h1D_pfChMet_halonoisehbheecaljet->Fill(pfChMet);
            if(dPhiCaloMet < M_PI) h1D_jetCaloMetPhi_halonoisehbheecaljet->Fill(dPhiCaloMet);

            // SURVIVING EVENTS

            for(int iDet = 0; iDet < 32; iDet++) {
                if( evt_detectorStatus() & (1 << iDet) ) h1D_detectorStatus_filt->Fill(iDet);
            }


            h2D_pfCaloMet_pfMet->Fill(pfCaloMet, pfMet);
            h2D_pfCaloMet_caloMet->Fill(pfCaloMet, caloMet);
            h2D_caloMet_pfMet->Fill(caloMet, pfMet);
            h2D_pfClusterMet_pfMet->Fill(pfClusterMet,pfMet);
            h2D_pfClusterMet_caloMet->Fill(pfClusterMet,caloMet);
            h2D_pfClusterMet_pfCaloMet->Fill(pfClusterMet,pfCaloMet);
            h2D_pfCaloMet_pfMet->Fill(pfCaloMet, pfMet);
            h2D_pfCaloMet_caloMet->Fill(pfCaloMet, caloMet);
            h2D_caloMet_pfMet->Fill(caloMet, pfMet);
            h2D_jetPt_caloMet->Fill(leadingJetPt, caloMet);

            h1D_hcalnoise_HasBadRBXTS4TS5->Fill(hcalnoise_HasBadRBXTS4TS5());
            h1D_hcalnoise_GetRecHitEnergy->Fill(hcalnoise_GetRecHitEnergy());
            h1D_hcalnoise_GetRecHitEnergy15->Fill(hcalnoise_GetRecHitEnergy15());
            h1D_hcalnoise_GetTotalCalibCharge->Fill(hcalnoise_GetTotalCalibCharge());
            h1D_hcalnoise_TS4TS5NoiseSumE->Fill(hcalnoise_TS4TS5NoiseSumE());
            h1D_hcalnoise_TS4TS5NoiseSumEt->Fill(hcalnoise_TS4TS5NoiseSumEt());
            h1D_hcalnoise_eventChargeFraction->Fill(hcalnoise_eventChargeFraction());
            h1D_hcalnoise_eventEMEnergy->Fill(hcalnoise_eventEMEnergy());
            h1D_hcalnoise_eventEMFraction->Fill(hcalnoise_eventEMFraction());
            h1D_hcalnoise_eventHadEnergy->Fill(hcalnoise_eventHadEnergy());
            h1D_hcalnoise_eventTrackEnergy->Fill(hcalnoise_eventTrackEnergy());
            h1D_hcalnoise_flatNoiseSumE->Fill(hcalnoise_flatNoiseSumE());
            h1D_hcalnoise_flatNoiseSumEt->Fill(hcalnoise_flatNoiseSumEt());
            h1D_hcalnoise_isolatedNoiseSumE->Fill(hcalnoise_isolatedNoiseSumE());
            h1D_hcalnoise_isolatedNoiseSumEt->Fill(hcalnoise_isolatedNoiseSumEt());
            h1D_hcalnoise_max10GeVHitTime->Fill(hcalnoise_max10GeVHitTime());
            h1D_hcalnoise_max25GeVHitTime->Fill(hcalnoise_max25GeVHitTime());
            h1D_hcalnoise_maxE10TS->Fill(hcalnoise_maxE10TS());
            h1D_hcalnoise_maxE2Over10TS->Fill(hcalnoise_maxE2Over10TS());
            h1D_hcalnoise_maxE2TS->Fill(hcalnoise_maxE2TS());
            h1D_hcalnoise_min10GeVHitTime->Fill(hcalnoise_min10GeVHitTime());
            h1D_hcalnoise_min25GeVHitTime->Fill(hcalnoise_min25GeVHitTime());
            h1D_hcalnoise_minE10TS->Fill(hcalnoise_minE10TS());
            h1D_hcalnoise_minE2Over10TS->Fill(hcalnoise_minE2Over10TS());
            h1D_hcalnoise_minE2TS->Fill(hcalnoise_minE2TS());
            h1D_hcalnoise_minHPDEMF->Fill(hcalnoise_minHPDEMF());
            h1D_hcalnoise_minRBXEMF->Fill(hcalnoise_minRBXEMF());
            h1D_hcalnoise_rms10GeVHitTime->Fill(hcalnoise_rms10GeVHitTime());
            h1D_hcalnoise_rms25GeVHitTime->Fill(hcalnoise_rms25GeVHitTime());
            h1D_hcalnoise_spikeNoiseSumE->Fill(hcalnoise_spikeNoiseSumE());
            h1D_hcalnoise_spikeNoiseSumEt->Fill(hcalnoise_spikeNoiseSumEt());
            h1D_hcalnoise_triangleNoiseSumE->Fill(hcalnoise_triangleNoiseSumE());
            h1D_hcalnoise_triangleNoiseSumEt->Fill(hcalnoise_triangleNoiseSumEt());
            h1D_hcalnoise_GetRecHitCount->Fill(hcalnoise_GetRecHitCount());
            h1D_hcalnoise_GetRecHitCount15->Fill(hcalnoise_GetRecHitCount15());
            h1D_hcalnoise_hbheIsoNoiseFilter->Fill(hcalnoise_hbheIsoNoiseFilter());
            h1D_hcalnoise_maxHPDHits->Fill(hcalnoise_maxHPDHits());
            h1D_hcalnoise_maxHPDNoOtherHits->Fill(hcalnoise_maxHPDNoOtherHits());
            h1D_hcalnoise_maxRBXHits->Fill(hcalnoise_maxRBXHits());
            h1D_hcalnoise_maxZeros->Fill(hcalnoise_maxZeros());
            h1D_hcalnoise_noiseFilterStatus->Fill(hcalnoise_noiseFilterStatus());
            h1D_hcalnoise_noiseType->Fill(hcalnoise_noiseType());
            h1D_hcalnoise_num10GeVHits->Fill(hcalnoise_num10GeVHits());
            h1D_hcalnoise_num25GeVHits->Fill(hcalnoise_num25GeVHits());
            h1D_hcalnoise_numFlatNoiseChannels->Fill(hcalnoise_numFlatNoiseChannels());
            h1D_hcalnoise_numIsolatedNoiseChannels->Fill(hcalnoise_numIsolatedNoiseChannels());
            h1D_hcalnoise_numProblematicRBXs->Fill(hcalnoise_numProblematicRBXs());
            h1D_hcalnoise_numSpikeNoiseChannels->Fill(hcalnoise_numSpikeNoiseChannels());
            h1D_hcalnoise_numTS4TS5NoiseChannels->Fill(hcalnoise_numTS4TS5NoiseChannels());
            h1D_hcalnoise_numTriangleNoiseChannels->Fill(hcalnoise_numTriangleNoiseChannels());
            h1D_hcalnoise_passHighLevelNoiseFilter->Fill(hcalnoise_passHighLevelNoiseFilter());
            h1D_hcalnoise_passLooseNoiseFilter->Fill(hcalnoise_passLooseNoiseFilter());
            h1D_hcalnoise_passTightNoiseFilter->Fill(hcalnoise_passTightNoiseFilter());




            nEventsFiltered++;


            if(evt_run() != prevRun || evt_lumiBlock() != prevLumi) {
                runLumiOutput << evt_run() << ":" << evt_lumiBlock() << "\n";
                prevRun = evt_run();
                prevLumi = evt_lumiBlock();
            }

            if( passHLTTrigger("HLT_PFMET170_v1") ) h1D_trig_pfMet->Fill(pfMet);
            if( passHLTTrigger("HLT_PFMET170_NoiseCleaned_v2") ) h1D_trig_pfMet_clean->Fill(pfMet);
            if( passHLTTrigger("HLT_PFMET170_v1") && passHLTTrigger("HLT_PFMET170_NoiseCleaned_v2") ) h1D_trig_pfMet_both->Fill(pfMet);


            h1D_maxZeros_filt->Fill(hcalnoise_maxZeros());
            h1D_effbyrun_filt->Fill(runToBinMap[evt_run()]);


            // At this point, we've passed all the filters
            // and are now in the region of interest

            // if(pfMet > 500) {
            // std::cout << evt_run() << ":" << evt_lumiBlock() << ":" << evt_event() << " pfCaloMet: " << pfCaloMet << " pfMet: " << pfMet << " pfChMet: " << pfChMet << " caloMet: " << caloMet << " pfClusterMet: " << pfClusterMet << std::endl;
            // }

        }

        // Clean Up
        delete tree;
        file->Close();
        delete file;
        }

        runLumiOutput.close();
        debug.close();
        printCounter();

        std::cout << " nEventsChain: " << nEventsChain << " nEventsFiltered: " << nEventsFiltered << std::endl;


        std::cout << "ALL: " << passFilters.at(0) << std::endl
            << "trackingFailure: " << passFilters.at(1) << std::endl
            << "cscTightHalo: " << passFilters.at(2) << std::endl
            << "hbheIsoNoise: " << passFilters.at(3) << std::endl
            << "hbheFilterRun1: " << passFilters.at(4) << std::endl
            << "ecalDeadCell: " << passFilters.at(5) << std::endl
            << "eeBadSc: " << passFilters.at(6) << std::endl
            << "passTightNoise: " << passFilters.at(7) << std::endl;


        std::string out = "pdfs/";
        std::string common = "--noStack --noFill --xAxisOverride [GeV] --type --preserveBackgroundOrder --legendTextSize 0.03 --legendRight -0.05 ";
        dataMCplotMaker(null, h1D_met_vec, titlesMet, "", "", common+" --overrideHeader MET (after filters) --outputName "+out+"h1D_met.pdf");

        dataMCplotMaker(null, h1D_caloMet_filters_vec, titlesFilters, "", "", common+" --overrideHeader caloMet (cumulative filters) --outputName "+out+"h1D_caloMet_filters.pdf");
        dataMCplotMaker(null, h1D_pfMet_filters_vec, titlesFilters, "", "", common+" --overrideHeader pfMet (cumulative filters) --outputName "+out+"h1D_pfMet_filters.pdf");
        dataMCplotMaker(null, h1D_pfClusterMet_filters_vec, titlesFilters, "", "", common+" --overrideHeader pfClusterMet (cumulative filters) --outputName "+out+"h1D_pfClusterMet_filters.pdf");
        dataMCplotMaker(null, h1D_pfChMet_filters_vec, titlesFilters, "", "", common+" --overrideHeader pfChMet (cumulative filters) --outputName "+out+"h1D_pfChMet_filters.pdf");
        dataMCplotMaker(null, h1D_pfCaloMet_filters_vec, titlesFilters, "", "", common+" --overrideHeader pfCaloMet (cumulative filters) --outputName "+out+"h1D_pfCaloMet_filters.pdf");

        dataMCplotMaker(null, h1D_caloMetPhi_filters_vec, titlesFilters, "", "", common+" --setMaximum 5000 --isLinear --overrideHeader caloMetPhi (cumulative filters) --outputName "+out+"h1D_caloMetPhi_filters.pdf");
        dataMCplotMaker(null, h1D_pfMetPhi_filters_vec, titlesFilters, "", "", common+" --isLinear --overrideHeader pfMetPhi (cumulative filters) --outputName "+out+"h1D_pfMetPhi_filters.pdf");

        dataMCplotMaker(null, h1D_jetCaloMetPhi_filters_vec, titlesFilters, "", "", common+"  --overrideHeader #Delta#phi(j,caloMet) (cumulative filters) --xAxisOverride #phi --outputName "+out+"h1D_jetCaloMetPhi_filters.pdf");

        dataMCplotMaker(null, h1D_caloMet_filt_track_vec, titlesOneFilt, "", "", common+" --overrideHeader caloMet: trackingFailureFilter --outputName "+out+"h1D_caloMet_filt_track.pdf");
        dataMCplotMaker(null, h1D_caloMet_filt_halo_vec, titlesOneFilt, "", "", common+" --overrideHeader caloMet: cscTightHaloFilter --outputName "+out+"h1D_caloMet_filt_halo.pdf");
        dataMCplotMaker(null, h1D_caloMet_filt_isonoise_vec, titlesOneFilt, "", "", common+" --overrideHeader caloMet: hbheIsoNoiseFilter --outputName "+out+"h1D_caloMet_filt_isonoise.pdf");
        dataMCplotMaker(null, h1D_caloMet_filt_tightnoise_vec, titlesOneFilt, "", "", common+" --overrideHeader caloMet: passTightNoiseFilter --outputName "+out+"h1D_caloMet_filt_tightnoise.pdf");
        dataMCplotMaker(null, h1D_caloMet_filt_hbherun1_vec, titlesOneFilt, "", "", common+" --overrideHeader caloMet: hbheFilterRun1 --outputName "+out+"h1D_caloMet_filt_hbherun1.pdf");
        dataMCplotMaker(null, h1D_caloMet_filt_ecalcell_vec, titlesOneFilt, "", "", common+" --overrideHeader caloMet: EcalDeadCellFilter --outputName "+out+"h1D_caloMet_filt_ecalcell.pdf");
        dataMCplotMaker(null, h1D_caloMet_filt_eebadsc_vec, titlesOneFilt, "", "", common+" --overrideHeader caloMet: eeBadScFilter --outputName "+out+"h1D_caloMet_filt_eebadsc.pdf");

        dataMCplotMaker(null, h1D_maxZeros_vec, titlesOnesFilt, "", "", common+" --overrideHeader maxZeros in RBX --outputName "+out+"h1D_maxZeros.pdf");

        dataMCplotMaker(null, h1D_leadingJet_chf_vec, titlesLeadingJet, "", "", common+"  --overrideHeader charged hadron fraction (no filters) --xAxisOverride fraction --outputName "+out+"h1D_leadingJet_chf.pdf");
        dataMCplotMaker(null, h1D_leadingJet_nhf_vec, titlesLeadingJet, "", "", common+"  --overrideHeader neutral hadron fraction (no filters) --xAxisOverride fraction --outputName "+out+"h1D_leadingJet_nhf.pdf");
        dataMCplotMaker(null, h1D_leadingJet_cef_vec, titlesLeadingJet, "", "", common+"  --overrideHeader charged EM fraction (no filters) --xAxisOverride fraction --outputName "+out+"h1D_leadingJet_cef.pdf");
        dataMCplotMaker(null, h1D_leadingJet_nef_vec, titlesLeadingJet, "", "", common+"  --overrideHeader neutral EM fraction (no filters) --xAxisOverride fraction --outputName "+out+"h1D_leadingJet_nef.pdf");
        dataMCplotMaker(null, h1D_leadingJet_cm_vec,  titlesLeadingJet, "", "", common+"  --overrideHeader charged multiplicity  (no filters) --xAxisOverride --outputName "+out+"h1D_leadingJet_cm.pdf");

        dataMCplotMaker(null, h1D_nm1_maxHPDHits_vec, titlesNm1, "", "", common+"  --overrideHeader maxHPDHits N-1 before other filters --xAxisOverride n --vLine 17 --outputName "+out+"h1D_nm1_maxHPDHits.pdf");
        dataMCplotMaker(null, h1D_nm1_maxHPDNoOtherHits_vec, titlesNm1, "", "", common+"  --overrideHeader maxHPDNoOtherHits N-1 before other filters --xAxisOverride n --vLine 10 --outputName "+out+"h1D_nm1_maxHPDNoOtherHits.pdf");
        dataMCplotMaker(null, h1D_nm1_numIsolatedNoiseChannels_vec, titlesNm1, "", "", common+"  --overrideHeader numIsolatedNoiseChannels N-1 before other filters --vLine 10 --xAxisOverride n --outputName "+out+"h1D_nm1_numIsolatedNoiseChannels.pdf");
        dataMCplotMaker(null, h1D_nm1_isolatedNoiseSumE_vec, titlesNm1, "", "", common+"  --overrideHeader isolatedNoiseSumE N-1 before other filters --vLine 50 --xAxisOverride [GeV] --outputName "+out+"h1D_nm1_isolatedNoiseSumE.pdf");
        dataMCplotMaker(null, h1D_nm1_isolatedNoiseSumEt_vec,  titlesNm1, "", "", common+"  --overrideHeader isolatedNoiseSumEt N-1 before other filters --vLine 25 --xAxisOverride [GeV] --outputName "+out+"h1D_nm1_isolatedNoiseSumEt.pdf");

        dataMCplotMaker(null, h1D_trig_pfMet_vec,  titlesTrig, "", "", common+"  --overrideHeader pfMet (after filters) --xAxisOverride [GeV] --outputName "+out+"h1D_trig_pfMet.pdf");

        drawHist2D(h2D_pfClusterMet_pfCaloMet,out+"h2D_pfClusterMet_pfCaloMet.pdf",    "--logscale --title pfCaloMet vs pfClusterMet --xlabel pfClusterMet --ylabel pfCaloMet");
        drawHist2D(h2D_pfClusterMet_caloMet,out+"h2D_pfClusterMet_caloMet.pdf","--logscale --title caloMet vs pfClusterMet --xlabel pfClusterMet --ylabel caloMet");
        drawHist2D(h2D_pfClusterMet_pfMet,out+"h2D_pfClusterMet_pfMet.pdf","--logscale --title pfMet vs pfClusterMet --xlabel  pfClusterMet --ylabel pfMet");
        drawHist2D(h2D_pfCaloMet_pfMet,out+"h2D_pfCaloMet_pfMet.pdf",    "--logscale --title pfMet vs pfCaloMet --xlabel pfCaloMet_met --ylabel pfMet_met");
        drawHist2D(h2D_pfCaloMet_caloMet,out+"h2D_pfCaloMet_caloMet.pdf","--logscale --title caloMet vs pfCaloMet --xlabel pfCaloMet_met --ylabel caloMet");
        drawHist2D(h2D_caloMet_pfMet,out+"h2D_caloMet_pfMet.pdf","--logscale --title pfMet vs caloMet --xlabel  caloMet --ylabel pfMet");

        drawHist2D(h2D_jetPt_caloMet,out+"h2D_jetPt_caloMet.pdf","--logscale --title caloMet vs leading jet pT --xlabel  jetPt --ylabel caloMet");

        drawHist2D(h2D_towers_etaphi,out+"h2D_towers_etaphi.pdf","--logscale --title towers --xlabel  #eta --ylabel #phi");
        drawHist2D(h2D_towers_etaphi_em,out+"h2D_towers_etaphi_em.pdf","--logscale --title towers (EM weighted) --xlabel  #eta --ylabel #phi");
        drawHist2D(h2D_towers_etaphi_had,out+"h2D_towers_etaphi_had.pdf","--logscale --title towers (HCAL weighted) --xlabel  #eta --ylabel #phi");
        drawHist2D(h2D_towers_etaphi_outer,out+"h2D_towers_etaphi_outer.pdf","--logscale --title towers (HO weighted) --xlabel  #eta --ylabel #phi");
        drawHist2D(h2D_pfclusters_etaphi,out+"h2D_pfclusters_etaphi.pdf","--logscale --title pfclusters --xlabel  #eta --ylabel #phi");
        drawHist2D(h2D_calojets_etaphi,out+"h2D_calojets_etaphi.pdf","--logscale --title calojets --xlabel  #eta --ylabel #phi");

        TH2F *h2D_towers_etaphi_em_avg = (TH2F*)h2D_towers_etaphi_em->Clone();
        TH2F *h2D_towers_etaphi_had_avg = (TH2F*)h2D_towers_etaphi_had->Clone();
        h2D_towers_etaphi_em_avg->Divide(h2D_towers_etaphi);
        h2D_towers_etaphi_had_avg->Divide(h2D_towers_etaphi);

        h2D_towers_etaphi_em->Divide(h2D_towers_etaphi);
        h2D_towers_etaphi_had->Divide(h2D_towers_etaphi);

        drawHist2D(h2D_towers_etaphi_em,out+"h2D_towers_etaphi_em_avg.pdf","--logscale --title towers (EM weighted,avg per bin) --xlabel  #eta --ylabel #phi");
        drawHist2D(h2D_towers_etaphi_had,out+"h2D_towers_etaphi_had_avg.pdf","--logscale --title towers (HCAL weighted,avg per bin) --xlabel  #eta --ylabel #phi");

        h1D_trig_pfMet_clean->Divide(h1D_trig_pfMet);

        singlePlotMaker(h1D_trig_pfMet_clean, "",common+" --overrideHeader clean/normal --outputName "+out+"h1D_trig_pfMet_clean_ratio.pdf");

        singlePlotMaker(h1D_towers_phi, "",common+" --overrideHeader towers phi occupancy --outputName "+out+"h1D_towers_phi.pdf");
        singlePlotMaker(h1D_towers_phi_em, "",common+" --overrideHeader towers phi occupancy (ECAL weighted) --outputName "+out+"h1D_towers_phi_em.pdf");
        singlePlotMaker(h1D_towers_phi_had, "",common+" --overrideHeader towers phi occupancy (HCAL weighted) --outputName "+out+"h1D_towers_phi_had.pdf");
        singlePlotMaker(h1D_towers_phi_outer, "",common+" --overrideHeader towers phi occupancy (HO weighted) --outputName "+out+"h1D_towers_phi_outer.pdf");

        h1D_towers_phi_em->Divide(h1D_towers_phi);
        h1D_towers_phi_had->Divide(h1D_towers_phi);

        singlePlotMaker(h1D_towers_phi_em, "",common+" --histoErrors --overrideHeader towers phi occupancy (ECAL weighted, avg per bin) --outputName "+out+"h1D_towers_phi_em_avg.pdf");
        singlePlotMaker(h1D_towers_phi_had, "",common+" --histoErrors --overrideHeader towers phi occupancy (HCAL weighted, avg per bin) --outputName "+out+"h1D_towers_phi_had_avg.pdf");

        // singlePlotMaker(h1D_caloMetNew, "",common+" --overrideHeader caloMet tower eta-phi corrected --outputName "+out+"h1D_caloMetNew.pdf");
        // singlePlotMaker(h1D_caloMetPhiNew, "",common+" --isLinear --overrideHeader caloMetPhi tower eta-phi corrected --outputName "+out+"h1D_caloMetPhiNew.pdf");

        std::string runBinLabels = "";
        for(int i = 0; i < binToRunMap.size(); i++) {
            runBinLabels += to_string(binToRunMap[i]) + ",";
        }
        dataMCplotMaker(null, h1D_effbyrun_vec, titlesOnesFilt, "", "", common+" --overrideHeader filter efficiency by run  --xAxisVerticalBinLabels --xAxisBinLabels "+runBinLabels+" --outputName "+out+"h1D_effbyrun.pdf");

        std::string binLabels = "EBp,EBm,EEp,EEm,_,HBHEa,HBHEb,HBHEc,HF,HO,_,_,RPC,DT0,DTp,DTm,CSCp,CSCm,_,_,CASTOR,_,ZDC,_,TIBTID,TOB,TECp,TECm,BPIX,FPIX,ESp,ESm";
        dataMCplotMaker(null, h1D_detectorStatus_vec, titlesDCS, "", "", common+"  --overrideHeader DCS bits --nDivisions 216 --xAxisVerticalBinLabels --xAxisBinLabels "+binLabels+" --outputName "+out+"h1D_detectorStatus.pdf");


        // hcalnoise plots
        dataMCplotMaker(null,h1D_hcalnoise_HasBadRBXTS4TS5_vec,titlesHcalnoise,"hcalnoise_HasBadRBXTS4TS5","",common+"  --xAxisOverride [GeV] --outputName "+out+"hcalnoise_HasBadRBXTS4TS5.pdf");
        dataMCplotMaker(null,h1D_hcalnoise_GetRecHitEnergy_vec,titlesHcalnoise,"hcalnoise_GetRecHitEnergy","",common+"  --xAxisOverride [GeV] --outputName "+out+"hcalnoise_GetRecHitEnergy.pdf");
        dataMCplotMaker(null,h1D_hcalnoise_GetRecHitEnergy15_vec,titlesHcalnoise,"hcalnoise_GetRecHitEnergy15","",common+"  --xAxisOverride [GeV] --outputName "+out+"hcalnoise_GetRecHitEnergy15.pdf");
        dataMCplotMaker(null,h1D_hcalnoise_GetTotalCalibCharge_vec,titlesHcalnoise,"hcalnoise_GetTotalCalibCharge","",common+"  --xAxisOverride [GeV] --outputName "+out+"hcalnoise_GetTotalCalibCharge.pdf");
        dataMCplotMaker(null,h1D_hcalnoise_TS4TS5NoiseSumE_vec,titlesHcalnoise,"hcalnoise_TS4TS5NoiseSumE","",common+"  --xAxisOverride [GeV] --outputName "+out+"hcalnoise_TS4TS5NoiseSumE.pdf");
        dataMCplotMaker(null,h1D_hcalnoise_TS4TS5NoiseSumEt_vec,titlesHcalnoise,"hcalnoise_TS4TS5NoiseSumEt","",common+"  --xAxisOverride [GeV] --outputName "+out+"hcalnoise_TS4TS5NoiseSumEt.pdf");
        dataMCplotMaker(null,h1D_hcalnoise_eventChargeFraction_vec,titlesHcalnoise,"hcalnoise_eventChargeFraction","",common+"  --xAxisOverride [GeV] --outputName "+out+"hcalnoise_eventChargeFraction.pdf");
        dataMCplotMaker(null,h1D_hcalnoise_eventEMEnergy_vec,titlesHcalnoise,"hcalnoise_eventEMEnergy","",common+"  --xAxisOverride [GeV] --outputName "+out+"hcalnoise_eventEMEnergy.pdf");
        dataMCplotMaker(null,h1D_hcalnoise_eventEMFraction_vec,titlesHcalnoise,"hcalnoise_eventEMFraction","",common+"  --xAxisOverride [GeV] --outputName "+out+"hcalnoise_eventEMFraction.pdf");
        dataMCplotMaker(null,h1D_hcalnoise_eventHadEnergy_vec,titlesHcalnoise,"hcalnoise_eventHadEnergy","",common+"  --xAxisOverride [GeV] --outputName "+out+"hcalnoise_eventHadEnergy.pdf");
        dataMCplotMaker(null,h1D_hcalnoise_eventTrackEnergy_vec,titlesHcalnoise,"hcalnoise_eventTrackEnergy","",common+"  --xAxisOverride [GeV] --outputName "+out+"hcalnoise_eventTrackEnergy.pdf");
        dataMCplotMaker(null,h1D_hcalnoise_flatNoiseSumE_vec,titlesHcalnoise,"hcalnoise_flatNoiseSumE","",common+"  --xAxisOverride [GeV] --outputName "+out+"hcalnoise_flatNoiseSumE.pdf");
        dataMCplotMaker(null,h1D_hcalnoise_flatNoiseSumEt_vec,titlesHcalnoise,"hcalnoise_flatNoiseSumEt","",common+"  --xAxisOverride [GeV] --outputName "+out+"hcalnoise_flatNoiseSumEt.pdf");
        dataMCplotMaker(null,h1D_hcalnoise_isolatedNoiseSumE_vec,titlesHcalnoise,"hcalnoise_isolatedNoiseSumE","",common+"  --xAxisOverride [GeV] --outputName "+out+"hcalnoise_isolatedNoiseSumE.pdf");
        dataMCplotMaker(null,h1D_hcalnoise_isolatedNoiseSumEt_vec,titlesHcalnoise,"hcalnoise_isolatedNoiseSumEt","",common+"  --xAxisOverride [GeV] --outputName "+out+"hcalnoise_isolatedNoiseSumEt.pdf");
        dataMCplotMaker(null,h1D_hcalnoise_max10GeVHitTime_vec,titlesHcalnoise,"hcalnoise_max10GeVHitTime","",common+"  --xAxisOverride [GeV] --outputName "+out+"hcalnoise_max10GeVHitTime.pdf");
        dataMCplotMaker(null,h1D_hcalnoise_max25GeVHitTime_vec,titlesHcalnoise,"hcalnoise_max25GeVHitTime","",common+"  --xAxisOverride [GeV] --outputName "+out+"hcalnoise_max25GeVHitTime.pdf");
        dataMCplotMaker(null,h1D_hcalnoise_maxE10TS_vec,titlesHcalnoise,"hcalnoise_maxE10TS","",common+"  --xAxisOverride [GeV] --outputName "+out+"hcalnoise_maxE10TS.pdf");
        dataMCplotMaker(null,h1D_hcalnoise_maxE2Over10TS_vec,titlesHcalnoise,"hcalnoise_maxE2Over10TS","",common+"  --xAxisOverride [GeV] --outputName "+out+"hcalnoise_maxE2Over10TS.pdf");
        dataMCplotMaker(null,h1D_hcalnoise_maxE2TS_vec,titlesHcalnoise,"hcalnoise_maxE2TS","",common+"  --xAxisOverride [GeV] --outputName "+out+"hcalnoise_maxE2TS.pdf");
        dataMCplotMaker(null,h1D_hcalnoise_min10GeVHitTime_vec,titlesHcalnoise,"hcalnoise_min10GeVHitTime","",common+"  --xAxisOverride [GeV] --outputName "+out+"hcalnoise_min10GeVHitTime.pdf");
        dataMCplotMaker(null,h1D_hcalnoise_min25GeVHitTime_vec,titlesHcalnoise,"hcalnoise_min25GeVHitTime","",common+"  --xAxisOverride [GeV] --outputName "+out+"hcalnoise_min25GeVHitTime.pdf");
        dataMCplotMaker(null,h1D_hcalnoise_minE10TS_vec,titlesHcalnoise,"hcalnoise_minE10TS","",common+"  --xAxisOverride [GeV] --outputName "+out+"hcalnoise_minE10TS.pdf");
        dataMCplotMaker(null,h1D_hcalnoise_minE2Over10TS_vec,titlesHcalnoise,"hcalnoise_minE2Over10TS","",common+"  --xAxisOverride [GeV] --outputName "+out+"hcalnoise_minE2Over10TS.pdf");
        dataMCplotMaker(null,h1D_hcalnoise_minE2TS_vec,titlesHcalnoise,"hcalnoise_minE2TS","",common+"  --xAxisOverride [GeV] --outputName "+out+"hcalnoise_minE2TS.pdf");
        dataMCplotMaker(null,h1D_hcalnoise_minHPDEMF_vec,titlesHcalnoise,"hcalnoise_minHPDEMF","",common+"  --xAxisOverride [GeV] --outputName "+out+"hcalnoise_minHPDEMF.pdf");
        dataMCplotMaker(null,h1D_hcalnoise_minRBXEMF_vec,titlesHcalnoise,"hcalnoise_minRBXEMF","",common+"  --xAxisOverride [GeV] --outputName "+out+"hcalnoise_minRBXEMF.pdf");
        dataMCplotMaker(null,h1D_hcalnoise_rms10GeVHitTime_vec,titlesHcalnoise,"hcalnoise_rms10GeVHitTime","",common+"  --xAxisOverride [GeV] --outputName "+out+"hcalnoise_rms10GeVHitTime.pdf");
        dataMCplotMaker(null,h1D_hcalnoise_rms25GeVHitTime_vec,titlesHcalnoise,"hcalnoise_rms25GeVHitTime","",common+"  --xAxisOverride [GeV] --outputName "+out+"hcalnoise_rms25GeVHitTime.pdf");
        dataMCplotMaker(null,h1D_hcalnoise_spikeNoiseSumE_vec,titlesHcalnoise,"hcalnoise_spikeNoiseSumE","",common+"  --xAxisOverride [GeV] --outputName "+out+"hcalnoise_spikeNoiseSumE.pdf");
        dataMCplotMaker(null,h1D_hcalnoise_spikeNoiseSumEt_vec,titlesHcalnoise,"hcalnoise_spikeNoiseSumEt","",common+"  --xAxisOverride [GeV] --outputName "+out+"hcalnoise_spikeNoiseSumEt.pdf");
        dataMCplotMaker(null,h1D_hcalnoise_triangleNoiseSumE_vec,titlesHcalnoise,"hcalnoise_triangleNoiseSumE","",common+"  --xAxisOverride [GeV] --outputName "+out+"hcalnoise_triangleNoiseSumE.pdf");
        dataMCplotMaker(null,h1D_hcalnoise_triangleNoiseSumEt_vec,titlesHcalnoise,"hcalnoise_triangleNoiseSumEt","",common+"  --xAxisOverride [GeV] --outputName "+out+"hcalnoise_triangleNoiseSumEt.pdf");
        dataMCplotMaker(null,h1D_hcalnoise_GetRecHitCount_vec,titlesHcalnoise,"hcalnoise_GetRecHitCount","",common+"  --xAxisOverride [GeV] --outputName "+out+"hcalnoise_GetRecHitCount.pdf");
        dataMCplotMaker(null,h1D_hcalnoise_GetRecHitCount15_vec,titlesHcalnoise,"hcalnoise_GetRecHitCount15","",common+"  --xAxisOverride [GeV] --outputName "+out+"hcalnoise_GetRecHitCount15.pdf");
        dataMCplotMaker(null,h1D_hcalnoise_hbheIsoNoiseFilter_vec,titlesHcalnoise,"hcalnoise_hbheIsoNoiseFilter","",common+"  --xAxisOverride [GeV] --outputName "+out+"hcalnoise_hbheIsoNoiseFilter.pdf");
        dataMCplotMaker(null,h1D_hcalnoise_maxHPDHits_vec,titlesHcalnoise,"hcalnoise_maxHPDHits","",common+"  --xAxisOverride [GeV] --outputName "+out+"hcalnoise_maxHPDHits.pdf");
        dataMCplotMaker(null,h1D_hcalnoise_maxHPDNoOtherHits_vec,titlesHcalnoise,"hcalnoise_maxHPDNoOtherHits","",common+"  --xAxisOverride [GeV] --outputName "+out+"hcalnoise_maxHPDNoOtherHits.pdf");
        dataMCplotMaker(null,h1D_hcalnoise_maxRBXHits_vec,titlesHcalnoise,"hcalnoise_maxRBXHits","",common+"  --xAxisOverride [GeV] --outputName "+out+"hcalnoise_maxRBXHits.pdf");
        dataMCplotMaker(null,h1D_hcalnoise_maxZeros_vec,titlesHcalnoise,"hcalnoise_maxZeros","",common+"  --xAxisOverride [GeV] --outputName "+out+"hcalnoise_maxZeros.pdf");
        dataMCplotMaker(null,h1D_hcalnoise_noiseFilterStatus_vec,titlesHcalnoise,"hcalnoise_noiseFilterStatus","",common+"  --xAxisOverride [GeV] --outputName "+out+"hcalnoise_noiseFilterStatus.pdf");
        dataMCplotMaker(null,h1D_hcalnoise_noiseType_vec,titlesHcalnoise,"hcalnoise_noiseType","",common+"  --xAxisOverride [GeV] --outputName "+out+"hcalnoise_noiseType.pdf");
        dataMCplotMaker(null,h1D_hcalnoise_num10GeVHits_vec,titlesHcalnoise,"hcalnoise_num10GeVHits","",common+"  --xAxisOverride [GeV] --outputName "+out+"hcalnoise_num10GeVHits.pdf");
        dataMCplotMaker(null,h1D_hcalnoise_num25GeVHits_vec,titlesHcalnoise,"hcalnoise_num25GeVHits","",common+"  --xAxisOverride [GeV] --outputName "+out+"hcalnoise_num25GeVHits.pdf");
        dataMCplotMaker(null,h1D_hcalnoise_numFlatNoiseChannels_vec,titlesHcalnoise,"hcalnoise_numFlatNoiseChannels","",common+"  --xAxisOverride [GeV] --outputName "+out+"hcalnoise_numFlatNoiseChannels.pdf");
        dataMCplotMaker(null,h1D_hcalnoise_numIsolatedNoiseChannels_vec,titlesHcalnoise,"hcalnoise_numIsolatedNoiseChannels","",common+"  --xAxisOverride [GeV] --outputName "+out+"hcalnoise_numIsolatedNoiseChannels.pdf");
        dataMCplotMaker(null,h1D_hcalnoise_numProblematicRBXs_vec,titlesHcalnoise,"hcalnoise_numProblematicRBXs","",common+"  --xAxisOverride [GeV] --outputName "+out+"hcalnoise_numProblematicRBXs.pdf");
        dataMCplotMaker(null,h1D_hcalnoise_numSpikeNoiseChannels_vec,titlesHcalnoise,"hcalnoise_numSpikeNoiseChannels","",common+"  --xAxisOverride [GeV] --outputName "+out+"hcalnoise_numSpikeNoiseChannels.pdf");
        dataMCplotMaker(null,h1D_hcalnoise_numTS4TS5NoiseChannels_vec,titlesHcalnoise,"hcalnoise_numTS4TS5NoiseChannels","",common+"  --xAxisOverride [GeV] --outputName "+out+"hcalnoise_numTS4TS5NoiseChannels.pdf");
        dataMCplotMaker(null,h1D_hcalnoise_numTriangleNoiseChannels_vec,titlesHcalnoise,"hcalnoise_numTriangleNoiseChannels","",common+"  --xAxisOverride [GeV] --outputName "+out+"hcalnoise_numTriangleNoiseChannels.pdf");
        dataMCplotMaker(null,h1D_hcalnoise_passHighLevelNoiseFilter_vec,titlesHcalnoise,"hcalnoise_passHighLevelNoiseFilter","",common+"  --xAxisOverride [GeV] --outputName "+out+"hcalnoise_passHighLevelNoiseFilter.pdf");
        dataMCplotMaker(null,h1D_hcalnoise_passLooseNoiseFilter_vec,titlesHcalnoise,"hcalnoise_passLooseNoiseFilter","",common+"  --xAxisOverride [GeV] --outputName "+out+"hcalnoise_passLooseNoiseFilter.pdf");
        dataMCplotMaker(null,h1D_hcalnoise_passTightNoiseFilter_vec,titlesHcalnoise,"hcalnoise_passTightNoiseFilter","",common+"  --xAxisOverride [GeV] --outputName "+out+"hcalnoise_passTightNoiseFilter.pdf");

        dataMCplotMaker(null,h1D_twrs_numBadEcalCells_vec,titlesHcalnoise,"twrs_numBadEcalCells_vec","",common+" --xAxisOverride [GeV] --outputName "+out+"twrs_numBadEcalCells_vec.pdf");
        dataMCplotMaker(null,h1D_twrs_numRecoveredEcalCells_vec,titlesHcalnoise,"twrs_numRecoveredEcalCells_vec","",common+" --xAxisOverride [GeV] --outputName "+out+"twrs_numRecoveredEcalCells_vec.pdf");
        dataMCplotMaker(null,h1D_twrs_numProblematicEcalCells_vec,titlesHcalnoise,"twrs_numProblematicEcalCells_vec","",common+" --xAxisOverride [GeV] --outputName "+out+"twrs_numProblematicEcalCells_vec.pdf");
        dataMCplotMaker(null,h1D_twrs_numBadHcalCells_vec,titlesHcalnoise,"twrs_numBadHcalCells_vec","",common+" --xAxisOverride [GeV] --outputName "+out+"twrs_numBadHcalCells_vec.pdf");
        dataMCplotMaker(null,h1D_twrs_numRecoveredHcalCells_vec,titlesHcalnoise,"twrs_numRecoveredHcalCells_vec","",common+" --xAxisOverride [GeV] --outputName "+out+"twrs_numRecoveredHcalCells_vec.pdf");
        dataMCplotMaker(null,h1D_twrs_numProblematicHcalCells_vec,titlesHcalnoise,"twrs_numProblematicHcalCells_vec","",common+" --xAxisOverride [GeV] --outputName "+out+"twrs_numProblematicHcalCells_vec.pdf");
        dataMCplotMaker(null,h1D_twrs_numCrystals_vec,titlesHcalnoise,"twrs_numCrystals_vec","",common+" --xAxisOverride [GeV] --outputName "+out+"twrs_numCrystals_vec.pdf");

        dataMCplotMaker(null,h1D_lengthBadCells_vec,titlesBadCells,"length bad HCAL cells","",common+" --xAxisOverride [GeV] --outputName "+out+"h1D_lengthBadCells_vec.pdf");

        drawHist2D(h2D_twrs_numBadEcalCells,out+"h2D_twrs_numBadEcalCells.pdf","--logscale --title  twrs_numBadEcalCells --xlabel #eta --ylabel #phi");
        drawHist2D(h2D_twrs_numRecoveredEcalCells,out+"h2D_twrs_numRecoveredEcalCells.pdf","--logscale --title  twrs_numRecoveredEcalCells --xlabel #eta --ylabel #phi");
        drawHist2D(h2D_twrs_numProblematicEcalCells,out+"h2D_twrs_numProblematicEcalCells.pdf","--logscale --title twrs_numProblematicEcalCells  --xlabel #eta --ylabel #phi");
        drawHist2D(h2D_twrs_numBadHcalCells,out+"h2D_twrs_numBadHcalCells.pdf","--logscale --title twrs_numBadHcalCells  --xlabel #eta --ylabel #phi");
        drawHist2D(h2D_twrs_numRecoveredHcalCells,out+"h2D_twrs_numRecoveredHcalCells.pdf","--logscale --title twrs_numRecoveredHcalCells  --xlabel #eta --ylabel #phi");
        drawHist2D(h2D_twrs_numProblematicHcalCells,out+"h2D_twrs_numProblematicHcalCells.pdf","--logscale --title twrs_numProblematicHcalCells  --xlabel #eta --ylabel #phi");
        drawHist2D(h2D_twrs_numCrystals,out+"h2D_twrs_numCrystals.pdf","--logscale --title twrs_numCrystals  --xlabel #eta --ylabel #phi");

        f.Write();

        return 0;
    }
