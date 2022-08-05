{
    vector <double> z;
    vector <double> rate;
    double a, b;
    ifstream input("output.dat");
    while(input>>a>>b){
        z.push_back(a);
        rate.push_back(b);
    }
    const double factor = rate[0];
    for(int i = 0; i<z.size(); i++) rate[i] /= factor;
    TGraph *gr1 = new TGraph(z.size(), &z[0], &rate[0]);

    TF1 *fit = new TF1("fit", "exp(-1.0 * x * [0])", 0, 5);
    auto fitResPtr = gr1->Fit("fit", "SV");
    fitResPtr->Print();

    TMatrixDSym covMatrix (fitResPtr->GetCovarianceMatrix());
    covMatrix.Print();

    gr1->Draw("AP"); gr1->SetMarkerStyle(8); 
    gr1->SetTitle("Particle Creation Rate as a Function of Depth;Atmospheric Depth (m);Normalized Rate")
}