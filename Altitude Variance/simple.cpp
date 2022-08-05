#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;

int main(){
    ofstream output("output.txt");
    double A = 100.0; //initial beam flux
    double sigma = 96.07; //reaction cross sectioni in mb (10^-28 m^2)
    double n = 0.001; //in 10^27 m^3
    double dz = 0.0005; //step distance in m
    double L = 1e4; //total depth in m
    double z = 0; //penetration depth in m

    while(z < L && A > 0.0001){
        double change = n * sigma * A * dz;
        output<<z<<" "<<A<<"\n";
        z += dz;
        A -= change;
    }
    
    return 0;
}