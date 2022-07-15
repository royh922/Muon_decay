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

// #define c 29979245800.0 //unit: cm/s
#define m_0 105.6583755 //unit: MeV/c^2
#define m_e 0.51099895 //unit: MeV/c^2
#define pi (atan(1)*4)
#define coef 0.1535 //MeVcm^2/g

//energy loss porton

void energy_adjust(double E_temp, double& Gamma, double& Beta){
    Gamma = E_temp / m_0 + 1; //deriving Gamma from kinetic energy
    Beta = sqrt(1-(1/pow(Gamma, 2))); //deriving Beta from Gamma
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

double bethe_bloch(double W_max, double Gamma, double Beta, double eta, double rho){
    double I = 85.7e-6;
    double Z = 14.51888746, A = 29.09833728, z = 1.0;
    return -1.0 * coef * rho * (Z/A) * pow(z/Beta, 2) * (log(2 * m_e * pow(Gamma * Beta, 2) * W_max / pow(I, 2)) - 2 * pow(Beta, 2)
                    -delta_correc(Beta, Gamma) - 2 * shell_correc(Beta, Gamma) / Z);
}

int main(){
    string filename;
    cout<<"Name of the output file: ";
    cin>>filename;
    ofstream output(filename);

    double Gamma, Beta, dEdx, eta;
    double W_max;
    for(double KE = 10.0; KE < 10000.0; KE += 100.0){
        for(double rho = 0.4; rho < 2.0; rho += 0.02){
            energy_adjust(KE, Gamma, Beta);
            eta = Gamma * Beta;
            W_max = 2.0 * m_e * pow(eta, 2.0);
            dEdx = -1.0 * bethe_bloch(W_max, Gamma, Beta, eta, rho * 1.0e-3);
            output<<KE<<" "<<rho<<" "<<dEdx<<" "<<Gamma<<" "<<Beta<<" "<<eta<<"\n";
        }
    }
    output.close();
}