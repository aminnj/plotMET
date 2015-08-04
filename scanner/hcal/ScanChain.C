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
#include "../../Tools/goodrun.cc"

using namespace std;
using namespace tas;


int ScanChain( TChain* chain) {
    ofstream runLumiOutput;
    ofstream debug;
    TFile f("histos.root", "new");
    runLumiOutput.open("runLumiOutput.txt");
    debug.open("debug.txt");
    initCounter();

    TH1F* null = new TH1F("","",1,0,1);



    // eta-phi of towers, pfclusters, and calojets
    float maxEta = 4.5;
    TH2F* h2D_towers_etaphi = new TH2F("h2D_towers_etaphi"                                           , "" , 50 , -maxEta , maxEta , 50 , -3.15 , 3.15);
    TH2F* h2D_towers_ietaiphi = new TH2F("h2D_towers_ietaiphi"                                       , "" , 90 , -45     , 45     , 75 , 0     , 75);
    TH2F* h2D_towers_ietaiphihad = new TH2F("h2D_towers_ietaiphihad"                                 , "" , 90 , -45     , 45     , 75 , 0     , 75);
    TH2F* h2D_twrs_numProblematicHcalCells = new TH2F("h2D_twrs_numProblematicHcalCells"             , "" , 90 , -45     , 45     , 75 , 0     , 75);
    TH2F* h2D_twrs_numProblematicHcalCellsEtaPhi = new TH2F("h2D_twrs_numProblematicHcalCellsEtaPhi" , "" , 50 , -maxEta , maxEta , 50 , -3.15 , 3.15);


    const char* json_file = "Run2015BGoldenPlus_v2.txt";
    // const char* json_file = "Run2015BGolden.txt";
    set_goodrun_file(json_file);

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

            // use golden json file 
            if ( evt_isRealData() && !goodrun(evt_run(), evt_lumiBlock()) ) continue;

            if(evt_event() != 302642409) continue;

            std::cout << evt_run() << ":" << evt_lumiBlock() << ":" << evt_event() << std::endl;


            int maxIPhiHad = -1, maxIEtaHad = -1;
            float maxHadEnergy = -1;
            vector<int> badCellsPerPhiStrip(150,0); // there shouldn't be more than 150 iphi vals...
            for(int i = 0; i < twrs_eta().size(); i++) {

                float eta = twrs_etacorr().at(i);
                float phi = twrs_phicorr().at(i);

                // don't deal with HF
                if( abs(eta) > 3.0) continue;

                int ieta = twrs_ieta().at(i);
                int iphi = twrs_iphi().at(i);

                int numProbHcalCells = twrs_numProblematicHcalCells().at(i);

                if(twrs_hadEnergy().at(i) > maxHadEnergy) {
                    maxIPhiHad = iphi;
                    maxIEtaHad = ieta;
                    maxHadEnergy = twrs_hadEnergy().at(i);
                }
                if(twrs_numProblematicHcalCells().at(i) > 0) {
                    badCellsPerPhiStrip[iphi] += numProbHcalCells;
                }

                // plots
                h2D_towers_etaphi->Fill(eta, phi);
                h2D_towers_ietaiphi->Fill(ieta, iphi);
                h2D_towers_ietaiphihad->Fill(ieta, iphi, twrs_hadEnergy().at(i));
                h2D_twrs_numProblematicHcalCells->Fill(ieta, iphi, numProbHcalCells);
                h2D_twrs_numProblematicHcalCellsEtaPhi->Fill(eta, phi, numProbHcalCells);

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

                // don't deal with HF
                if( abs(twrs_etacorr().at(i)) > 3.0) continue;
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

                cout << badCellsAlongWorstPhiStrip.at(ieta) << " ";
            }
            cout << endl;


            // maxIPhiBad maxIPhiHad maxLengthBad
            std::cout << " maxIPhiBad: " << maxIPhiBad << " maxIPhiHad: " << maxIPhiHad << " maxLengthBad: " << maxLengthBad << std::endl;


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


    std::string out = "pdfs/";

    drawHist2D(h2D_towers_etaphi,out+"h2D_towers_etaphi.pdf","--logscale --title towers --xlabel  #eta --ylabel #phi");
    drawHist2D(h2D_towers_ietaiphi,out+"h2D_towers_ietaiphi.pdf","--logscale --title towers --xlabel  #eta --ylabel #phi");
    drawHist2D(h2D_towers_ietaiphihad,out+"h2D_towers_ietaiphihad.pdf","--logscale --title towers (had weighted) --xlabel  #eta --ylabel #phi");
    drawHist2D(h2D_twrs_numProblematicHcalCells,out+"h2D_twrs_numProblematicHcalCells.pdf","--logscale --title twrs_numProblematicHcalCellsietaiphi --xlabel #eta --ylabel #phi");
    drawHist2D(h2D_twrs_numProblematicHcalCellsEtaPhi,out+"h2D_twrs_numProblematicHcalCellsEtaPhi.pdf","--logscale --title twrs_numProblematicHcalCellsEtaPhi  --xlabel #eta --ylabel #phi");

    f.Write();

    return 0;
}
