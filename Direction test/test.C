{
    vector <double> x;
    vector <double> y;
    vector <double> z;
    auto c1 = new TCanvas();
    double a,b,c;
    ifstream input("test.txt");
    while(input>>a>>b>>c){
        x.push_back(a);
        y.push_back(b);
        z.push_back(c);
    }
    input.close();
    auto dt = new TGraph2D(x.size(), &x[0], &y[0], &z[0]);
    dt->SetTitle("Uniform grid point generation inside a half circle;x;y;z");
    dt->Draw("P");
}