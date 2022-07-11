{
    vector <double> x;
    vector <double> y;
    ifstream input("test.txt");
    double a,b;
    while(input>>a>>b){
        x.push_back(a);
        y.push_back(b);
    }
    TCanvas *c1=new TCanvas();
    /* gPad->SetLogx();
    gPad->SetLogy(); */
    TGraph *gr1 = new TGraph(x.size(), &x[0], &y[0]);
    // gr1->SetTitle("Test;E;dE/dx");
    gr1->Draw("A*");
    input.close();
}