{
    vector <double> y;
    vector <double> x; 
    ifstream input("update_20.txt");
    double a;
    for(int i = 0; i<90; i++){
        x.push_back((double)(i+1) / 180.0 * TMath::Pi());
        input>>a;
        y.push_back(a);
    }
    input.close();
    auto c1 = new TCanvas();
    TGraph gr1(x.size(), &x[0], &y[0]);

    //fit
    TF1 *fit = new TF1("fit", "[0] * cos(x)", 0, TMath::Pi() / 2);
    auto fitResPtr = gr1.Fit("fit", "S");
    // gr1.Fit("chebyshev1", 0, TMath::Pi() / 2);
    fitResPtr->Print();

    TMatrixDSym covMatrix (fitResPtr->GetCovarianceMatrix());
    covMatrix.Print();

    // fit->Draw("AL");

    gr1.SetTitle("Angle distribution, 8B points, cos(x) fit;Angle from zenith;Count"); gr1.SetMarkerStyle(8); gr1.SetLineWidth(2);
    gr1.Draw("AP");
}