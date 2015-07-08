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

#include "CMS3.cc"

using namespace std;
using namespace tas;

int RunLumis( TChain* chain) {

    unsigned int nEventsTotal = 0;
    unsigned int nEventsChain = chain->GetEntries();

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

        int prevRun = -1;
        int prevLumi = -1;
        for( unsigned int event = 0; event < nEventsTree; ++event) {

            // Get Event Content
            if( nEventsTotal >= nEventsChain ) continue;
            tree->LoadTree(event);
            cms3.GetEntry(event);
            ++nEventsTotal;
            // CMS3::progress( nEventsTotal, nEventsChain );

            // Analysis Code
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
            if ( !hcalnoise_passTightNoiseFilter() ) continue; // XXX
            if ( !evt_hbheFilterRun2Tight() ) continue; // XXX

            if(prevRun != evt_run() || prevLumi != evt_lumiBlock()) {
                std::cout << evt_run() << " " << evt_lumiBlock() << std::endl;
                prevRun = evt_run();
                prevLumi = evt_lumiBlock();
            }

        }

        // Clean Up
        delete tree;
        file->Close();
        delete file;
    }


    return 0;
}
