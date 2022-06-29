{
    const int n = 25;
    double x[n];
    double probability[n];
    double sim_prob[n];
    double uncertainty[n];
    double cos_sqr[n];
    ifstream input("muon2D_root.txt");
    for(int i = 0; i<n; i++){
        input>>x[i]>>probability[i]>>sim_prob[i]>>uncertainty[i]>>cos_sqr[i];
    }
    TMultiGraph *mg = new TMultiGraph();
    TGraph *gr1 = new TGraph(n, x, probability);
    TGraph *gr2 = new TGraphErrors(n, x, sim_prob, NULL, uncertainty);
    TGraph *gr3 = new TGraph(n, x, cos_sqr);
    auto c3 = new TCanvas("c3","c3");
    

    gr1->SetTitle("Theoretical Probability");
    gr2->SetTitle("Simulated Probability");
    gr3->SetTitle("Cos^2(Theta) fit curve");

    gr1->SetLineColor(kRed);
    gr3->SetLineColor(kBlue);
    mg->Add(gr1, "AL");
    mg->Add(gr2, "A*");
    mg->Add(gr3, "AL");
    mg->SetTitle("Simple 2D Simulation; Angle from Z-axis (theta); Survival Percentage");
    // mg->GetXaxis()->SetTitle("Theta");
    // mg->GetYaxis()->SetTitle("Survival percentage"); 
    mg->Draw("A");
    
    auto legend = new TLegend(0.3, 0.1);
    legend->AddEntry("", "Number of muons per batch: 99", "C");
    legend->Draw();
    
    c3->BuildLegend();
    
    
    input.close();
}