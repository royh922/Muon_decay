{
    vector <double> x;
    vector <double> sim_prob_1;
    vector <double> sim_prob_2;
    vector <double> sim_prob_3;
    vector <double> sim_prob_4;
    vector <double> sim_prob_5;

    ifstream input1("final_10.dat");
    ifstream input2("final.dat");
    ifstream input3("final_15.dat");
    ifstream input4("final_20.dat");
    ifstream input5("final_30.dat");


    double a,b,c;
    while(input1>>a>>b>>c){
        x.push_back(a);
        sim_prob_1.push_back(b);
    }
    while(input2>>a>>b>>c) sim_prob_2.push_back(b);
    while(input3>>a>>b>>c) sim_prob_3.push_back(b);
    while(input4>>a>>b>>c) sim_prob_4.push_back(b);
    while(input5>>a>>b>>c) sim_prob_5.push_back(b);


    double factor = sim_prob_1[0];
    for(int i = 0; i<sim_prob_1.size(); i++) sim_prob_1[i]/=factor;

    factor = sim_prob_2[0];
    for(int i = 0; i<sim_prob_2.size(); i++) sim_prob_2[i]/=factor;
    factor = sim_prob_3[0];
    for(int i = 0; i<sim_prob_3.size(); i++) sim_prob_3[i]/=factor;
    factor = sim_prob_4[0];
    for(int i = 0; i<sim_prob_4.size(); i++) sim_prob_4[i]/=factor;
    factor = sim_prob_5[0];
    for(int i = 0; i<sim_prob_5.size(); i++) sim_prob_5[i]/=factor;
    
    TMultiGraph *mg = new TMultiGraph();

    TGraph *gr1 = new TGraph(x.size(), &x[0], &sim_prob_1[0]);
    TGraph *gr2 = new TGraph(x.size(), &x[0], &sim_prob_2[0]);
    TGraph *gr3 = new TGraph(x.size(), &x[0], &sim_prob_3[0]);
    TGraph *gr4 = new TGraph(x.size(), &x[0], &sim_prob_4[0]);
    TGraph *gr5 = new TGraph(x.size(), &x[0], &sim_prob_5[0]);

    TF1 *fit = new TF1("fit", "pow(cos(x / 180.0 * TMath::Pi()), [0])", 0, 70.0);
    // auto fit_1 = gr1->Fit("fit", "SV");
    // auto fit_2 = gr2->Fit("fit", "SV");
    // auto fit_3 = gr3->Fit("fit", "SV");
    // auto fit_4 = gr4->Fit("fit", "SV");

    auto gr1_1 = new TGraph(); gr1_1->SetLineColor(1); gr1_1->SetLineWidth(4);
    gr1_1->SetTitle("cos^{2}(#theta) fit");
    
    for(int i = 0; i<x.size(); i++) gr1_1->SetPoint(i, x[i], 1 * pow(cos(x[i] / 180.0 * TMath::Pi()), 2.0));
    auto c3 = new TCanvas("c3","c3");
    
    gr1->SetTitle("10 KM");     gr1->SetLineWidth(2); gr1->SetLineColor(2); gr1->SetMarkerStyle(8); gr1->SetMarkerColor(2);
    gr2->SetTitle("12.5 KM");   gr2->SetLineWidth(2); gr2->SetLineColor(3); gr2->SetMarkerStyle(8); gr2->SetMarkerColor(3);
    gr3->SetTitle("15 KM");     gr3->SetLineWidth(2); gr3->SetLineColor(4); gr3->SetMarkerStyle(8); gr3->SetMarkerColor(4);
    gr4->SetTitle("20 KM");     gr4->SetLineWidth(2); gr4->SetLineColor(6); gr4->SetMarkerStyle(8); gr4->SetMarkerColor(6);
    gr4->SetTitle("30 KM");     gr5->SetLineWidth(2); gr5->SetLineColor(7); gr5->SetMarkerStyle(8); gr5->SetMarkerColor(7);

    
    mg->Add(gr1, "APL");
    mg->Add(gr2, "APL");
    mg->Add(gr3, "APL");
    mg->Add(gr4, "APL");
    mg->Add(gr5, "APL");
    mg->Add(gr1_1, "AL");

    // gPad->SetLogy();

    mg->SetTitle("Simulated rates from different altitudes;Angle from Z-axis (#theta);Normalized Hits"); 
    mg->Draw("A");
    
    c3->BuildLegend();
    
    // input.close();
}