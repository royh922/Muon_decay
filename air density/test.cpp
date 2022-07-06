#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;


int main(){
    ofstream output("output.txt");
    double h = 0.0;
    int n = 1000000.0;
    for(int i = 0; i<n; i++){
        output<<h<<" "<<1.225* pow((288.16-0.0065*h)/288.16, 4.2561)<<"\n";
        h+=(double)10000.0/n;
    }

    return 0;
}