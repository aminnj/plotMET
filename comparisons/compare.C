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


void plotBranches(std::vector<TString> branches, TChain *ch, TCut cuts, std::string filename) {
    std::vector<TH1F*> hists;
    std::vector<std::string> titles;
    TH1F* null = new TH1F("","",1,0,1);

    // do once to get min and max
    float maximum = -9999.9, minimum = 9999.9;
    for(unsigned int i = 0; i < branches.size(); i++) {
        std::cout << "drawing " << branches[i] << std::endl;
        ch->Draw(branches[i]+">>h_"+branches[i], cuts);
        hists.push_back( (TH1F*)gDirectory->Get("h_"+branches[i]) );
        if( hists[i]->GetXaxis()->GetXmax() > maximum ) maximum = hists[i]->GetXaxis()->GetXmax() ;
        if( hists[i]->GetXaxis()->GetXmin() < minimum ) minimum = hists[i]->GetXaxis()->GetXmin() ;
    }

    TString newMax =  TString::Format("%.2f", maximum);
    TString newMin =  TString::Format("%.2f", minimum);
    TString newBins = TString::Format("%i"  , hists.at(0)->GetNbinsX()/2 );

    // draw again with "good" min/max/nbins
    for(unsigned int i = 0; i < branches.size(); i++) {
        ch->Draw(branches[i]+">>h_"+branches[i]+"("  +newBins+","+newMin+","+newMax+  ")", cuts);
        hists.at(i) = (TH1F*)gDirectory->Get("h_"+branches[i]);
        titles.push_back(branches[i].Data());
    }

    TString opts = Form( "--noStack --isLinear --legendRight -0.2 --xAxisOverride [GeV]  --type  --outputName %s --overrideHeader %s (%s)", 
                        filename.c_str(), titles[0].c_str() , ((TString)cuts).Data() );
    dataMCplotMaker(null, hists, titles, "", "", opts.Data());
}

void compare(TChain *ch) {

    std::vector<TString> branches;
    TCut cuts = "evt_met > 3000";

    branches = {"pfCaloMet_met", "evt_met"};
    plotBranches(branches, ch, cuts, "plot1.pdf");

    branches = {"pfCaloMet_metPhi", "evt_metPhi"};
    plotBranches(branches, ch, cuts, "plot2.pdf");

}
