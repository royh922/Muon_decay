{
    vector <double> x;
    vector <double> y;
    ifstream input("test0.txt");
    double a,b;
    while(input>>a>>b){
        x.push_back(a);
        y.push_back(b * -1.0);
    }
    TCanvas *c1=new TCanvas();
    gPad->SetLogx();
    gPad->SetLogy();
    TGraph *gr1 = new TGraph(x.size(), &x[0], &y[0]);
    gr1->SetTitle("Test;E;dE/dx");
    gr1->Draw("AL");
    input.close();
}