{
    vector <double> y;
    vector <double> x; 
    ifstream input("output_20.txt");
    double a;
    for(int i = 0; i<91; i++){
        x.push_back(i);
        input>>a;
        y.push_back(a);
    }
    // TMultiGraph *mg = new TMultiGraph();
    TGraph *gr1 = new TGraph(x.size(), &x[0], &y[0]);
    gr1->SetTitle("Angle distribution, 8B points;Angle from zenith;Relative count"); gr1->SetMarkerStyle(8); gr1->SetLineWidth(2);
    gr1->Draw("AL");
    // TGraph *gr2 = new TGraph(x.size(), &x[0], &KE[0]);
    /* auto h1 = new TH1D("h1", "Angle Distribution", x.size(), 0.0, 90.0);
    for(int i = 0; i<x.size(); i++) h1->Fill(x[i]);
    h1->Draw(); */
}