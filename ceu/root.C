{
    vector <double> x;
    vector <double> sim_prob;

    ifstream input("./data/energy_loss.dat");
    
    double a,b;
    while(input>>a>>b){
        x.push_back(a);
        sim_prob.push_back(b);
    }

    double factor = sim_prob[0];
    for(int i = 0; i<sim_prob.size(); i++){
        sim_prob[i]/=factor;
    }  
    
    TMultiGraph *mg = new TMultiGraph();
    TGraph *gr1 = new TGraph(x.size(), &x[0], &sim_prob[0]);

    /* TF1 *fit = new TF1("fit", "pow(cos(x / 180.0 * TMath::Pi()), [0])", 0, 70.0);
    auto fitResPtr = gr1->Fit("fit", "SV");
    fitResPtr->Print();

    TMatrixDSym covMatrix (fitResPtr->GetCovarianceMatrix());
    covMatrix.Print(); */

    auto gr1_1 = new TGraph(); gr1_1->SetLineColor(1); gr1_1->SetLineWidth(3);
    gr1_1->SetTitle("cos^{2}(#theta) Parameterization");
    
    const double n = 1.928;
    for(int i = 0; i<x.size(); i++) gr1_1->SetPoint(i, x[i], sim_prob[0] * pow(cos(x[i] / 180.0 * TMath::Pi()), n));
    auto c3 = new TCanvas("c3","c3");
    
    // gr1->SetTitle("Analytical results"); gr1->SetMarkerStyle(8); gr1->SetMarkerColor(2);
    gr1->SetTitle("Simulated results"); gr1->SetLineWidth(6); gr1->SetLineColor(2);
    
    mg->Add(gr1, "AL");
    mg->Add(gr1_1, "AL");

    // gPad->SetLogy();

    // mg->SetTitle("0.1KM separation, 12.5KM, cos^{[0]}(#theta) fit;Angle from Z-axis (#theta); Normalized Hits");
    mg->SetTitle("0.1KM grid width, 12.5KM altitude;Angle from Z-axis (#theta); Normalized Hits"); 
    mg->Draw("A");
    
    c3->BuildLegend();
    
    input.close();
}