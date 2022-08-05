{
    vector<double> x;
    vector<double> y;
    vector<double> z;
    double a, b, c;
    ifstream input("test.dat");
    while(input>>a>>b>>c){
        z.push_back(a);
        x.push_back(b);
        y.push_back(c);
    }

    TGraph2D* gr1 = new TGraph2D(x.size(), &x[0], &y[0], &z[0]);
    gr1->SetMarkerColor(2);
    gr1->Draw("AP");
}