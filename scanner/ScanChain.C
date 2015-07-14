#pragma GCC diagnostic ignored "-Wsign-compare"
#include <iostream>
#include <fstream>
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
    runLumiOutput.open("runLumiOutput.txt");
    initCounter();

    TH1F* null = new TH1F("","",1,0,1);

    // comparison of METs
    std::vector<std::string> titlesMet;
    titlesMet.push_back("pfCaloMet");
    titlesMet.push_back("pfMet");
    titlesMet.push_back("caloMet");
    titlesMet.push_back("pfClusterMet");
    titlesMet.push_back("pfChMet");

    float lowerMet = 0.0;
    float upperMet = 500.0;
    int metBins = 60;

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
    std::vector<std::string> titlesLeadingJet;
    titlesLeadingJet.push_back("leading PF jet");
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

    // detector status
    std::vector<TH1F*> h1D_detectorStatus_vec;
    std::vector<std::string> titlesDCS;
    TH1F *h1D_detectorStatus = new TH1F("h1D_detectorStatus","", 32,0,32);
    TH1F *h1D_detectorStatus_filt = new TH1F("h1D_detectorStatus_filt","", 32,0,32);
    h1D_detectorStatus_vec.push_back(h1D_detectorStatus);
    h1D_detectorStatus_vec.push_back(h1D_detectorStatus_filt);
    titlesDCS.push_back("DCS bits (no filters)");
    titlesDCS.push_back("DCS bits (filters)");

    unsigned int nEventsTotal = 0;
    unsigned int nEventsChain = chain->GetEntries();
    unsigned int nEventsFiltered = 0;

    TObjArray *listOfFiles = chain->GetListOfFiles();
    TIter fileIter(listOfFiles);
    TFile *currentFile = 0;

    // File Loop
    int prevRun = -1; int prevLumi = -1;
    while ( (currentFile = (TFile*)fileIter.Next()) ) {

        // Get File Content
        TFile *file = new TFile( currentFile->GetTitle() );
        TTree *tree = (TTree*)file->Get("Events");
        TTreeCache::SetLearnEntries(10);
        tree->SetCacheSize(128*1024*1024);
        cms3.Init(tree);

        bool fast = false;

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

            float caloMet = evt_metMuonCorr();
            float caloMetPhi = evt_metMuonCorrPhi();

            float pfClusterMet = pfcluster_met();
            float pfClusterMetPhi = pfcluster_metphi();

            h1D_pfCaloMet->Fill(pfCaloMet);
            h1D_pfMet->Fill(pfMet);
            h1D_caloMet->Fill(caloMet);
            h1D_pfClusterMet->Fill(pfClusterMet);
            h1D_pfChMet->Fill(pfChMet);

            if( !fast ) {
                for(int i = 0; i < twrs_eta().size(); i++) {
                    h2D_towers_etaphi->Fill(twrs_eta().at(i), twrs_phi().at(i));
                    h2D_towers_etaphi_em->Fill(twrs_eta().at(i), twrs_phi().at(i), twrs_emEnergy().at(i));
                    h2D_towers_etaphi_had->Fill(twrs_eta().at(i), twrs_phi().at(i), twrs_hadEnergy().at(i));
                    h2D_towers_etaphi_outer->Fill(twrs_eta().at(i), twrs_phi().at(i), twrs_outerEnergy().at(i));
                }   

                for(int i = 0; i < pfcluster_eta().size(); i++) h2D_pfclusters_etaphi->Fill(pfcluster_eta().at(i), pfcluster_phi().at(i));
                for(int i = 0; i < calojets_eta().size(); i++)  h2D_calojets_etaphi->Fill(calojets_eta().at(i), calojets_phi().at(i));
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


            addToCounter("ALL");
            // DCS AND TRACKS FILTER
            if ( ! haveFunctionalDCS() ) continue;
            addToCounter("haveFunctionalDCS()");
            if ( ! evt_trackingFailureFilter() ) continue;
            addToCounter("evt_trackingFailureFilter()");
            if ( evt_ntracks() < 4 ) continue;
            addToCounter("evt_ntracks()<4");

            // if(evt_run() != prevRun || evt_lumiBlock() != prevLumi) {
            //     runLumiOutput << evt_run() << ":" << evt_lumiBlock() << "\n";
            //     prevRun = evt_run();
            //     prevLumi = evt_lumiBlock();
            // }


            // CSC HALO FILTER
            if ( !evt_cscTightHaloFilter() ) continue;
            addToCounter("evt_cscTightHaloFilter()");

            h1D_pfCaloMet_halo->Fill(pfCaloMet);
            h1D_pfMet_halo->Fill(pfMet);
            h1D_caloMet_halo->Fill(caloMet);
            h1D_pfClusterMet_halo->Fill(pfClusterMet);
            h1D_pfChMet_halo->Fill(pfChMet);
            if(dPhiCaloMet < M_PI) h1D_jetCaloMetPhi_halo->Fill(dPhiCaloMet);


            // HCAL NOISE FILTERS
            if ( !hbheIsoNoiseFilter() ) continue;
            addToCounter("hbheIsoNoiseFilter()");
            if ( !hcalnoise_passTightNoiseFilter() ) continue; 
            addToCounter("hcalnoise_passTightNoiseFilter())");

            h1D_pfCaloMet_halonoise->Fill(pfCaloMet);
            h1D_pfMet_halonoise->Fill(pfMet);
            h1D_caloMet_halonoise->Fill(caloMet);
            h1D_pfClusterMet_halonoise->Fill(pfClusterMet);
            h1D_pfChMet_halonoise->Fill(pfChMet);
            if(dPhiCaloMet < M_PI) h1D_jetCaloMetPhi_halonoise->Fill(dPhiCaloMet);


            // HCAL FILTER 50NS
            if ( !evt_hbheFilterRun1() ) continue;
            addToCounter("evt_hbheFilterRun1()");

            h1D_pfCaloMet_halonoisehbhe->Fill(pfCaloMet);
            h1D_pfMet_halonoisehbhe->Fill(pfMet);
            h1D_caloMet_halonoisehbhe->Fill(caloMet);
            h1D_pfClusterMet_halonoisehbhe->Fill(pfClusterMet);
            h1D_pfChMet_halonoisehbhe->Fill(pfChMet);
            if(dPhiCaloMet < M_PI) h1D_jetCaloMetPhi_halonoisehbhe->Fill(dPhiCaloMet);


            // ECAL FILTERS
            if ( !evt_EcalDeadCellTriggerPrimitiveFilter() ) continue;
            addToCounter("evt_EcalDeadCellTriggerPrimitiveFilter()");
            if ( !evt_eeBadScFilter() ) continue;
            addToCounter("evt_eeBadScFilter()");

            h1D_pfCaloMet_halonoisehbheecal->Fill(pfCaloMet);
            h1D_pfMet_halonoisehbheecal->Fill(pfMet);
            h1D_caloMet_halonoisehbheecal->Fill(caloMet);
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

            if( !passJetID ) continue;
            addToCounter("passJetID");

            h1D_pfCaloMet_halonoisehbheecaljet->Fill(pfCaloMet);
            h1D_pfMet_halonoisehbheecaljet->Fill(pfMet);
            h1D_caloMet_halonoisehbheecaljet->Fill(caloMet);
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

            // also, if we're at this point, we want to check out the events in more detail
            if(  (caloMet > 290 && pfMet > 290) ||
                 (caloMet > 100 && pfMet < 30)  ||
                 (caloMet < 20  && pfMet > 100) ) {
                std::cout << evt_run() << ":" << evt_lumiBlock() << ":" << evt_event()
                          << " caloMet: " << caloMet << " pfMet: " << pfMet << " pfCaloMet: " << pfCaloMet << " pfChMet: " << pfChMet << " pfClusterMet: " << pfClusterMet << std::endl;
            }

        }

        // Clean Up
        delete tree;
        file->Close();
        delete file;
    }

    runLumiOutput.close();
    printCounter();

    std::cout << " nEventsChain: " << nEventsChain << " nEventsFiltered: " << nEventsFiltered << std::endl;

    std::string out = "pdfs/";
    std::string common = "--noStack --noFill --xAxisOverride [GeV] --type --preserveBackgroundOrder --legendTextSize 0.03 --legendRight -0.05";
    dataMCplotMaker(null, h1D_met_vec, titlesMet, "", "", common+" --overrideHeader MET (after filters) --outputName "+out+"h1D_met.pdf");

    dataMCplotMaker(null, h1D_caloMet_filters_vec, titlesFilters, "", "", common+" --overrideHeader caloMet (cumulative filters) --outputName "+out+"h1D_caloMet_filters.pdf");
    dataMCplotMaker(null, h1D_pfMet_filters_vec, titlesFilters, "", "", common+" --overrideHeader pfMet (cumulative filters) --outputName "+out+"h1D_pfMet_filters.pdf");
    dataMCplotMaker(null, h1D_pfClusterMet_filters_vec, titlesFilters, "", "", common+" --overrideHeader pfClusterMet (cumulative filters) --outputName "+out+"h1D_pfClusterMet_filters.pdf");
    dataMCplotMaker(null, h1D_pfChMet_filters_vec, titlesFilters, "", "", common+" --overrideHeader pfChMet (cumulative filters) --outputName "+out+"h1D_pfChMet_filters.pdf");
    dataMCplotMaker(null, h1D_pfCaloMet_filters_vec, titlesFilters, "", "", common+" --overrideHeader pfCaloMet (cumulative filters) --outputName "+out+"h1D_pfCaloMet_filters.pdf");

    dataMCplotMaker(null, h1D_jetCaloMetPhi_filters_vec, titlesFilters, "", "", common+"  --overrideHeader #Delta#phi(j,caloMet) (cumulative filters) --xAxisOverride #phi --outputName "+out+"h1D_jetCaloMetPhi_filters.pdf");

    dataMCplotMaker(null, h1D_leadingJet_chf_vec, titlesLeadingJet, "", "", common+"  --overrideHeader charged hadron fraction (no filters) --xAxisOverride fraction --outputName "+out+"h1D_leadingJet_chf_vec.pdf");
    dataMCplotMaker(null, h1D_leadingJet_nhf_vec, titlesLeadingJet, "", "", common+"  --overrideHeader neutral hadron fraction (no filters) --xAxisOverride fraction --outputName "+out+"h1D_leadingJet_nhf_vec.pdf");
    dataMCplotMaker(null, h1D_leadingJet_cef_vec, titlesLeadingJet, "", "", common+"  --overrideHeader charged EM fraction (no filters) --xAxisOverride fraction --outputName "+out+"h1D_leadingJet_cef_vec.pdf");
    dataMCplotMaker(null, h1D_leadingJet_nef_vec, titlesLeadingJet, "", "", common+"  --overrideHeader neutral EM fraction (no filters) --xAxisOverride fraction --outputName "+out+"h1D_leadingJet_nef_vec.pdf");
    dataMCplotMaker(null, h1D_leadingJet_cm_vec,  titlesLeadingJet, "", "", common+"  --overrideHeader charged multiplicity  (no filters) --xAxisOverride --outputName "+out+"h1D_leadingJet_cm_vec.pdf");

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

    std::string binLabels = "EBp,EBm,EEp,EEm,_,HBHEa,HBHEb,HBHEc,HF,HO,_,_,RPC,DT0,DTp,DTm,CSCp,CSCm,_,_,CASTOR,_,ZDC,_,TIBTID,TOB,TECp,TECm,BPIX,FPIX,ESp,ESm";
    dataMCplotMaker(null, h1D_detectorStatus_vec, titlesDCS, "", "", common+"  --overrideHeader DCS bits --nDivisions 216 --xAxisVerticalBinLabels --xAxisBinLabels "+binLabels+" --outputName "+out+"h1D_detectorStatus.pdf");

    return 0;
}
