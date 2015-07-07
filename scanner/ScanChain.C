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
    // float upperMet = 2000.0;
    // int metBins = 50;
    float upperMet = 350.0;
    int metBins = 70;

    std::vector<TH1F*> h1D_met_vec;
    TH1F *h1D_pfCaloMet = new TH1F("h1D_pfCaloMet", "", metBins,lowerMet,upperMet);
    TH1F *h1D_pfMet = new TH1F("h1D_pfMet", "", metBins,lowerMet,upperMet);
    TH1F *h1D_caloMet = new TH1F("h1D_caloMet", "", metBins,lowerMet,upperMet);
    TH1F *h1D_pfClusterMet = new TH1F("h1D_pfClusterMet", "", metBins,lowerMet,upperMet);
    h1D_met_vec.push_back(h1D_pfCaloMet);
    h1D_met_vec.push_back(h1D_pfMet);
    h1D_met_vec.push_back(h1D_caloMet);
    h1D_met_vec.push_back(h1D_pfClusterMet);

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
    // twrs_eta twrs_phi pfcluster_eta pfcluster_phi  calojets_eta calojets_phi
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

    std::cout << "Running over " << nEventsChain << " events." << std::endl;

    cms3.Init(chain);
    for( unsigned int event = 0; event < nEventsChain; ++event) {
        // if(event > 10) break; // XXX
        // std::cout << " evt_event(): " << evt_event() << " evt_met(): " << evt_met() << " evt_metPhi(): " << evt_metPhi() << std::endl;

        cms3.GetEntry(event);
        ++nEventsTotal;
        CMS3::progress( nEventsTotal, nEventsChain );

        // NOTE: get rid of "bad" events?
        // if(fabs(evt_metPhi()) < 0.000001 && evt_met() < 0.000001) continue;

        h1D_pfCaloMet->Fill(pfCaloMet_met());
        h1D_pfMet->Fill(pfMet_met());
        h1D_caloMet->Fill(evt_met());
        h1D_pfClusterMet->Fill(pfcluster_met());

        // twrs_eta twrs_phi pfcluster_eta pfcluster_phi  calojets_eta calojets_phi
        // for(int i = 0; i < twrs_eta().size(); i++)      h2D_towers_etaphi->Fill(twrs_eta().at(i), twrs_phi().at(i));
        // for(int i = 0; i < pfcluster_eta().size(); i++) h2D_pfclusters_etaphi->Fill(pfcluster_eta().at(i), pfcluster_phi().at(i));
        // for(int i = 0; i < calojets_eta().size(); i++)  h2D_calojets_etaphi->Fill(calojets_eta().at(i), calojets_phi().at(i));

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

        if ( !evt_cscTightHaloFilter() ) continue; // XXX

        h1D_pfCaloMet_halo->Fill(pfCaloMet_met());
        h1D_pfMet->Fill(pfMet_met());
        h1D_caloMet_halo->Fill(evt_met());
        if(dPhiCaloMet < M_PI) h1D_jetCaloMetPhi_halo->Fill(dPhiCaloMet);

        if ( !hcalnoise_passTightNoiseFilter() ) continue; // XXX

        h1D_pfCaloMet_halonoise->Fill(pfCaloMet_met());
        h1D_pfMet->Fill(pfMet_met());
        h1D_caloMet_halonoise->Fill(evt_met());
        if(dPhiCaloMet < M_PI) h1D_jetCaloMetPhi_halonoise->Fill(dPhiCaloMet);

        if ( !evt_hbheFilterRun2Tight() ) continue; // XXX

        h1D_pfCaloMet_halonoisehbhe->Fill(pfCaloMet_met());
        h1D_pfMet->Fill(pfMet_met());
        h1D_caloMet_halonoisehbhe->Fill(evt_met());
        if(dPhiCaloMet < M_PI) h1D_jetCaloMetPhi_halonoisehbhe->Fill(dPhiCaloMet);

        for(int iDet = 0; iDet < 32; iDet++) {
            if( evt_detectorStatus() & (1 << iDet) ) h1D_detectorStatus_filt->Fill(iDet);
        }

        // also, if we're at this point, we want to check out the events in more detail if met is high enough

        float thresh = 1200;
        if( evt_met()>thresh || pfCaloMet_met()>thresh || pfcluster_met()>thresh || pfMet_met()>thresh ) {
            std::cout << evt_run() << ":" << evt_lumiBlock() << ":" << evt_event() << " evt_met(): " << evt_met() << " pfCaloMet_met(): " << pfCaloMet_met() << " pfcluster_met(): " << pfcluster_met() << " pfMet_met(): " << pfMet_met() << std::endl;
        }

    }

    int binmax = h1D_jetCaloMetPhi_filters_vec.at(0)->GetMaximumBin();
    double x = h1D_jetCaloMetPhi_filters_vec.at(0)->GetXaxis()->GetBinCenter(binmax);
    std::cout << " binmax: " << binmax << " x: " << x << std::endl;

    std::string out = "pdfs/";
    std::string common = "--noStack --noFill --xAxisOverride [GeV] --type --preserveBackgroundOrder --legendTextSize 0.03 --legendRight -0.05";
    dataMCplotMaker(null, h1D_met_vec, titlesMet, "", "", common+" --overrideHeader MET --outputName "+out+"h1D_met.pdf");
    dataMCplotMaker(null, h1D_caloMet_filters_vec, titlesFilters, "", "", common+" --overrideHeader caloMet (cumulative filters) --outputName "+out+"h1D_caloMet_filters.pdf");
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
