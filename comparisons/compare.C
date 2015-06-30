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


void plotBranches(std::vector<TString> branches, TChain *ch, std::vector<TCut> cuts, std::string filename) {
    std::vector<TH1F*> hists;
    std::vector<std::string> titles;
    TH1F* null = new TH1F("","",1,0,1);

    //if len(cuts) > len(branches), then we probably have 1 branch with multiple cuts
    while( branches.size() < cuts.size() ) {
        branches.push_back(branches[0]);
    }


    // do once to get min and max
    float maximum = -9999.9, minimum = 9999.9;
    for(unsigned int i = 0; i < branches.size(); i++) {
        TString is = TString::Itoa(i,10);
        std::cout << "drawing " << branches.at(i) << std::endl;
        ch->Draw("0+"+branches.at(i)+">>h_"+branches.at(i)+is, cuts.at(i));
        hists.push_back( (TH1F*)gDirectory->Get("h_"+branches.at(i)+is) );
        if( hists.at(i)->GetXaxis()->GetXmax() > maximum ) maximum = hists.at(i)->GetXaxis()->GetXmax() ;
        if( hists.at(i)->GetXaxis()->GetXmin() < minimum ) minimum = hists.at(i)->GetXaxis()->GetXmin() ;
    }

    TString newMax =  TString::Format("%.2f", maximum);
    TString newMin =  TString::Format("%.2f", minimum);
    TString newBins = TString::Format("%i"  , hists.at(0)->GetNbinsX() );

    // draw again with "good" min/max/nbins
    for(unsigned int i = 0; i < branches.size(); i++) {
        TString is = TString::Itoa(i,10);
        ch->Draw("0+"+branches.at(i)+">>h_"+branches.at(i)+is+"("  +newBins+","+newMin+","+newMax+  ")", cuts.at(i));
        hists.at(i) = (TH1F*)gDirectory->Get("h_"+branches.at(i)+is);
        TString title = Form("%s (%s)", branches.at(i).Data(), ((TString)cuts.at(i)).Data());
        titles.push_back(title.Data());
    }

    // TString opts = Form( "--noStack --isLinear --legendRight -0.40 --legendTextSize 0.03 --xAxisOverride [GeV]  --type  --outputName %s --overrideHeader %s", 
    TString opts = Form( "--noStack --legendRight -0.40 --legendTextSize 0.025 --xAxisOverride [GeV]  --type  --outputName %s --overrideHeader %s", 
            filename.c_str(), titles[0].c_str() );
    dataMCplotMaker(null, hists, titles, "", "", opts.Data());
}

void compare(TChain *ch) {

    std::vector<TString> branches;
    std::vector<TCut> cuts;
    TCut cut = "evt_met > 2000";

    branches = {"pfCaloMet_met", "evt_met"};
    cuts = { cut, cut };
    plotBranches(branches, ch, cuts, "plot1.pdf");

    branches = {"pfCaloMet_metPhi", "evt_metPhi"};
    cuts = { cut, cut };
    plotBranches(branches, ch, cuts, "plot2.pdf");


    branches = {"evt_met"};
    cuts = {
        "evt_met>500",
        "evt_met>500 && evt_cscTightHaloFilter",
        "evt_met>500 && hcalnoise_passHighLevelNoiseFilter",
        "evt_met>500 && hcalnoise_passLooseNoiseFilter",
        "evt_met>500 && hcalnoise_passTightNoiseFilter"
    };
    plotBranches(branches, ch, cuts, "caloMetNoise.pdf");

    branches = {"evt_met"};
    cuts = {
        "evt_met>500",
        "evt_met>500 && evt_hbheFilter",
        "evt_met>500 && evt_hbheFilterRun1",
        "evt_met>500 && evt_hbheFilterRun2Loose",
        "evt_met>500 && evt_hbheFilterRun2Tight"
    };
    plotBranches(branches, ch, cuts, "caloMetHBHE.pdf");

    branches = {"pfCaloMet_met"};
    cuts = {
        "evt_met>500",
        "evt_met>500 && evt_cscTightHaloFilter",
        "evt_met>500 && hcalnoise_passHighLevelNoiseFilter",
        "evt_met>500 && hcalnoise_passLooseNoiseFilter",
        "evt_met>500 && hcalnoise_passTightNoiseFilter"
    };
    plotBranches(branches, ch, cuts, "pfCaloMetNoise.pdf");

    branches = {"pfCaloMet_met"};
    cuts = {
        "evt_met>500",
        "evt_met>500 && evt_hbheFilter",
        "evt_met>500 && evt_hbheFilterRun1",
        "evt_met>500 && evt_hbheFilterRun2Loose",
        "evt_met>500 && evt_hbheFilterRun2Tight"
    };
    plotBranches(branches, ch, cuts, "pfCaloMetHBHE.pdf");
}
