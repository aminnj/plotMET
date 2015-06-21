{
    TFile *file = new TFile("../ntuple.root");
    TTree *tree = (TTree*)file->Get("Events");
    TCanvas *c1 = new TCanvas("c1");
    for(int i = 0; i < tree->GetListOfAliases()->LastIndex(); i++) {
        TString branch = tree->GetListOfAliases()->At(i)->GetName();
        // if(! branch.Contains("metPhi")) continue;
        std::cout << tree->GetListOfAliases()->At(i)->GetName() << std::endl;
        tree->Draw(branch);
        c1->SaveAs("pdfs/"+branch+".pdf");
    }
}
