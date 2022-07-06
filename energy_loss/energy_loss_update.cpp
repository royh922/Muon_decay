#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;

#define c 29979245800 //unit: cm/s
#define m_0 105.6583755 //unit: MeV/c^2
#define m_e 0.51099895 //unit: MeV/c^2
#define pi (atan(1)*4)
#define coef 0.1535 //MeVcm^2/g

double rho = 1.29e-3, Z = 14.51888746, A = 29.09833728, z = 1.0;
double E_k, Beta, Gamma, v, L = 10.0e5;
double dt = 1.0e-8, x = 0.0;
double I = 85.7e-6;
double t_total = 0.0;

double C_0 = -10.6, X_0 = 1.742, X_1 = 4.28, m = 3.4, a = 0.1091;

ofstream output("time_dialated.txt");

void energy_adjust(){
    Gamma = E_k / m_0 + 1; //deriving Gamma from kinetic energy
    Beta = sqrt(1-(1/pow(Gamma, 2))); //deriving Beta from Gamma
    v = Beta * c;
}

double delta_correc(double Beta, double Gamma){
    double X = log10(Beta * Gamma);
    if(X < X_0) return 0.0;
    else if(X < X_1) return 4.6052 * X + C_0 + a * pow(X_1-X_0, m);
    else return 4.6052 * X + C_0;
}

double shell_correc(double Beta, double Gamma){
    double eta = Beta * Gamma;
    return (0.422377 * pow(eta, -2.0) + 0.0304043 * pow(eta, -4.0) - 0.00038106 * pow(eta, -6.0)) * 1e6 * pow(I, 2.0)
            +(3.850190 * pow(eta, -2.0) - 0.1667989 * pow(eta, -4.0) + 0.00157955 * pow(eta, -6.0)) * 1e9 * pow(I, 3.0);
}

double bethe_bloch(double W_max, double eta){
    double dx = v * dt;
    double dE_k = -1.0 * coef * rho * (Z/A) * pow(z/Beta, 2) * (log(2 * m_e * pow(Gamma * Beta, 2) * W_max / pow(I, 2)) - 2 * pow(Beta, 2)
                    -delta_correc(Beta, Gamma) - 2 * shell_correc(Beta, Gamma) / Z) * dx;
    E_k += dE_k;
    output<<dE_k / dx<<" ";
    return dx;
}


int main(){
    cout<<"Kinetic enrgy of muon(GeV): ";
    cin>>E_k;
    E_k *= 1000.0; //GeV to MeV
    energy_adjust();
    double eta = Gamma * Beta;
    double W_max = 2.0 * m_e * eta;
    x += bethe_bloch(W_max, eta);
    t_total += dt * Gamma;
    output<<x<<" "<<E_k<<" "<<t_total<<"\n";
    /* while(x<L){
        energy_adjust();
        double eta = Gamma * Beta;
        double W_max = 2.0 * m_e * pow(c, 2) * eta;
        x += bethe_bloch(W_max, eta);
        t_total += dt * Gamma;
        output<<x<<" "<<E_k<<" "<<t_total<<"\n";
    } */
}