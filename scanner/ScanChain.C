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
    titlesMet.push_back("pfClusterMet");

    float lowerMet = 0.0;
    float upperMet = 400.0;
    int metBins = 80;

    // met with no filters
    TH1F *h1D_pfCaloMet = new TH1F("h1D_pfCaloMet", "", metBins,lowerMet,upperMet);
    TH1F *h1D_pfMet = new TH1F("h1D_pfMet", "", metBins,lowerMet,upperMet);
    TH1F *h1D_caloMet = new TH1F("h1D_caloMet", "", metBins,lowerMet,upperMet);
    TH1F *h1D_pfClusterMet = new TH1F("h1D_pfClusterMet", "", metBins,lowerMet,upperMet);

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
    TH2F* h2D_towers_etaphi = new TH2F("h2D_towers_etaphi","",         50,-2.4,2.4, 50,-3.15,3.15);
    TH2F* h2D_pfclusters_etaphi = new TH2F("h2D_pfclusters_etaphi","", 50,-2.4,2.4, 50,-3.15,3.15);
    TH2F* h2D_calojets_etaphi = new TH2F("h2D_calojets_etaphi","",     50,-2.4,2.4, 50,-3.15,3.15);


    // filters
    std::vector<std::string> titlesFilters;
    titlesFilters.push_back(" NO filter");
    titlesFilters.push_back("+cscTightHalo");
    titlesFilters.push_back("+hcalNoise");
    titlesFilters.push_back("+hbheRun2Tight");

    // caloMet with filters layered
    std::vector<TH1F*> h1D_caloMet_filters_vec;
    TH1F *h1D_caloMet_halo = new TH1F("h1D_caloMet_halo", "", metBins,lowerMet,upperMet);
    TH1F *h1D_caloMet_halonoise = new TH1F("h1D_caloMet_halonoise", "", metBins,lowerMet,upperMet);
    TH1F *h1D_caloMet_halonoisehbhe = new TH1F("h1D_caloMet_halonoisehbhe", "", metBins,lowerMet,upperMet);
    h1D_caloMet_filters_vec.push_back(h1D_caloMet);
    h1D_caloMet_filters_vec.push_back(h1D_caloMet_halo);
    h1D_caloMet_filters_vec.push_back(h1D_caloMet_halonoise);
    h1D_caloMet_filters_vec.push_back(h1D_caloMet_halonoisehbhe);

    // pfCaloMet with filters layered
    std::vector<TH1F*> h1D_pfCaloMet_filters_vec;
    TH1F *h1D_pfCaloMet_halo = new TH1F("h1D_pfCaloMet_halo", "", metBins,lowerMet,upperMet);
    TH1F *h1D_pfCaloMet_halonoise = new TH1F("h1D_pfCaloMet_halonoise", "", metBins,lowerMet,upperMet);
    TH1F *h1D_pfCaloMet_halonoisehbhe = new TH1F("h1D_pfCaloMet_halonoisehbhe", "", metBins,lowerMet,upperMet);
    h1D_pfCaloMet_filters_vec.push_back(h1D_pfCaloMet);
    h1D_pfCaloMet_filters_vec.push_back(h1D_pfCaloMet_halo);
    h1D_pfCaloMet_filters_vec.push_back(h1D_pfCaloMet_halonoise);
    h1D_pfCaloMet_filters_vec.push_back(h1D_pfCaloMet_halonoisehbhe);

    // pfMet with filters layered
    std::vector<TH1F*> h1D_pfMet_filters_vec;
    TH1F *h1D_pfMet_halo = new TH1F("h1D_pfMet_halo", "", metBins,lowerMet,upperMet);
    TH1F *h1D_pfMet_halonoise = new TH1F("h1D_pfMet_halonoise", "", metBins,lowerMet,upperMet);
    TH1F *h1D_pfMet_halonoisehbhe = new TH1F("h1D_pfMet_halonoisehbhe", "", metBins,lowerMet,upperMet);
    h1D_pfMet_filters_vec.push_back(h1D_pfMet);
    h1D_pfMet_filters_vec.push_back(h1D_pfMet_halo);
    h1D_pfMet_filters_vec.push_back(h1D_pfMet_halonoise);
    h1D_pfMet_filters_vec.push_back(h1D_pfMet_halonoisehbhe);

    // pfClusterMet with filters layered
    std::vector<TH1F*> h1D_pfClusterMet_filters_vec;
    TH1F *h1D_pfClusterMet_halo = new TH1F("h1D_pfClusterMet_halo", "", metBins,lowerMet,upperMet);
    TH1F *h1D_pfClusterMet_halonoise = new TH1F("h1D_pfClusterMet_halonoise", "", metBins,lowerMet,upperMet);
    TH1F *h1D_pfClusterMet_halonoisehbhe = new TH1F("h1D_pfClusterMet_halonoisehbhe", "", metBins,lowerMet,upperMet);
    h1D_pfClusterMet_filters_vec.push_back(h1D_pfClusterMet);
    h1D_pfClusterMet_filters_vec.push_back(h1D_pfClusterMet_halo);
    h1D_pfClusterMet_filters_vec.push_back(h1D_pfClusterMet_halonoise);
    h1D_pfClusterMet_filters_vec.push_back(h1D_pfClusterMet_halonoisehbhe);

    // all met after filters
    std::vector<TH1F*> h1D_met_vec;
    h1D_met_vec.push_back(h1D_pfCaloMet_halonoisehbhe);
    h1D_met_vec.push_back(h1D_pfMet_halonoisehbhe);
    h1D_met_vec.push_back(h1D_caloMet_halonoisehbhe);
    h1D_met_vec.push_back(h1D_pfClusterMet_halonoisehbhe);


    // dPhi(leading jet,caloMet)
    std::vector<TH1F*> h1D_jetCaloMetPhi_filters_vec;
    TH1F *h1D_jetCaloMetPhi               = new TH1F("h1D_jetCaloMetPhi", "",               70,0,3.5);
    TH1F *h1D_jetCaloMetPhi_halo          = new TH1F("h1D_jetCaloMetPhi_halo", "",          70,0,3.5);
    TH1F *h1D_jetCaloMetPhi_halonoise     = new TH1F("h1D_jetCaloMetPhi_halonoise", "",     70,0,3.5);
    TH1F *h1D_jetCaloMetPhi_halonoisehbhe = new TH1F("h1D_jetCaloMetPhi_halonoisehbhe", "", 70,0,3.5);
    h1D_jetCaloMetPhi_filters_vec.push_back(h1D_jetCaloMetPhi);
    h1D_jetCaloMetPhi_filters_vec.push_back(h1D_jetCaloMetPhi_halo);
    h1D_jetCaloMetPhi_filters_vec.push_back(h1D_jetCaloMetPhi_halonoise);
    h1D_jetCaloMetPhi_filters_vec.push_back(h1D_jetCaloMetPhi_halonoisehbhe);

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

            h1D_pfCaloMet->Fill(pfCaloMet_met());
            h1D_pfMet->Fill(pfMet_met());
            h1D_caloMet->Fill(evt_met());
            h1D_pfClusterMet->Fill(pfcluster_met());

            if( !fast ) {
                for(int i = 0; i < twrs_eta().size(); i++)      h2D_towers_etaphi->Fill(twrs_eta().at(i), twrs_phi().at(i));
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

            for(int iDet = 0; iDet < 32; iDet++) {
                if( evt_detectorStatus() & (1 << iDet) ) h1D_detectorStatus->Fill(iDet);
            }

            float dPhiCaloMet = deltaPhi(leadingJetPhi, evt_metPhi());
            if(dPhiCaloMet < M_PI) h1D_jetCaloMetPhi->Fill(dPhiCaloMet);


            // require that all subsystems systems are functional
            // don't judge the hardcoding :(
            bool dcsFunctional = true;
            if( ! ( evt_detectorStatus() & (1 << 0  ) ) ) dcsFunctional = false;
            if( ! ( evt_detectorStatus() & (1 << 1  ) ) ) dcsFunctional = false;
            if( ! ( evt_detectorStatus() & (1 << 2  ) ) ) dcsFunctional = false;
            if( ! ( evt_detectorStatus() & (1 << 3  ) ) ) dcsFunctional = false;
            if( ! ( evt_detectorStatus() & (1 << 5  ) ) ) dcsFunctional = false;
            if( ! ( evt_detectorStatus() & (1 << 6  ) ) ) dcsFunctional = false;
            if( ! ( evt_detectorStatus() & (1 << 7  ) ) ) dcsFunctional = false;
            if( ! ( evt_detectorStatus() & (1 << 8  ) ) ) dcsFunctional = false;
            if( ! ( evt_detectorStatus() & (1 << 9  ) ) ) dcsFunctional = false;
            if( ! ( evt_detectorStatus() & (1 << 12 ) ) ) dcsFunctional = false;
            if( ! ( evt_detectorStatus() & (1 << 13 ) ) ) dcsFunctional = false;
            if( ! ( evt_detectorStatus() & (1 << 14 ) ) ) dcsFunctional = false;
            if( ! ( evt_detectorStatus() & (1 << 15 ) ) ) dcsFunctional = false;
            if( ! ( evt_detectorStatus() & (1 << 16 ) ) ) dcsFunctional = false;
            if( ! ( evt_detectorStatus() & (1 << 17 ) ) ) dcsFunctional = false;
            if( ! ( evt_detectorStatus() & (1 << 24 ) ) ) dcsFunctional = false;
            if( ! ( evt_detectorStatus() & (1 << 25 ) ) ) dcsFunctional = false;
            if( ! ( evt_detectorStatus() & (1 << 26 ) ) ) dcsFunctional = false;
            if( ! ( evt_detectorStatus() & (1 << 27 ) ) ) dcsFunctional = false;
            if( ! ( evt_detectorStatus() & (1 << 28 ) ) ) dcsFunctional = false;
            if( ! ( evt_detectorStatus() & (1 << 29 ) ) ) dcsFunctional = false;
            if( ! ( evt_detectorStatus() & (1 << 30 ) ) ) dcsFunctional = false;
            if( ! ( evt_detectorStatus() & (1 << 31 ) ) ) dcsFunctional = false;
            if( ! dcsFunctional ) continue;

            if ( !evt_cscTightHaloFilter() ) continue; // XXX

            h1D_pfCaloMet_halo->Fill(pfCaloMet_met());
            h1D_pfMet_halo->Fill(pfMet_met());
            h1D_caloMet_halo->Fill(evt_met());
            h1D_pfClusterMet_halo->Fill(pfcluster_met());
            if(dPhiCaloMet < M_PI) h1D_jetCaloMetPhi_halo->Fill(dPhiCaloMet);

            if ( !hcalnoise_passTightNoiseFilter() ) continue; // XXX

            h1D_pfCaloMet_halonoise->Fill(pfCaloMet_met());
            h1D_pfMet_halonoise->Fill(pfMet_met());
            h1D_caloMet_halonoise->Fill(evt_met());
            h1D_pfClusterMet_halonoise->Fill(pfcluster_met());
            if(dPhiCaloMet < M_PI) h1D_jetCaloMetPhi_halonoise->Fill(dPhiCaloMet);

            if ( !evt_hbheFilterRun2Tight() ) continue; // XXX

            h1D_pfCaloMet_halonoisehbhe->Fill(pfCaloMet_met());
            h1D_pfMet_halonoisehbhe->Fill(pfMet_met());
            h1D_caloMet_halonoisehbhe->Fill(evt_met());
            h1D_pfClusterMet_halonoisehbhe->Fill(pfcluster_met());
            if(dPhiCaloMet < M_PI) h1D_jetCaloMetPhi_halonoisehbhe->Fill(dPhiCaloMet);


            for(int iDet = 0; iDet < 32; iDet++) {
                if( evt_detectorStatus() & (1 << iDet) ) h1D_detectorStatus_filt->Fill(iDet);
            }


            h2D_pfCaloMet_pfMet->Fill(pfCaloMet_met(), pfMet_met());
            h2D_pfCaloMet_caloMet->Fill(pfCaloMet_met(), evt_met());
            h2D_caloMet_pfMet->Fill(evt_met(), pfMet_met());
            h2D_pfClusterMet_pfMet->Fill(pfcluster_met(),pfMet_met());
            h2D_pfClusterMet_caloMet->Fill(pfcluster_met(),evt_met());
            h2D_pfClusterMet_pfCaloMet->Fill(pfcluster_met(),pfCaloMet_met());
            h2D_pfCaloMet_pfMet->Fill(pfCaloMet_met(), pfMet_met());
            h2D_pfCaloMet_caloMet->Fill(pfCaloMet_met(), evt_met());
            h2D_caloMet_pfMet->Fill(evt_met(), pfMet_met());
            h2D_jetPt_caloMet->Fill(leadingJetPt, evt_met());

            nEventsFiltered++;

            // also, if we're at this point, we want to check out the events in more detail

            float thresh = 1200;
            if( evt_met()>thresh || pfCaloMet_met()>thresh || pfcluster_met()>thresh || pfMet_met()>thresh ) {
                std::cout << evt_run() << ":" << evt_lumiBlock() << ":" << evt_event() << " caloMet: " << evt_met() << " pfCaloMet: " << pfCaloMet_met() << " pfClusterMet: " << pfcluster_met() << " pfMet: " << pfMet_met() << std::endl;
            }

            if( evt_met() > 70 && pfMet_met() < 20 )
                std::cout << evt_run() << ":" << evt_lumiBlock() << ":" << evt_event() << " caloMet: " << evt_met() << " pfCaloMet: " << pfCaloMet_met() << " pfClusterMet: " << pfcluster_met() << " pfMet: " << pfMet_met() << std::endl;

            if( evt_met() < 20 && pfcluster_met() > 60 )
                std::cout << evt_run() << ":" << evt_lumiBlock() << ":" << evt_event() << " caloMet: " << evt_met() << " pfCaloMet: " << pfCaloMet_met() << " pfClusterMet: " << pfcluster_met() << " pfMet: " << pfMet_met() << std::endl;

            if( pfCaloMet_met() > 110 && evt_met() < 20 )
                std::cout << evt_run() << ":" << evt_lumiBlock() << ":" << evt_event() << " caloMet: " << evt_met() << " pfCaloMet: " << pfCaloMet_met() << " pfClusterMet: " << pfcluster_met() << " pfMet: " << pfMet_met() << std::endl;

            if( pfcluster_met() > 60 && pfCaloMet_met() < 10 )
                std::cout << evt_run() << ":" << evt_lumiBlock() << ":" << evt_event() << " caloMet: " << evt_met() << " pfCaloMet: " << pfCaloMet_met() << " pfClusterMet: " << pfcluster_met() << " pfMet: " << pfMet_met() << std::endl;

            // if( pfCaloMet_met() > 220 && pfMet_met() > 160 )
            if( evt_met() > 150 )
                std::cout << evt_run() << ":" << evt_lumiBlock() << ":" << evt_event() << " caloMet: " << evt_met() << " pfCaloMet: " << pfCaloMet_met() << " pfClusterMet: " << pfcluster_met() << " pfMet: " << pfMet_met() << std::endl;

        }

        // Clean Up
        delete tree;
        file->Close();
        delete file;
    }

    std::cout << " nEventsChain: " << nEventsChain << " nEventsFiltered: " << nEventsFiltered << std::endl;

    std::string out = "pdfs/";
    std::string common = "--noStack --noFill --xAxisOverride [GeV] --type --preserveBackgroundOrder --legendTextSize 0.03 --legendRight -0.05";
    dataMCplotMaker(null, h1D_met_vec, titlesMet, "", "", common+" --overrideHeader MET (after filters) --outputName "+out+"h1D_met.pdf");

    dataMCplotMaker(null, h1D_caloMet_filters_vec, titlesFilters, "", "", common+" --overrideHeader caloMet (cumulative filters) --outputName "+out+"h1D_caloMet_filters.pdf");
    dataMCplotMaker(null, h1D_pfMet_filters_vec, titlesFilters, "", "", common+" --overrideHeader pfMet (cumulative filters) --outputName "+out+"h1D_pfMet_filters.pdf");
    dataMCplotMaker(null, h1D_pfClusterMet_filters_vec, titlesFilters, "", "", common+" --overrideHeader pfClusterMet (cumulative filters) --outputName "+out+"h1D_pfClusterMet_filters.pdf");
    dataMCplotMaker(null, h1D_pfCaloMet_filters_vec, titlesFilters, "", "", common+" --overrideHeader pfCaloMet (cumulative filters) --outputName "+out+"h1D_pfCaloMet_filters.pdf");

    dataMCplotMaker(null, h1D_jetCaloMetPhi_filters_vec, titlesFilters, "", "", common+"  --overrideHeader #Delta#phi(j,caloMet) (cumulative filters) --xAxisOverride #phi --outputName "+out+"h1D_jetCaloMetPhi_filters.pdf");

    drawHist2D(h2D_pfClusterMet_pfCaloMet,out+"h2D_pfClusterMet_pfCaloMet.pdf",    "--logscale --title pfCaloMet vs pfClusterMet --xlabel pfClusterMet --ylabel pfCaloMet");
    drawHist2D(h2D_pfClusterMet_caloMet,out+"h2D_pfClusterMet_caloMet.pdf","--logscale --title caloMet vs pfClusterMet --xlabel pfClusterMet --ylabel caloMet");
    drawHist2D(h2D_pfClusterMet_pfMet,out+"h2D_pfClusterMet_pfMet.pdf","--logscale --title pfMet vs pfClusterMet --xlabel  pfClusterMet --ylabel pfMet");
    drawHist2D(h2D_pfCaloMet_pfMet,out+"h2D_pfCaloMet_pfMet.pdf",    "--logscale --title pfMet vs pfCaloMet --xlabel pfCaloMet_met --ylabel pfMet_met");
    drawHist2D(h2D_pfCaloMet_caloMet,out+"h2D_pfCaloMet_caloMet.pdf","--logscale --title caloMet vs pfCaloMet --xlabel pfCaloMet_met --ylabel caloMet");
    drawHist2D(h2D_caloMet_pfMet,out+"h2D_caloMet_pfMet.pdf","--logscale --title pfMet vs caloMet --xlabel  caloMet --ylabel pfMet");

    drawHist2D(h2D_jetPt_caloMet,out+"h2D_jetPt_caloMet.pdf","--logscale --title caloMet vs leading jet pT --xlabel  jetPt --ylabel caloMet");

    drawHist2D(h2D_towers_etaphi,out+"h2D_towers_etaphi.pdf","--logscale --title towers --xlabel  #eta --ylabel #phi");
    drawHist2D(h2D_pfclusters_etaphi,out+"h2D_pfclusters_etaphi.pdf","--logscale --title pfclusters --xlabel  #eta --ylabel #phi");
    drawHist2D(h2D_calojets_etaphi,out+"h2D_calojets_etaphi.pdf","--logscale --title calojets --xlabel  #eta --ylabel #phi");

    std::string binLabels = "EBp,EBm,EEp,EEm,_,HBHEa,HBHEb,HBHEc,HF,HO,_,_,RPC,DT0,DTp,DTm,CSCp,CSCm,_,_,CASTOR,_,ZDC,_,TIBTID,TOB,TECp,TECm,BPIX,FPIX,ESp,ESm";
    dataMCplotMaker(null, h1D_detectorStatus_vec, titlesDCS, "", "", common+"  --overrideHeader DCS bits --nDivisions 216 --xAxisVerticalBinLabels --xAxisBinLabels "+binLabels+" --outputName "+out+"h1D_detectorStatus.pdf");

    return 0;
}
