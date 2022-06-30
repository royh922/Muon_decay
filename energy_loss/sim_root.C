{
    vector<double> dE_kx;
    vector<double> x;
    vector<double> E_k;
    vector<double> v;
    ifstream input("sim.txt");
    double temp1, temp2, temp3, temp4;
    while(input>>temp1>>temp2>>temp3>>temp4){
        dE_kx.push_back(temp1);
        x.push_back(temp2);
        E_k.push_back(temp3);
        v.push_back(temp4);
    }
    TGraph *gr1 = new TGraph(x.size(), &E_k[0], &dE_kx[0]);
    gr1->SetTitle("Energy Loss; E_k; dE_k/dx");
    gPad->SetLogx();
    gr1->Draw("AL");

    
    input.close();
}