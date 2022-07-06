{
    vector <double> x;
    vector <double> sim_prob;
    vector <double> uncertainty;
    vector <double> cos_sqr;
    ifstream input("output.txt");
    double a,b,c,d;
    while(input>>a>>b>>c>>d){
        x.push_back(a);
        sim_prob.push_back(b);
        uncertainty.push_back(c);
        cos_sqr.push_back(d);
    }
    TMultiGraph *mg = new TMultiGraph();
    // TGraph *gr1 = new TGraphErrors(x.size(), &x[0], &sim_prob[0], NULL, &uncertainty[0]);
    TGraph *gr1 = new TGraph(x.size(), &x[0], &sim_prob[0]);
    TGraph *gr2 = new TGraph(x.size(), &x[0], &cos_sqr[0]);
    auto c3 = new TCanvas("c3","c3");
    
    gr1->SetTitle("Simulated Probability");
    gr2->SetTitle("Cos^2(Theta) fit curve");

    gr2->SetLineColor(kBlue);
    mg->Add(gr1, "A*");
    mg->Add(gr2, "AL");
    mg->SetTitle("0.1KM seperation, 1 per dot; Angle from Z-axis; Survival Percentage"); 
    mg->Draw("A");
    
    c3->BuildLegend();
    
    input.close();
}