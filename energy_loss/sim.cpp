#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;

#define c 299792.458 //unit: m/s
#define tau 2.1969811e-6 //unit: s
#define m_0 105.6583755 //unit: MeV/c^2
#define pi (atan(1)*4)
#define coef 0.1535 //MeVcm^2/g

double rho = 1.29e-3, Z = 7.31719204, A = 28.9647, z = 1.0;
double E_k, Beta, Gamma, v, L = 15.0;

ofstream output("sim.txt");



int main(){
    cout<<"Kinetic enrgy of muon(GeV): ";
    cin>>E_k;
    Gamma = E_k * 1e3 / m_0 + 1; //deriving Gamma from kinetic energy
    Beta = sqrt(1-(1/pow(Gamma, 2))); //deriving Beta from Gamma
}