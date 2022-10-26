{
    auto histogram=new TH1D("count_rate", "Count Rate;Penetration Depth;# Occurrence",
                200, // Number of Bins
                14000, // Lower X Boundary
                15000.0); // Upper X Boundary

    vector<double> x;
    double a;
    ifstream input("p_air.dat");
    while (input>>a){
        histogram->Fill(a);
    }
    input.close();

    /* TF1 *fit = new TF1("fit", "[0] * exp((x - [2]) * [1])", 0, 15000);
    auto fitResPtr = histogram->Fit("fit", "SV");
    fitResPtr->Print(); */

    histogram->Draw();
    
}