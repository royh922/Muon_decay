{
    

    auto histogram=new TH1D("count_rate", "Count Rate;Penetration Depth;# Occurrence",
                80, // Number of Bins
                0.0, // Lower X Boundary
                1.0); // Upper X Boundary

    vector<double> x;
    double a;
    ifstream input("test.dat");
    while (input>>a){
        histogram->Fill(a);
    }
    input.close();

    TF1 *fit = new TF1("fit", "[0] * exp(-1.0 * x * [1])", 0, 1.0);
    auto fitResPtr = histogram->Fit("fit", "SV");
    fitResPtr->Print();

    histogram->Draw();
    
}