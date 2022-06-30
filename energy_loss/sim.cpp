#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;

#define c 29979245800 //unit: cm/s
#define m_0 105.6583755 //unit: MeV/c^2
#define m_e 0.51099895 //unit: MeV/c^2
#define pi (atan(1)*4)
#define coef 0.1535 //MeVcm^2/g

double rho = 1.29e-3, Z = 7.31719204, A = 28.9647, z = 1.0;
double E_k, Beta, Gamma, v, L = 15.0e5;
double dt = 1.0e-8, x = 0.0;
double I = 85.7;

ofstream output("sim.txt");




void energy_adjust(){
    Gamma = E_k / m_0 + 1; //deriving Gamma from kinetic energy
    Beta = sqrt(1-(1/pow(Gamma, 2))); //deriving Beta from Gamma
    v = Beta * c;
}

double bethe_bloch(double W_max, double eta){
    double dx = v * dt;
    double dE_k = coef * rho * (Z/A) * pow(z/Beta, 2) * (log(2 * m_e * pow(Gamma * v, 2) * W_max / pow(I, 2)) - 2 * pow(Beta, 2)) * dx;
    E_k -= dE_k;
    return dx;
}

int main(){
    cout<<"Kinetic enrgy of muon(GeV): ";
    cin>>E_k;
    E_k *= 1000.0; //GeV to MeV
    while(x<L || E_k < 0.0){
        output<<x<<" "<<E_k<<" "<<v<<"\n";
        energy_adjust();
        double eta = Gamma * Beta;
        double W_max = 2.0 * m_e * pow(c, 2) * eta;
        x += bethe_bloch(W_max, eta);
    }
}