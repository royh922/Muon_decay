{
    vector <double> x;
    vector <double> sim_prob0;
    vector <double> sim_prob1;
    vector <double> sim_prob2;
    vector <double> sim_prob3;
    vector <double> sim_prob4;
    vector <double> cos_sqr;
    ifstream input("dump.txt");
    double temp[11];
    for(int i = 0; i<20; i++){
        for(int j = 0; j<11; j++){
            input>>temp[j];
        }
        x.push_back(temp[0]);
        sim_prob0.push_back(temp[1]);
        sim_prob1.push_back(temp[3]);
        sim_prob2.push_back(temp[5]);
        sim_prob3.push_back(temp[7]);
        sim_prob4.push_back(temp[9]);
    }
    TMultiGraph *mg = new TMultiGraph();
    // TGraph *gr1 = new TGraphErrors(x.size(), &x[0], &sim_prob[0], NULL, &uncertainty[0]);
    TGraph *gr1 = new TGraph(x.size(), &x[0], &sim_prob0[0]);
    TGraph *gr2 = new TGraph(x.size(), &x[0], &sim_prob1[0]);
    TGraph *gr3 = new TGraph(x.size(), &x[0], &sim_prob2[0]);
    TGraph *gr4 = new TGraph(x.size(), &x[0], &sim_prob3[0]);
    TGraph *gr5 = new TGraph(x.size(), &x[0], &sim_prob4[0]);

    auto gr1_1 = new TGraph(); gr1_1->SetLineColor(1);
    auto gr2_1 = new TGraph(); gr2_1->SetLineColor(2);
    auto gr3_1 = new TGraph(); gr3_1->SetLineColor(3);
    auto gr4_1 = new TGraph(); gr4_1->SetLineColor(4);
    auto gr5_1 = new TGraph(); gr5_1->SetLineColor(6);
    
    for(int i = 0; i<20; i++){
        gr1_1->SetPoint(i, x[i], sim_prob0[0] * TMath::Cos(3.0));
        /* gr2_1->SetPoint(i, x[i], simprob1[0] * TMath::Power(TMath::Cos(x[i] / 180.0 * 3.14), 2.0));
        gr3_1->SetPoint(i, x[i], simprob2[0] * TMath::Power(TMath::Cos(x[i] / 180.0 * 3.14), 2.0));
        gr4_1->SetPoint(i, x[i], simprob3[0] * TMath::Power(TMath::Cos(x[i] / 180.0 * 3.14), 2.0));
        gr5_1->SetPoint(i, x[i], simprob4[0] * TMath::Power(TMath::Cos(x[i] / 180.0 * 3.14), 2.0)); */
    }
    auto c3 = new TCanvas("c3","c3");
    
    gr1->SetTitle("Initial_KE = 3 GeV"); gr1->SetMarkerStyle(8); gr1->SetMarkerColor(1); 
    gr2->SetTitle("Initial_KE = 4 GeV"); gr2->SetMarkerStyle(8); gr2->SetMarkerColor(2);
    gr3->SetTitle("Initial_KE = 5 GeV"); gr3->SetMarkerStyle(8); gr3->SetMarkerColor(3);
    gr4->SetTitle("Initial_KE = 6 GeV"); gr4->SetMarkerStyle(8); gr4->SetMarkerColor(4);
    gr5->SetTitle("Initial_KE = 7 GeV"); gr5->SetMarkerStyle(8); gr5->SetMarkerColor(6);

    
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

    mg->SetTitle("0.1KM seperation; Angle from Z-axis; Hit Percentage"); 
    mg->Draw("A");
    
    c3->BuildLegend();
    
    input.close();
}