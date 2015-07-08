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
