/*
    This program verifies the accuracy of the implementation of bethe bloch formula
    Author: Jui-Teng Hsu (Roy)
    Summer 2022
*/

#include <iostream>
#include <cmath>
#include <fstream>
#include <random>
using namespace std;

#define c 29979245800.0 //unit: cm/s
#define m_0 105.6583755 //unit: MeV/c^2
#define m_e 0.51099895 //unit: MeV/c^2
#define tau 2.1969811e-6 //unit: s
#define pi (atan(1)*4)
#define coef 0.1535 //MeVcm^2/g
#define dt 1.0e-8

ofstream output("adjusted_6GeV.txt");

//energy loss porton

void energy_adjust(double E_temp, double& Gamma, double& Beta, double& v){
    Gamma = E_temp / m_0 + 1; //deriving Gamma from kinetic energy
    Beta = sqrt(1-(1/pow(Gamma, 2))); //deriving Beta from Gamma
    v = Beta * c;
}

double delta_correc(double Beta, double Gamma){
    double C_0 = -10.6, X_0 = 1.742, X_1 = 4.28, m = 3.4, a_bethe = 0.1091;
    double X = log10(Beta * Gamma);
    if(X < X_0) return 0.0;
    else if(X < X_1) return 4.6052 * X + C_0 + a_bethe * pow(X_1-X_0, m);
    else return 4.6052 * X + C_0;
}

double shell_correc(double Beta, double Gamma){
    double I = 85.7e-6;
    double eta = Beta * Gamma;
    return (0.422377 * pow(eta, -2.0) + 0.0304043 * pow(eta, -4.0) - 0.00038106 * pow(eta, -6.0)) * 1e6 * pow(I, 2.0)
            +(3.850190 * pow(eta, -2.0) - 0.1667989 * pow(eta, -4.0) + 0.00157955 * pow(eta, -6.0)) * 1e9 * pow(I, 3.0);
}

double bethe_bloch(double W_max, double Gamma, double Beta, double& E_temp, double rho){
    double I = 85.7e-6;
    double Z = 14.51888746, A = 29.09833728, z = 1.0;
    double eta = Gamma * Beta;
    double v = Beta * c;
    double dx = v * dt;
    double dE_k = -1.0 * coef * rho * (Z/A) * pow(z/Beta, 2) * (log(2 * m_e * pow(Gamma * Beta, 2) * W_max / pow(I, 2)) - 2 * pow(Beta, 2)
                    -delta_correc(Beta, Gamma) - 2 * shell_correc(Beta, Gamma) / Z) * dx;
    E_temp += dE_k;
    output<<dE_k / dx<<" ";
    return dx;
}

double rho_calc(double h){//h in meters
    return 1.225e-3 * pow((288.16-0.0065*h)/288.16, 4.2561); //returns in kg/m^3
}

void calc(double E_init, double altitude){
    double t_total = 0.0;
    double x = altitude;
    double E_temp = E_init; //initial kinetic energy
    double Gamma, Beta, v;
    double probability = 0.0;
    energy_adjust(E_temp, Gamma, Beta, v);
    while(x > 0 && Beta * Gamma > 0.1 && E_temp > 0){
        energy_adjust(E_temp, Gamma, Beta, v);
        double eta = Gamma * Beta;
        double W_max = 2.0 * m_e * pow(eta, 2.0);
        double height = x / 100.0; 
        x -= bethe_bloch(W_max, Gamma, Beta, E_temp, rho_calc(height));
        // x -= bethe_bloch(W_max, Gamma, Beta, E_temp, rho_calc(0.0));
        t_total += (dt / Gamma);
        probability = exp(-1.0 * t_total / tau);
        output<<x<<" "<<altitude - x<<" "<<E_temp<<" "<<t_total<<" "<<probability<<"\n";
    }
}

int main(){
    double E_init, altitude;
    cout<<"Initial KE in GeV: ";
    cin>>E_init;
    cout<<"Starting altitude in KM: ";
    cin>>altitude;
    altitude *= 1.0e5;
    E_init *= 1000.0;
    calc(E_init, altitude);
}