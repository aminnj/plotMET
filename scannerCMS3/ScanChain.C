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

// #include "CMS3.h"
#include "../Software/dataMCplotMaker/dataMCplotMaker.h"
#include "../CORE/EventSelections.h"

using namespace std;
using namespace tas;


struct trackMetStruct {
  trackMetStruct () : met(-42.), metphi(-42.) {}
  float met;
  float metphi;
};

trackMetStruct trackMet() {

  double pX(0), pY(0);
  
  for (unsigned int i=0; i<pfcands_particleId().size(); ++i){
    if ( pfcands_charge().at(i)==0 ) continue;
    
    pX -= pfcands_p4().at(i).px();
    pY -= pfcands_p4().at(i).py();
  }
  
  trackMetStruct met;
  met.met     = sqrt(pX * pX + pY * pY);
  met.metphi  = atan2(pY, pX);
  return met;
}

int ScanChain( TChain* chain) {
    TH1F* null = new TH1F("","",1,0,1);

    // comparison of METs
    std::vector<std::string> titlesMet;
    titlesMet.push_back("tcMet");
    titlesMet.push_back("pfMet");
    titlesMet.push_back("caloMet");

    float lowerMet = 0.0;
    float upperMet = 500.0;
    int metBins = 80;

    // met with no filters
    TH1F *h1D_tcMet = new TH1F("h1D_tcMet", "", metBins,lowerMet,upperMet);
    TH1F *h1D_pfMet = new TH1F("h1D_pfMet", "", metBins,lowerMet,upperMet);
    TH1F *h1D_caloMet = new TH1F("h1D_caloMet", "", metBins,lowerMet,upperMet);

    // 2d plots of met
    TH2F* h2D_tcMet_pfMet = new TH2F("h2D_tcMet_pfMet","", metBins,lowerMet,upperMet, metBins,lowerMet,upperMet);
    TH2F* h2D_tcMet_caloMet = new TH2F("h2D_tcMet_caloMet","", metBins,lowerMet,upperMet, metBins,lowerMet,upperMet);
    TH2F* h2D_caloMet_pfMet = new TH2F("h2D_caloMet_pfMet","", metBins,lowerMet,upperMet, metBins,lowerMet,upperMet);


    // filters
    std::vector<std::string> titlesFilters;
    titlesFilters.push_back(" NO filter");
    titlesFilters.push_back("+cscTightHalo");
    titlesFilters.push_back("+hcalNoise");
    titlesFilters.push_back("+hbheFilter");

    // caloMet with filters layered
    std::vector<TH1F*> h1D_caloMet_filters_vec;
    TH1F *h1D_caloMet_halo = new TH1F("h1D_caloMet_halo", "", metBins,lowerMet,upperMet);
    TH1F *h1D_caloMet_halonoise = new TH1F("h1D_caloMet_halonoise", "", metBins,lowerMet,upperMet);
    TH1F *h1D_caloMet_halonoisehbhe = new TH1F("h1D_caloMet_halonoisehbhe", "", metBins,lowerMet,upperMet);
    h1D_caloMet_filters_vec.push_back(h1D_caloMet);
    h1D_caloMet_filters_vec.push_back(h1D_caloMet_halo);
    h1D_caloMet_filters_vec.push_back(h1D_caloMet_halonoise);
    h1D_caloMet_filters_vec.push_back(h1D_caloMet_halonoisehbhe);

    // tcMet with filters layered
    std::vector<TH1F*> h1D_tcMet_filters_vec;
    TH1F *h1D_tcMet_halo = new TH1F("h1D_tcMet_halo", "", metBins,lowerMet,upperMet);
    TH1F *h1D_tcMet_halonoise = new TH1F("h1D_tcMet_halonoise", "", metBins,lowerMet,upperMet);
    TH1F *h1D_tcMet_halonoisehbhe = new TH1F("h1D_tcMet_halonoisehbhe", "", metBins,lowerMet,upperMet);
    h1D_tcMet_filters_vec.push_back(h1D_tcMet);
    h1D_tcMet_filters_vec.push_back(h1D_tcMet_halo);
    h1D_tcMet_filters_vec.push_back(h1D_tcMet_halonoise);
    h1D_tcMet_filters_vec.push_back(h1D_tcMet_halonoisehbhe);

    // pfMet with filters layered
    std::vector<TH1F*> h1D_pfMet_filters_vec;
    TH1F *h1D_pfMet_halo = new TH1F("h1D_pfMet_halo", "", metBins,lowerMet,upperMet);
    TH1F *h1D_pfMet_halonoise = new TH1F("h1D_pfMet_halonoise", "", metBins,lowerMet,upperMet);
    TH1F *h1D_pfMet_halonoisehbhe = new TH1F("h1D_pfMet_halonoisehbhe", "", metBins,lowerMet,upperMet);
    h1D_pfMet_filters_vec.push_back(h1D_pfMet);
    h1D_pfMet_filters_vec.push_back(h1D_pfMet_halo);
    h1D_pfMet_filters_vec.push_back(h1D_pfMet_halonoise);
    h1D_pfMet_filters_vec.push_back(h1D_pfMet_halonoisehbhe);

    // all met after filters
    std::vector<TH1F*> h1D_met_vec;
    h1D_met_vec.push_back(h1D_tcMet_halonoisehbhe);
    h1D_met_vec.push_back(h1D_pfMet_halonoisehbhe);
    h1D_met_vec.push_back(h1D_caloMet_halonoisehbhe);

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

            trackMetStruct trackerMet = trackMet();
            float caloMet = evt_calomet();
            float caloMetPhi = evt_calometPhi();
            float pfMet = evt_pfmet();
            float pfMetPhi = evt_pfmetPhi();
            float tcMet = trackerMet.met;
            float tcMetPhi = trackerMet.metphi;
            // float tcMet = -1;
            // float tcMetPhi = -1;

            h1D_tcMet->Fill(tcMet);
            h1D_pfMet->Fill(pfMet);
            h1D_caloMet->Fill(caloMet);

            for(int iDet = 0; iDet < 32; iDet++) {
                if( evt_detectorStatus() & (1 << iDet) ) h1D_detectorStatus->Fill(iDet);
            }

            // require that all subsystems systems are functional
            if ( !haveFunctionalDCS() ) continue;

            // require a good vertex
            if( !filt_goodVertices() ) continue;

            if ( !filt_cscBeamHalo() ) continue; // XXX

            /// XXX ecal filter
            if ( !filt_eeBadSc() ) continue; // XXX

            h1D_tcMet_halo->Fill(tcMet);
            h1D_pfMet_halo->Fill(pfMet);
            h1D_caloMet_halo->Fill(caloMet);

            if ( !filt_hbheNoise() ) continue; // XXX

            h1D_tcMet_halonoise->Fill(tcMet);
            h1D_pfMet_halonoise->Fill(pfMet);
            h1D_caloMet_halonoise->Fill(caloMet);

            if ( !evt_hbheFilter() ) continue; // XXX

            h1D_tcMet_halonoisehbhe->Fill(tcMet);
            h1D_pfMet_halonoisehbhe->Fill(pfMet);
            h1D_caloMet_halonoisehbhe->Fill(caloMet);


            for(int iDet = 0; iDet < 32; iDet++) {
                if( evt_detectorStatus() & (1 << iDet) ) h1D_detectorStatus_filt->Fill(iDet);
            }


            h2D_tcMet_pfMet->Fill(tcMet, pfMet);
            h2D_tcMet_caloMet->Fill(tcMet, caloMet);
            h2D_caloMet_pfMet->Fill(caloMet, pfMet);
            h2D_tcMet_pfMet->Fill(tcMet, pfMet);
            h2D_tcMet_caloMet->Fill(tcMet, caloMet);
            h2D_caloMet_pfMet->Fill(caloMet, pfMet);

            nEventsFiltered++;


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
    dataMCplotMaker(null, h1D_tcMet_filters_vec, titlesFilters, "", "", common+" --overrideHeader tcMet (cumulative filters) --outputName "+out+"h1D_tcMet_filters.pdf");

    drawHist2D(h2D_tcMet_pfMet,out+"h2D_tcMet_pfMet.pdf",    "--logscale --title pfMet vs tcMet --xlabel tcMet_met --ylabel pfMet_met");
    drawHist2D(h2D_tcMet_caloMet,out+"h2D_tcMet_caloMet.pdf","--logscale --title caloMet vs tcMet --xlabel tcMet_met --ylabel caloMet");
    drawHist2D(h2D_caloMet_pfMet,out+"h2D_caloMet_pfMet.pdf","--logscale --title pfMet vs caloMet --xlabel  caloMet --ylabel pfMet");



    std::string binLabels = "EBp,EBm,EEp,EEm,_,HBHEa,HBHEb,HBHEc,HF,HO,_,_,RPC,DT0,DTp,DTm,CSCp,CSCm,_,_,CASTOR,_,ZDC,_,TIBTID,TOB,TECp,TECm,BPIX,FPIX,ESp,ESm";
    dataMCplotMaker(null, h1D_detectorStatus_vec, titlesDCS, "", "", common+"  --overrideHeader DCS bits --nDivisions 216 --xAxisVerticalBinLabels --xAxisBinLabels "+binLabels+" --outputName "+out+"h1D_detectorStatus.pdf");

    return 0;
}
