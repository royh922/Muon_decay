{
    vector <double> dEdx;
    vector <double> KE;
    vector <double> x;
    vector <double> eta;
    vector <double> t_total;
    vector <double> probability;
    ifstream input("sealevel.txt");
    double a,b,c,d,e,f;
    while(input>>a>>b>>c>>d>>e>>f){
        dEdx.push_back(a * -1.0);
        KE.push_back(b);
        x.push_back(c);
        eta.push_back(d);
        t_total.push_back(e);
        probability.push_back(f);
    }
    TMultiGraph *mg = new TMultiGraph();
    // TGraph *gr1 = new TGraphErrors(x.size(), &x[0], &sim_prob[0], NULL, &uncertainty[0]);
    TGraph *gr1 = new TGraph(x.size(), &x[0], &dEdx[0]);
    gr1->SetTitle("dE/dx vs depth, log scale (const. density);depth (cm);dE/dx (MeV / cm)");
    gr1->SetLineWidth(3);

    TCanvas *c1=new TCanvas();
    gPad->SetLogx();
    gPad->SetLogy();
    gr1->Draw("AL");
    /* TGraph *gr2 = new TGraph(x.size(), &x[0], &sim_prob1[0]);
    TGraph *gr3 = new TGraph(x.size(), &x[0], &sim_prob2[0]);
    TGraph *gr4 = new TGraph(x.size(), &x[0], &sim_prob3[0]);
    TGraph *gr5 = new TGraph(x.size(), &x[0], &sim_prob4[0]); */
    
    // auto c3 = new TCanvas("c3","c3");
    
    /* gr1->SetTitle("Initial_KE = 3 GeV"); gr1->SetMarkerStyle(8); gr1->SetMarkerColor(1); 
    gr2->SetTitle("Initial_KE = 5 GeV"); gr2->SetMarkerStyle(8); gr2->SetMarkerColor(2);
    gr3->SetTitle("Initial_KE = 7 GeV"); gr3->SetMarkerStyle(8); gr3->SetMarkerColor(3);
    gr4->SetTitle("Initial_KE = 9 GeV"); gr4->SetMarkerStyle(8); gr4->SetMarkerColor(4);
    gr5->SetTitle("Initial_KE = 11 GeV"); gr5->SetMarkerStyle(8); gr5->SetMarkerColor(6);

    
    mg->Add(gr1, "AP");
    mg->Add(gr2, "AP");
    mg->Add(gr3, "AP");
    mg->Add(gr4, "AP");
    mg->Add(gr5, "AP");

    mg->Add(gr1_1, "AL");
    mg->Add(gr2_1, "AL");
    mg->Add(gr3_1, "AL");
    mg->Add(gr4_1, "AL");
    mg->Add(gr5_1, "AL");

    mg->SetTitle("0.25KM separation, 15KM altitude; Angle from Z-axis; Hit Percentage"); 
    mg->Draw("A");
    
    c3->BuildLegend(); */
    
    input.close();
}