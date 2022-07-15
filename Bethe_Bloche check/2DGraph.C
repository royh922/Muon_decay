{
    vector <double> KE;
    vector <double> rho;
    vector <double> dEdx;
    vector <double> Gamma;
    vector <double> Beta;
    vector <double> eta;

    ifstream input("2D.txt");
    double a,b,c,d,e,f;

    while(input>>a>>b>>c>>d>>e>>f){
        KE.push_back(a);
        rho.push_back(b);
        dEdx.push_back(c);
        Gamma.push_back(d);
        Beta.push_back(e);
        eta.push_back(f);
    }
    input.close();
    TCanvas *c1 = new TCanvas;
    TGraph2D *gr1 = new TGraph2D(KE.size(), &KE[0], &rho[0], &dEdx[0]);
    gPad->SetLogz();
    gr1->SetTitle("dEdx as a function of KE and air density;KE (MeV);Air Density (kg/m^3);dE/dx (MeV/cm)");
    gr1->Draw("TRI1");
}