{
    TH1D h("h", "Probability Histogram", 100, 0.0, 1.0);
    ifstream input("simple_histogram_root.txt");
    double x;
    while(input>>x) h.Fill(x);
    h.Draw();
    input.close();
}