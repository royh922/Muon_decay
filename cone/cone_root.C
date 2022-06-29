{
    const int n = 25;
    double x[n];
    double sim_prob[n];
    double uncertainty[n];
    double cos_sqr[n];
    ifstream input("cone.txt");
    for(int i = 0; i<n; i++){
        input>>x[i]>>sim_prob[i]>>uncertainty[i]>>cos_sqr[i];
    }
    TMultiGraph *mg = new TMultiGraph();
    TGraph *gr1 = new TGraphErrors(n, x, sim_prob, NULL, uncertainty);
    TGraph *gr2 = new TGraph(n, x, cos_sqr);
    auto c3 = new TCanvas("c3","c3");
    
    gr1->SetTitle("Simulated Probability");
    gr2->SetTitle("Cos^2(Theta) fit curve");

    gr2->SetLineColor(kBlue);
    mg->Add(gr1, "A*");
    mg->Add(gr2, "AL");
    mg->SetTitle("0.01KM seperation, 10 per dot; Angle from Z-axis; Survival Percentage");
    // mg->GetXaxis()->SetTitle("Theta");
    // mg->GetYaxis()->SetTitle("Survival percentage"); 
    mg->Draw("A");
    
    c3->BuildLegend();
    
    input.close();
}