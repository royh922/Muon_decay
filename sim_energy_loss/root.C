{
    vector <double> x;
    vector <double> sim_prob;
    vector <double> sim_prob_un;
    vector <double> uncertainty;
    vector <double> cos_sqr;
    ifstream input("output.txt");
    double a,b,c,d,e;
    while(input>>a>>b>>c>>d>>e){
        x.push_back(a);
        sim_prob.push_back(b);
        sim_prob_un.push_back(c);
        uncertainty.push_back(d);
        cos_sqr.push_back(e);
    }
    TMultiGraph *mg = new TMultiGraph();
    // TGraph *gr1 = new TGraphErrors(x.size(), &x[0], &sim_prob[0], NULL, &uncertainty[0]);
    TGraph *gr1 = new TGraph(x.size(), &x[0], &sim_prob[0]);
    TGraph *gr2 = new TGraph(x.size(), &x[0], &cos_sqr[0]);
    TGraph *gr3 = new TGraph(x.size(), &x[0], &sim_prob_un[0]);
    auto c3 = new TCanvas("c3","c3");
    
    gr1->SetTitle("Simulated Probability");
    gr2->SetTitle("Cos^2(Theta) fit curve");
    gr3->SetTitle("Simulated Probability without energy loss");

    gr2->SetLineColor(kBlue);
    gr1->SetMarkerStyle(3);
    gr3->SetMarkerStyle(5);
    mg->Add(gr1, "AP");
    mg->Add(gr2, "AL");
    mg->Add(gr3, "AP");
    mg->SetTitle("0.01KM seperation, 30 per dot; Angle from Z-axis; Survival Percentage"); 
    mg->Draw("A");
    
    c3->BuildLegend();
    
    input.close();
}