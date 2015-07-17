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

    // std::cout << " pfjet_chf_: " << pfjet_chf_ << " pfjet_nhf_: " << pfjet_nhf_ << " pfjet_cef_: " << pfjet_cef_ << " pfjet_nef_: " << pfjet_nef_ << std::endl;
    // std::cout << pfjet_eta << std::endl;

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
    float maxEta = 2.8;
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

    // projected 2D plots
    TH1F* h1D_towers_phi = new TH1F("h2D_towers_phi","",              30 ,-3.15,3.15);
    TH1F* h1D_towers_phi_em = new TH1F("h2D_towers_phi_em","",        30 ,-3.15,3.15);
    TH1F* h1D_towers_phi_had = new TH1F("h2D_towers_phi_had","",      30 ,-3.15,3.15);
    TH1F* h1D_towers_phi_outer = new TH1F("h2D_towers_phi_outer","",  30 ,-3.15,3.15);
    TH1F* h1D_pfclusters_phi = new TH1F("h2D_pfclusters_phi","",      30 ,-3.15,3.15);
    TH1F* h1D_calojets_phi = new TH1F("h2D_calojets_phi","",          30 ,-3.15,3.15);


    const char* json_file = "Run2015BGoldenPlus.txt";
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

        // if(nEventsFiltered>400000) break;
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

            //before loading next event, print out where last event failed cutflow
            // if iCut is 2 then we failed the evt_trackingFailureFilter (i.e., iCut = n means
            // we failed the filter labeled by n+1 in the cutflow printout)
            // debug << iCut << " " << evt_run() << ":" << evt_lumiBlock() << ":" << evt_event() << "\n";

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

            float caloMet = evt_metMuonCorr();
            float caloMetPhi = evt_metMuonCorrPhi();

            float pfClusterMet = pfcluster_met();
            float pfClusterMetPhi = pfcluster_metphi();

            iCut = 0;

            // use golden json file 
            if ( evt_isRealData() && !goodrun(evt_run(), evt_lumiBlock()) ) continue;

            // if( evt_run() != 251251 ) continue;
            // if( evt_run() != 251252 ) continue;
            // if( evt_run() != 251244 ) continue;


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
                for(int i = 0; i < twrs_eta().size(); i++) {
                    // float twrEta = twrs_eta().at(i);
                    // float twrPhi = twrs_phi().at(i);
                    float twrEta = twrs_etacorr().at(i);
                    float twrPhi = twrs_phicorr().at(i);
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
                // cout << pfjets_p4().at(iJet).pt() << endl;
                    if(!passesLoosePFJetID(iJet)) {
                        passJetID = false;
                        break;
                    }
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

            nEventsFiltered++;


            if(evt_run() != prevRun || evt_lumiBlock() != prevLumi) {
                runLumiOutput << evt_run() << ":" << evt_lumiBlock() << "\n";
                prevRun = evt_run();
                prevLumi = evt_lumiBlock();
            }

            // if(std::find(hlt_trigNames().begin(), hlt_trigNames().end(), "HLT_PFMET170_v1")!=hlt_trigNames().end() &&
            //    std::find(hlt_trigNames().begin(), hlt_trigNames().end(), "HLT_PFMET170_NoiseCleaned_v2")!=hlt_trigNames().end() ) {
            // }
                
            if( passHLTTrigger("HLT_PFMET170_v1") ) h1D_trig_pfMet->Fill(pfMet);
            if( passHLTTrigger("HLT_PFMET170_NoiseCleaned_v2") ) h1D_trig_pfMet_clean->Fill(pfMet);
            if( passHLTTrigger("HLT_PFMET170_v1") && passHLTTrigger("HLT_PFMET170_NoiseCleaned_v2") ) h1D_trig_pfMet_both->Fill(pfMet);
                    
            
            h1D_maxZeros_filt->Fill(hcalnoise_maxZeros());
            h1D_effbyrun_filt->Fill(runToBinMap[evt_run()]);

            // also, if we're at this point, we want to check out the events in more detail
            // if(  (caloMet > 350 || pfMet > 350) ||
            //      (caloMet > 250 && pfMet < 60) ) {
            //     std::cout << evt_run() << ":" << evt_lumiBlock() << ":" << evt_event()
            //               << " caloMet: " << caloMet << " pfMet: " << pfMet << " pfCaloMet: " << pfCaloMet << " pfChMet: " << pfChMet << " pfClusterMet: " << pfClusterMet << std::endl;
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
    std::string common = "--noStack --noFill --xAxisOverride [GeV] --type --preserveBackgroundOrder --legendTextSize 0.03 --legendRight -0.05";
    dataMCplotMaker(null, h1D_met_vec, titlesMet, "", "", common+" --overrideHeader MET (after filters) --outputName "+out+"h1D_met.pdf");

    dataMCplotMaker(null, h1D_caloMet_filters_vec, titlesFilters, "", "", common+" --overrideHeader caloMet (cumulative filters) --outputName "+out+"h1D_caloMet_filters.pdf");
    dataMCplotMaker(null, h1D_pfMet_filters_vec, titlesFilters, "", "", common+" --overrideHeader pfMet (cumulative filters) --outputName "+out+"h1D_pfMet_filters.pdf");
    dataMCplotMaker(null, h1D_pfClusterMet_filters_vec, titlesFilters, "", "", common+" --overrideHeader pfClusterMet (cumulative filters) --outputName "+out+"h1D_pfClusterMet_filters.pdf");
    dataMCplotMaker(null, h1D_pfChMet_filters_vec, titlesFilters, "", "", common+" --overrideHeader pfChMet (cumulative filters) --outputName "+out+"h1D_pfChMet_filters.pdf");
    dataMCplotMaker(null, h1D_pfCaloMet_filters_vec, titlesFilters, "", "", common+" --overrideHeader pfCaloMet (cumulative filters) --outputName "+out+"h1D_pfCaloMet_filters.pdf");

    dataMCplotMaker(null, h1D_caloMetPhi_filters_vec, titlesFilters, "", "", common+" --isLinear --overrideHeader caloMetPhi (cumulative filters) --outputName "+out+"h1D_caloMetPhi_filters.pdf");
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
    singlePlotMaker(h1D_towers_phi_had, "",common+" --overrideHeader towers phi occupancy (HCAL weighted)--outputName "+out+"h1D_towers_phi_had.pdf");
    singlePlotMaker(h1D_towers_phi_outer, "",common+" --overrideHeader towers phi occupancy (HO weighted) --outputName "+out+"h1D_towers_phi_outer.pdf");

    h1D_towers_phi_em->Divide(h1D_towers_phi);
    h1D_towers_phi_had->Divide(h1D_towers_phi);

    singlePlotMaker(h1D_towers_phi_em, "",common+" --histoErrors --overrideHeader towers phi occupancy (ECAL weighted,avg per bin) --outputName "+out+"h1D_towers_phi_em_avg.pdf");
    singlePlotMaker(h1D_towers_phi_had, "",common+" --histoErrors --overrideHeader towers phi occupancy (HCAL weighted,avg per bin)--outputName "+out+"h1D_towers_phi_had_avg.pdf");

    std::string runBinLabels = "";
    for(int i = 0; i < binToRunMap.size(); i++) {
            runBinLabels += to_string(binToRunMap[i]) + ",";
    }
    // h1D_effbyrun_vec.at(0)->GetXaxis()->SetLimits(0,25);
    // h1D_effbyrun_vec.at(1)->GetXaxis()->SetLimits(0,25);
    // std::cout << " h1D_effbyrun_vec.at(0)->GetXaxis()->GetXmax(): " << h1D_effbyrun_vec.at(0)->GetXaxis()->GetXmax() << " h1D_effbyrun_vec.at(1)->GetXaxis()->GetXmax(): " << h1D_effbyrun_vec.at(1)->GetXaxis()->GetXmax() << std::endl;
    dataMCplotMaker(null, h1D_effbyrun_vec, titlesOnesFilt, "", "", common+" --overrideHeader filter efficiency by run  --xAxisVerticalBinLabels --xAxisBinLabels "+runBinLabels+" --outputName "+out+"h1D_effbyrun.pdf");

    std::string binLabels = "EBp,EBm,EEp,EEm,_,HBHEa,HBHEb,HBHEc,HF,HO,_,_,RPC,DT0,DTp,DTm,CSCp,CSCm,_,_,CASTOR,_,ZDC,_,TIBTID,TOB,TECp,TECm,BPIX,FPIX,ESp,ESm";
    dataMCplotMaker(null, h1D_detectorStatus_vec, titlesDCS, "", "", common+"  --overrideHeader DCS bits --nDivisions 216 --xAxisVerticalBinLabels --xAxisBinLabels "+binLabels+" --outputName "+out+"h1D_detectorStatus.pdf");

    return 0;
}
