{
    vector <double> dEdx;
    vector <double> alt;
    vector <double> x;
    vector <double> KE;
    vector <double> t_total;
    vector <double> probability;

    ifstream input1("adjusted_6GeV.txt");
    double a,b,c,d,e,f;
    
    TMultiGraph *mg = new TMultiGraph();

    while(input1>>a>>b>>c>>d>>e>>f){
        dEdx.push_back(a * -1.0);
        alt.push_back(b);
        x.push_back(c);
        KE.push_back(d);
        t_total.push_back(e);
        probability.push_back(f);
    }
    input1.close();
    TGraph *gr1 = new TGraph(x.size(), &alt[0], &KE[0]);

    dEdx.clear();
    alt.clear();
    x.clear();
    KE.clear();
    t_total.clear();
    probability.clear();

    ifstream input2("constant_6GeV.txt");

    while(input2>>a>>b>>c>>d>>e>>f){
        dEdx.push_back(a * -1.0);
        alt.push_back(b);
        x.push_back(c);
        KE.push_back(d);
        t_total.push_back(e);
        probability.push_back(f);
    }
    TGraph *gr2 = new TGraph(x.size(), &alt[0], &KE[0]);
    
    auto c3 = new TCanvas("c3","c3");

    // gPad->SetLogx();
    // gPad->SetLogy();
    
    gr1->SetTitle("Adjusted Density"); gr1->SetLineColor(1); gr1-> SetLineWidth(2);
    gr2->SetTitle("Constant Density"); gr2->SetLineColor(2); gr2-> SetLineWidth(2);
    
    mg->Add(gr1, "AL");
    mg->Add(gr2, "AL");

    mg->SetTitle("KE vs Altitude;Altitude (cm);KE (MeV)"); 
    mg->Draw("A");
    
    c3->BuildLegend();
}