{
    vector <double> x;
    vector <double> E_temp;
    vector <double> Beta;
    vector <double> t_total;
    ifstream input("test_data.txt");
    double a,b,c,d;
    while(input>>a>>b>>c>>d){
        x.push_back(a);
        E_temp.push_back(b);
        Beta.push_back(c);
        t_total.push_back(d);
    }
    TMultiGraph *mg = new TMultiGraph();
    // TGraph *gr1 = new TGraphErrors(x.size(), &x[0], &sim_prob[0], NULL, &uncertainty[0]);
    TGraph *gr1 = new TGraph(x.size(), &t_total[0], &x[0]);
    TGraph *gr2 = new TGraph(x.size(), &t_total[0], &E_temp[0]);
    TGraph *gr3 = new TGraph(x.size(), &t_total[0], &Beta[0]);
    auto c3 = new TCanvas("c3","c3");
    
    gr1->SetTitle("Time to position");
    gr2->SetTitle("Time to kinetic energy");
    gr3->SetTitle("Time to beta");

    gr1->SetLineColor(kRed);
    gr2->SetLineColor(kBlue);
    gr3->SetLineColor(kGreen);
    // mg->Add(gr1, "AL");
    // mg->Add(gr2, "AL");
    mg->Add(gr3, "AL");
    mg->SetTitle("Debug data; Time(s); IDK lmao"); 
    mg->Draw("A");
    
    c3->BuildLegend();
    
    input.close();
}