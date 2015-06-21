#include "TH1F.h"
#include "TFile.h"
#include "TCut.h"
#include "TChain.h"
#include "TTree.h"
#include "TString.h"
#include "TLegend.h"
#include <iostream>
#include <vector>
#include "dataMCplotMaker.h"

using namespace std;


void plotBranches(std::vector<TString> branches, TChain *ch, std::string filename) {
    std::vector<TH1F*> hists;
    std::vector<std::string> titles;
    TH1F* null = new TH1F("","",1,0,1);

    TCut cut1 = "evt_sumet>0";
    TCut metCut = "evt_met > 1500";
    TCut cuts = cut1 && metCut;

    std::cout << "Drawing ";
    // do once to get min and max
    float maximum = -9999.9, minimum = 9999.9;
    for(unsigned int i = 0; i < branches.size(); i++) {
        std::cout << branches[i] << ", ";
        ch->Draw(branches[i]+">>h_"+branches[i], cuts);
        // ch->Draw(branches[i]+">>h_"+branches[i]);
        hists.push_back( (TH1F*)gDirectory->Get("h_"+branches[i]) );
        if( hists[i]->GetXaxis()->GetXmax() > maximum ) maximum = hists[i]->GetXaxis()->GetXmax() ;
        if( hists[i]->GetXaxis()->GetXmin() < minimum ) minimum = hists[i]->GetXaxis()->GetXmin() ;
    }
    std::cout << std::endl;

    TString newMax =  TString::Format("%.2f", maximum);
    TString newMin =  TString::Format("%.2f", minimum);
    TString newBins = TString::Format("%i"  , hists.at(0)->GetNbinsX()/2 );

    // draw again with "good" min/max/nbins
    for(unsigned int i = 0; i < branches.size(); i++) {
        ch->Draw(branches[i]+">>h_"+branches[i]+"("  +newBins+","+newMin+","+newMax+  ")", cuts);
        // ch->Draw(branches[i]+">>h_"+branches[i]+"("  +newBins+","+newMin+","+newMax+  ")");
        hists.at(i) = (TH1F*)gDirectory->Get("h_"+branches[i]);
        titles.push_back(branches[i].Data());
    }

    std::string opts = "--noStack --isLinear --legendRight -0.2 --xAxisOverride [GeV]  --type --outputName "+filename+" --overrideHeader "+ titles[0];
    dataMCplotMaker(null, hists, titles, "", "", opts);
}

void compare(TChain *ch) {

    std::vector<TString> branches;

    branches = {"pfCaloMet_met", "evt_met"};
    plotBranches(branches, ch, "plot1.pdf");

    branches = {"pfCaloMet_metPhi", "evt_metPhi"};
    plotBranches(branches, ch, "plot2.pdf");

}
