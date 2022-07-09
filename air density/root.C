{
    vector<double> rho;
    vector<double> rho_fadem;
    vector<double> h;
    ifstream input("output.txt");
    double temp1, temp2, temp3;
    while(input>>temp1>>temp2>>temp3){
        h.push_back(temp1);
        rho.push_back(temp2);
        rho_fadem.push_back(temp3);
    }
    TCanvas *c1=new TCanvas();
    TMultiGraph *mg = new TMultiGraph();
    TGraph *gr1 = new TGraph(h.size(), &h[0], &rho[0]);
    TGraph *gr2 = new TGraph(h.size(), &h[0], &rho_fadem[0]);
    

    mg->Add(gr1, "AL");
    mg->Add(gr2, "AL");
    gr1->SetTitle("Roy");
    gr2->SetTitle("Dr. Fadem");
    gr1->SetLineColor(kBlue);
    gr2->SetLineColor(kRed);

    mg->SetTitle("Density as function of altitude;Altitude (m);Density(kg/m^3)");
    mg->Draw("A");
    
    c1->BuildLegend();
    
    input.close();
}