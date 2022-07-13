/*
    This program simulates muon decay in the atmosphere and records success rates from different angles (from zenith) of the telescope.
    Author: Jui-Teng Hsu (Roy)
    Summer 2022
*/

/*
    Variation in energy, variation in altitude
    3.5 GeV Std, 9,1 GeV Mean;
    Chi^2
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
#define scope_area 1.824146925e2 //cm^2
#define psi (pi * 9.7/180)
#define dt 1.0e-8
#define L_v 15.0e5 //cm STARTING ALTITUDE 
#define spacing 25000.0 //cm

// double E_k;
double batch_prob[5];
double factor[5];

//normal distribution generator
/* double normal_dis(){
    //random number generation
    random_device rd;
    default_random_engine eng(rd());
    normal_distribution<double> Random(9.0, 2.0);
    return Random(eng);
} */

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
    return dx;
}

//geometrical acceptance portion

void geometric_adjust(double& a, double& b, double& L, double& h, double theta){
    L = L_v / cos(theta);
    b = L * tan(psi);
    double x = tan(theta + psi);
    double y = tan(theta - psi);
    a = (x-y) * L_v / 2;
    h = y * L_v + a;
}

double rho_calc(double h){//h in meters
    return 1.225e-3 * pow((288.16-0.0065*h)/288.16, 4.2561); //returns in kg/m^3
}

void batch_calc(double theta){
    double h, k = 0.0;
    double a, b, L;
    geometric_adjust(a, b, L, h, theta);
    // ofstream test("test.txt");

    double probability[5] = {0.0};
    for(double i = h - a; i < h + a; i+=spacing){
        for(double j = k - b; j < k + b; j+=spacing){
            if(pow((i-h) / a, 2) + pow((j-k) / b, 2)<=1.0){
            // if(( (i * L * sin(theta) + L_v * L_v) / (L*dist) ) > cos(psi)){
                // test<<i<<" "<<j<<"\n";
                double dist = sqrt(pow(i, 2) + pow(j, 2) + pow(L_v, 2));
                // double E_temp = normal_dis() * 1000.0;
                double cos_alpha = L_v / dist; //angle between line of particle and zenith
                double cos_delta = (i * L * sin(theta) + L_v * L_v) / (L*dist); //angle between line of particle and scintillator

                for(int cnt = 0; cnt<5; cnt++){
                    double t_total = 0.0;
                    double x = dist;
                    double E_temp = 3000.0 + cnt * 2000.0; //initial kinetic energy
                    double Gamma, Beta, v;
                    energy_adjust(E_temp, Gamma, Beta, v);
                    while(x > 0 && E_temp > 0){
                        energy_adjust(E_temp, Gamma, Beta, v);
                        double eta = Gamma * Beta;
                        double W_max = 2.0 * m_e * eta;
                        double height = cos_alpha * x / 100.0; //PROBLEM HERE
                        // x -= bethe_bloch(W_max, Gamma, Beta, E_temp, rho_calc(height));
                        x -= bethe_bloch(W_max, Gamma, Beta, E_temp, rho_calc(0.0012));
                        t_total += (dt / Gamma);
                    }
                    if(E_temp>0) probability[cnt] += scope_area * cos_delta / (pow(dist,2) * 2 * pi) * exp(-1.0 * t_total / tau); //deriving survival probability
                }
            }
        }
    }
    for(int i = 0; i<5; i++){
        batch_prob[i] = probability[i];
        if(theta == 0.0) factor[i] = batch_prob[i];
    }
}

int main(){
    string filename;
    cout<<"Filename of output data: ";
    cin>>filename;
    ofstream output(filename);
    // cout<<"Kinetic enrgy of muon(GeV): ";
    // double temp;
    // cin>>temp;
    // E_k = temp * 1000.0; //GeV to MeV
    int n = 20; //number of batches to run
    double theta;
    for(int i = 0; i<n; i++){
        theta = (double)i / n * (pi / 2 - 2 * psi);
        cout<<i<<" "<<theta / pi * 180<<"\n";
        batch_calc(theta);
        output<<theta/pi*180.0<<" ";
        for(int j = 0; j<5; j++){
            output<<batch_prob[j]<<" "<<factor[j] * pow(cos(theta),2)<<" ";
        }
        output<<"\n";
    }
    output.close();
}