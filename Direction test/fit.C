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
    auto c1 = new TCanvas();
    TGraph gr1(x.size(), &x[0], &y[0]);

    TF1 trig("chebyshev0","[0]*TMath::Sin((x * 2) / 180.0 * TMath::Pi())",0,90);
    auto fitResPtr = gr1.Fit(&trig, "S");
    fitResPtr->Print();

    TMatrixDSym covMatrix (fitResPtr->GetCovarianceMatrix());
    covMatrix.Print();

    trig.Draw();

    gr1.SetTitle("Angle distribution, 8B points;Angle from zenith;Relative count"); gr1.SetMarkerStyle(8); gr1.SetLineWidth(2);
    gr1.Draw("APE");


    
}