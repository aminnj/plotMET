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

bool hbheNoiseFilter() {
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
    initCounter();

    TH1F* null = new TH1F("","",1,0,1);

    TH1F *h1D_energyRatio_A = new TH1F("h1D_energyRatio_A","",50,0,2.2);
    TH1F *h1D_energyRatio_B = new TH1F("h1D_energyRatio_B","",50,0,2.2);
    TH1F *h1D_energyRatio_C = new TH1F("h1D_energyRatio_C","",50,0,2.2);
    TH1F *h1D_energyRatio_D = new TH1F("h1D_energyRatio_D","",50,0,2.2);
    TH2F* h2D_energyRatio_lengthBad_A = new TH2F("h2D_energyRatio_lengthBad_A","",50,0,2.2, 30,0,30);
    TH2F* h2D_energyRatio_lengthBad_B = new TH2F("h2D_energyRatio_lengthBad_B","",50,0,2.2, 30,0,30);
    TH2F* h2D_energyRatio_lengthBad_C = new TH2F("h2D_energyRatio_lengthBad_C","",50,0,2.2, 30,0,30);
    TH2F* h2D_energyRatio_lengthBad_D = new TH2F("h2D_energyRatio_lengthBad_D","",50,0,2.2, 30,0,30);
    TH2F* h2D_energyRatio_lengthBad_E = new TH2F("h2D_energyRatio_lengthBad_E","",50,0,2.2, 30,0,30);

    TH2F* h2D_badPhi_pfMetPhi_1 = new TH2F("h2D_badPhi_pfMetPhi_1","",50,-3.15,3.15, 50,-3.15,3.15);
    TH2F* h2D_badPhi_pfMetPhi_2 = new TH2F("h2D_badPhi_pfMetPhi_2","",50,-3.15,3.15, 50,-3.15,3.15);
    TH2F* h2D_badPhi_pfMetPhi_3 = new TH2F("h2D_badPhi_pfMetPhi_3","",50,-3.15,3.15, 50,-3.15,3.15);
    TH2F* h2D_badPhi_pfMetPhi_4 = new TH2F("h2D_badPhi_pfMetPhi_4","",50,-3.15,3.15, 50,-3.15,3.15);
    TH2F* h2D_badPhi_pfMetPhi_5 = new TH2F("h2D_badPhi_pfMetPhi_5","",50,-3.15,3.15, 50,-3.15,3.15);
    TH2F* h2D_badPhi_pfMetPhi_6 = new TH2F("h2D_badPhi_pfMetPhi_6","",50,-3.15,3.15, 50,-3.15,3.15);

    TH2F* h2D_pfMet_lengthBad_A = new TH2F("h2D_pfMet_lengthBad_A","",50,0,500, 30,0,30);
    TH2F* h2D_pfMet_lengthBad_B = new TH2F("h2D_pfMet_lengthBad_B","",50,0,500, 30,0,30);
    TH2F* h2D_pfMet_lengthBad_C = new TH2F("h2D_pfMet_lengthBad_C","",50,0,500, 30,0,30);
    TH2F* h2D_pfMet_lengthBad_D = new TH2F("h2D_pfMet_lengthBad_D","",50,0,500, 30,0,30);

    TH2F* h2D_maxEnergy_lengthBad = new TH2F("h2D_maxEnergy_lengthBad","",80,0,800, 30,0,30);

    // eta-phi of towers, pfclusters, and calojets
    TH2F* h2D_towers = new TH2F("h2D_towers"                                       , "" , 90 , -45     , 45     , 75 , 0     , 75);
    TH2F* h2D_twrs_numProblematicHcalCells = new TH2F("h2D_twrs_numProblematicHcalCells"             , "" , 90 , -45     , 45     , 75 , 0     , 75);
    TH2F* h2D_twrs_numProblematicHcalCellsEtaPhi = new TH2F("h2D_twrs_numProblematicHcalCellsEtaPhi"             , "" , 50,-3,3, 50, -3.2, 3.2);

    // max length of bad hcal cells
    // std::vector<std::string> titlesBadCells = {"match", "no match", "either"};
    std::vector<std::string> titlesLengthBadCells = {"all","all, fails jetID", "filts + jetID", "filts + fail jetID"};

    // // no filt requirement ==> A
    TH1F *h1D_lengthBadCells_A_either = new TH1F("h1D_lengthBadCells_A_either","",50,0,50);

    // // no filt requirement, fails jet ID ==> B
    TH1F *h1D_lengthBadCells_B_either = new TH1F("h1D_lengthBadCells_B_either","",50,0,50);

    // // passes all filt (including jet ID) ==> C
    TH1F *h1D_lengthBadCells_C_either = new TH1F("h1D_lengthBadCells_C_either","",50,0,50);

    // // passes filts but fails jet ID ==> D
    TH1F *h1D_lengthBadCells_D_either = new TH1F("h1D_lengthBadCells_D_either","",50,0,50);

    std::vector<TH1F*> h1D_lengthBadCells_vec;
    h1D_lengthBadCells_vec.push_back(h1D_lengthBadCells_A_either);
    h1D_lengthBadCells_vec.push_back(h1D_lengthBadCells_B_either);
    h1D_lengthBadCells_vec.push_back(h1D_lengthBadCells_C_either);
    h1D_lengthBadCells_vec.push_back(h1D_lengthBadCells_D_either);

    const char* json_file = "Run2015BGoldenPlus_v2.txt";
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

            // if(nEventsTotal > 5000) break;

            // Get Event Content
            if( nEventsTotal >= nEventsChain ) continue;
            tree->LoadTree(event);
            cms3.GetEntry(event);
            ++nEventsTotal;
            CMS3::progress( nEventsTotal, nEventsChain );

            // use golden json file 
            if ( evt_isRealData() && !goodrun(evt_run(), evt_lumiBlock()) ) continue;

            // if(evt_event() != 302642409) continue;

            // std::cout << evt_run() << ":" << evt_lumiBlock() << ":" << evt_event() << std::endl;

            float pfMet = pfMet_met();
            float pfMetPhi = pfMet_metPhi();

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
                h2D_towers->Fill(ieta, iphi,twrs_hadEnergy().at(i));
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
            int iEtaLast = 0;
            for(int ieta = 0; ieta < badCellsAlongWorstPhiStrip.size(); ieta++) {
                if(badCellsAlongWorstPhiStrip.at(ieta) > 0) {
                    maxEndingHere++;
                    iEtaLast = ieta;
                } else {
                    if(maxEndingHere > maxLengthBad) maxLengthBad = maxEndingHere;
                    maxEndingHere = 0;
                }
            }

            // start ratio calculation
            vector<int> energyPerPhiStrip(150,0); // there shouldn't be more than 150 iphi vals...
            for(int i = 0; i < twrs_eta().size(); i++) {
                // I want to get a distribution of the ratio of energy in the neighboring iphi strips
                // to the energy of the iphi strip with the max energy

                int ieta = twrs_ieta().at(i);
                int iphi = twrs_iphi().at(i);

                if( abs(ieta) > 20 ) continue; // ignore the double spaced phi strips (see the 2D plots)

                // since we need to convert to original ieta
                float iEtaIndex = ieta;
                if(iEtaIndex > 0) iEtaIndex--;
                iEtaIndex += 50;
                // only consider the part of the strip that we called problematic
                if(iEtaIndex <= iEtaLast && iEtaIndex > iEtaLast - maxLengthBad) {
                    energyPerPhiStrip[iphi] += twrs_hadEnergy().at(i)+twrs_emEnergy().at(i);
                }
            }
            int maxIPhiEnergy = -1;
            float maxEnergy = -1;
            for(int iphi = 1; iphi < energyPerPhiStrip.size(); iphi++) {
                if(energyPerPhiStrip.at(iphi) > maxEnergy) {
                    maxEnergy = energyPerPhiStrip.at(iphi);
                    maxIPhiEnergy = iphi;
                }
            }
            float neighborEnergyRatio = 999;
            // if iphi is 71, then its neighbor is 1 (and vice versa)
            int lowerIPhi = (maxIPhiEnergy == 1) ? 71 : maxIPhiEnergy - 1;
            int upperIPhi = (maxIPhiEnergy == 71) ? 1 : maxIPhiEnergy + 1;
            float energyRatio = (energyPerPhiStrip.at(lowerIPhi) + energyPerPhiStrip.at(upperIPhi) ) / maxEnergy;


            // if( evt_cscTightHaloFilter() ) continue; // now we want to look at events that FAIL cscTightHaloFilter
            // end ratio calculation

            bool passAllFiltersWithoutJetID = evt_trackingFailureFilter() && evt_cscTightHaloFilter() && evt_EcalDeadCellTriggerPrimitiveFilter() && evt_eeBadScFilter() && hbheNoiseFilter() && evt_EcalDeadCellBoundaryEnergyFilter();
            // bool passAllFiltersWithoutJetID = evt_trackingFailureFilter() && evt_EcalDeadCellTriggerPrimitiveFilter() && evt_eeBadScFilter() && hbheNoiseFilter() && evt_EcalDeadCellBoundaryEnergyFilter();
            bool passJetID = true;
            for(int iJet = 0; iJet < pfjets_p4().size(); iJet++) {
                if(pfjets_p4().at(iJet).pt() > 100) {
                    if(!passesLoosePFJetID(iJet)) {
                        passJetID = false; break;
                    }
                }
            }


            // std::cout << evt_run() << ":" << evt_lumiBlock() << ":" << evt_event() << "  " << maxLengthBad << " " << energyRatio << std::endl;

            // no filters applied

            float badPhi = 2.0*3.141592*maxIPhiBad/72;
            if(badPhi > 3.141592) badPhi -= 2.0*3.141592;

            if(maxLengthBad < 5) {
                h2D_badPhi_pfMetPhi_1->Fill(badPhi, pfMetPhi);
            } else if(maxLengthBad >= 5 && maxLengthBad < 10) {
                h2D_badPhi_pfMetPhi_2->Fill(badPhi, pfMetPhi);
            } else if(maxLengthBad >= 10) {
                h2D_badPhi_pfMetPhi_3->Fill(badPhi, pfMetPhi);
            }

            if(maxEnergy < 150) {
                h2D_badPhi_pfMetPhi_6->Fill(badPhi,pfMetPhi);
            } else if(maxEnergy < 500 && maxEnergy > 150) {
                h2D_badPhi_pfMetPhi_5->Fill(badPhi,pfMetPhi);
            } else if(maxEnergy > 500) {
                h2D_badPhi_pfMetPhi_4->Fill(badPhi,pfMetPhi);
            }

            h2D_maxEnergy_lengthBad->Fill(maxEnergy,maxLengthBad);

            h1D_lengthBadCells_A_either->Fill(maxLengthBad);
            h2D_pfMet_lengthBad_A->Fill(pfMet,maxLengthBad);
            h1D_energyRatio_A->Fill(energyRatio);
            h2D_energyRatio_lengthBad_A->Fill(energyRatio, maxLengthBad);

            // no filters applied, fails jetID
            if( !passJetID ) {
                h1D_lengthBadCells_B_either->Fill(maxLengthBad);
                h2D_pfMet_lengthBad_B->Fill(pfMet,maxLengthBad);
                h1D_energyRatio_B->Fill(energyRatio);
                h2D_energyRatio_lengthBad_B->Fill(energyRatio, maxLengthBad);

            }

            if(passAllFiltersWithoutJetID) {

                h2D_energyRatio_lengthBad_E->Fill(energyRatio, maxLengthBad);

                if( passJetID ) {
                    // pass all filters (including jetID)

                    h1D_lengthBadCells_C_either->Fill(maxLengthBad);
                    h2D_pfMet_lengthBad_C->Fill(pfMet,maxLengthBad);
                    h1D_energyRatio_C->Fill(energyRatio);
                    h2D_energyRatio_lengthBad_C->Fill(energyRatio, maxLengthBad);



                } else {
                    // pass all filters but fail jetID

                    h1D_lengthBadCells_D_either->Fill(maxLengthBad);
                    h2D_pfMet_lengthBad_D->Fill(pfMet,maxLengthBad);
                    h1D_energyRatio_D->Fill(energyRatio);
                    h2D_energyRatio_lengthBad_D->Fill(energyRatio, maxLengthBad);

                }
            }
        }

        // Clean Up
        delete tree;
        file->Close();
        delete file;
    }

    printCounter();

    std::cout << " nEventsChain: " << nEventsChain << " nEventsFiltered: " << nEventsFiltered << std::endl;

    std::string out = "pdfs/";
    std::string common = "--noStack --noFill --xAxisOverride [GeV] --noType --preserveBackgroundOrder --legendTextSize 0.03 --legendUp -0.03 --legendRight -0.05 ";

    drawHist2D(h2D_towers,out+"h2D_towers.pdf","--logscale --title towers weighted by HCAL (i#eta i#phi) --xlabel  i#eta --ylabel i#phi");
    drawHist2D(h2D_twrs_numProblematicHcalCells,out+"h2D_twrs_numProblematicHcalCells.pdf","--logscale --title twrs_numProblematicHcalCells(i#eta i#phi) --xlabel i#eta --ylabel i#phi");
    drawHist2D(h2D_twrs_numProblematicHcalCellsEtaPhi,out+"h2D_twrs_numProblematicHcalCellsEtaPhi.pdf","--logscale --title twrs_numProblematicHcalCells(#eta #phi) --xlabel #eta --ylabel #phi");

    dataMCplotMaker(null,h1D_lengthBadCells_vec,titlesLengthBadCells,"length bad HCAL cells (either)","",common+" --xAxisOverride [GeV] --outputName "+out+"h1D_lengthBadCells_vec.pdf");

    singlePlotMaker(h1D_energyRatio_A, "energy ratio", common+" --xAxisOverride [GeV] --isLinear --outputName "+out+"h1D_energyRatio_A.pdf");

    drawHist2D(h2D_maxEnergy_lengthBad,out+"h2D_maxEnergy_lengthBad.pdf","--logscale --title max strip energy vs length bad cells (all) --xlabel max energy --ylabel length bad cells");

    drawHist2D(h2D_pfMet_lengthBad_A,out+"h2D_pfMet_lengthBad_A.pdf","--logscale --title pfMet vs length bad cells (all) --xlabel pfMet --ylabel length bad cells");
    drawHist2D(h2D_pfMet_lengthBad_B,out+"h2D_pfMet_lengthBad_B.pdf","--logscale --title pfMet vs length bad cells (all, fails jetID) --xlabel pfMet --ylabel length bad cells");
    drawHist2D(h2D_pfMet_lengthBad_C,out+"h2D_pfMet_lengthBad_C.pdf","--logscale --title pfMet vs length bad cells (passes filts+jetID) --xlabel pfMet --ylabel length bad cells");
    drawHist2D(h2D_pfMet_lengthBad_D,out+"h2D_pfMet_lengthBad_D.pdf","--logscale --title pfMet vs length bad cells (passes filts, fails jetID) --xlabel pfMet --ylabel length bad cells");

    drawHist2D(h2D_energyRatio_lengthBad_A,out+"h2D_energyRatio_lengthBad_A.pdf","--logscale --title energy ratio vs length prob cells (all) --xlabel energy ratio --ylabel length prob cells");
    drawHist2D(h2D_energyRatio_lengthBad_B,out+"h2D_energyRatio_lengthBad_B.pdf","--logscale --title energy ratio vs length prob cells (all, fails jetID) --xlabel energy ratio --ylabel length prob cells");
    drawHist2D(h2D_energyRatio_lengthBad_C,out+"h2D_energyRatio_lengthBad_C.pdf","--logscale --title energy ratio vs length prob cells (passes filts + jetID) --xlabel energy ratio --ylabel length prob cells");
    drawHist2D(h2D_energyRatio_lengthBad_D,out+"h2D_energyRatio_lengthBad_D.pdf","--logscale --title energy ratio vs length prob cells (passes filts, fails jetID) --xlabel energy ratio --ylabel length prob cells");
    drawHist2D(h2D_energyRatio_lengthBad_E,out+"h2D_energyRatio_lengthBad_E.pdf","--logscale --title energy ratio vs length prob cells (passes filts) --xlabel energy ratio --ylabel length prob cells");

    drawHist2D(h2D_badPhi_pfMetPhi_1,out+"h2D_badPhi_pfMetPhi_1.pdf","--logscale --title problematic strip #phi vs pfMet #phi (length < 5) --xlabel strip phi --ylabel pfMetPhi");
    drawHist2D(h2D_badPhi_pfMetPhi_2,out+"h2D_badPhi_pfMetPhi_2.pdf","--logscale --title problematic strip #phi vs pfMet #phi (5 <= length < 10) --xlabel strip phi --ylabel pfMetPhi");
    drawHist2D(h2D_badPhi_pfMetPhi_3,out+"h2D_badPhi_pfMetPhi_3.pdf","--logscale --title problematic strip #phi vs pfMet #phi (length >= 10) --xlabel strip phi --ylabel pfMetPhi");

    drawHist2D(h2D_badPhi_pfMetPhi_4,out+"h2D_badPhi_pfMetPhi_4.pdf","--logscale --title problematic strip #phi vs pfMet #phi (E > 500) --xlabel strip phi --ylabel pfMetPhi");
    drawHist2D(h2D_badPhi_pfMetPhi_5,out+"h2D_badPhi_pfMetPhi_5.pdf","--logscale --title problematic strip #phi vs pfMet #phi (150 < E < 500) --xlabel strip phi --ylabel pfMetPhi");
    drawHist2D(h2D_badPhi_pfMetPhi_6,out+"h2D_badPhi_pfMetPhi_6.pdf","--logscale --title problematic strip #phi vs pfMet #phi (E < 150) --xlabel strip phi --ylabel pfMetPhi");
    return 0;
}
