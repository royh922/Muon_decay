{
    vector <double> x;
    vector <double> sim_prob0;
    vector <double> sim_prob1;
    vector <double> sim_prob2;
    vector <double> sim_prob3;
    vector <double> sim_prob4;
    vector <double> cos_sqr;
    ifstream input("output_batch_2.txt");
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
    
    const double n = 2.0;
    for(int i = 0; i<20; i++){
        gr1_1->SetPoint(i, x[i], sim_prob0[0] * pow(cos(x[i] / 180.0 * TMath::Pi()), n));
        gr2_1->SetPoint(i, x[i], sim_prob1[0] * pow(cos(x[i] / 180.0 * TMath::Pi()), n));
        gr3_1->SetPoint(i, x[i], sim_prob2[0] * pow(cos(x[i] / 180.0 * TMath::Pi()), n));
        gr4_1->SetPoint(i, x[i], sim_prob3[0] * pow(cos(x[i] / 180.0 * TMath::Pi()), n));
        gr5_1->SetPoint(i, x[i], sim_prob4[0] * pow(cos(x[i] / 180.0 * TMath::Pi()), n));
    }
    auto c3 = new TCanvas("c3","c3");
    
    gr1->SetTitle("Initial_KE = 4 GeV"); gr1->SetMarkerStyle(8); gr1->SetMarkerColor(1); 
    gr2->SetTitle("Initial_KE = 6 GeV"); gr2->SetMarkerStyle(8); gr2->SetMarkerColor(2);
    gr3->SetTitle("Initial_KE = 8 GeV"); gr3->SetMarkerStyle(8); gr3->SetMarkerColor(3);
    gr4->SetTitle("Initial_KE = 10 GeV"); gr4->SetMarkerStyle(8); gr4->SetMarkerColor(4);
    gr5->SetTitle("Initial_KE = 12 GeV"); gr5->SetMarkerStyle(8); gr5->SetMarkerColor(6);
    
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

    mg->SetTitle("0.2KM separation, 15KM altitude; Angle from Z-axis; Hit Percentage"); 
    mg->Draw("A");
    
    c3->BuildLegend();
    
    input.close();
}