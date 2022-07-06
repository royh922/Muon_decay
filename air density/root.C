{
    vector<double> rho;
    vector<double> h;
    ifstream input("output.txt");
    double temp1, temp2;
    while(input>>temp1>>temp2){
        h.push_back(temp1);
        rho.push_back(temp2);
    }
    TCanvas *c1=new TCanvas();
    TGraph *gr1 = new TGraph(h.size(), &h[0], &rho[0]);
    gr1->SetTitle("h vs rho;h (m);rho (kg/m^3)");
    gr1->Draw("AL");
    
    input.close();
}