{
    vector<double> dE_kx;
    vector<double> x;
    vector<double> E_k;
    vector<double> v;
    ifstream input("sim.txt");
    ifstream input_2("sim_2.txt");
    double temp1, temp2, temp3, temp4;
    while(input>>temp1>>temp2>>temp3>>temp4){
        dE_kx.push_back(temp1 * -0.1);
        x.push_back(temp2);
        E_k.push_back(temp3);
        v.push_back(temp4);
    }
    TCanvas *c1=new TCanvas();
    TGraph *gr1 = new TGraph(x.size() - 2, &E_k[0], &dE_kx[0]);
    gPad->SetLogx();
    gPad->SetLogy();
    
    /* gr1->SetTitle("Energy Loss as function of penetration;x;dE_k/dx");
    gr1->Draw("AL"); */

    dE_kx.clear();
    x.clear();
    E_k.clear();
    v.clear();
    while(input_2>>temp1>>temp2>>temp3>>temp4){
        dE_kx.push_back(temp1 * -0.1);
        x.push_back(temp2);
        E_k.push_back(temp3);
        v.push_back(temp4);
    }
    TGraph *gr2 = new TGraph(x.size() - 2, &E_k[0], &dE_kx[0]);
    TMultiGraph *mg = new TMultiGraph(); 

    gr1->SetTitle("With Correction Terms");
    gr2->SetTitle("Without Correction Terms");
    gr1->SetLineColor(kBlue);
    gr2->SetLineColor(kRed);
    gr2->SetLineStyle(9);
    mg->Add(gr1);
    mg->Add(gr2);
    mg->SetTitle("Muon Energy Loss in Air;E_k;-dE_k/dx");
    
    mg->Draw("AL");
    c1->BuildLegend();
    
    input.close();
}