#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;


int main(){
    ofstream output("output.txt");
    double rho_0 = 1.205e-3; // density at 1 atm and 20 Celsius   
    double mass_of_one = (29.72 / 6.022e23)/1000; // in kg
    double g = 9.8; //m/s^2
    double K = 1.38065E-23;// J/K
    double T = 293.15 ;// 20 Celsius in Kelvin

    double h = 0.0;
    int n = 1000000.0;
    for(int i = 0; i<n; i++){
        output<<h<<" "<<1.225* pow((288.16-0.0065*h)/288.16, 4.2561)<<" "<<1e3 * rho_0 * exp(-1*mass_of_one*g*h / (K*T) )<<"\n";
        
        h+=(double)10000.0/n;


    }

    return 0;
}