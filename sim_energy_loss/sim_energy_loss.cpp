#include <iostream>
#include <cmath>
#include <fstream>
#include <random>
using namespace std;

#define c 29979245800 //unit: cm/s
#define m_0 105.6583755 //unit: MeV/c^2
#define m_e 0.51099895 //unit: MeV/c^2
#define tau 2.1969811e-6 //unit: s
#define pi (atan(1)*4)
#define coef 0.1535 //MeVcm^2/g

double rho = 1.29e-3, Z = 14.51888746, A = 29.09833728, z = 1.0;
double E_k, Beta, Gamma, v, L_v = 15.0e5, L;
double dt = 1.0e-8, t;
double a, b;
double scope_area = 1.824146925e-8;
double psi = ((double)9.7/180) * pi, theta;
double batch_prob, uncertainty;
double factor;
double I = 85.7e-6;

double C_0 = -10.6, X_0 = 1.742, X_1 = 4.28, m = 3.4, a = 0.1091;

ofstream output("output.txt");

//geometrical acceptance portion

void geometric_adjust(){
    L = L_v / cos(theta);
    b = L / cos(theta) * tan(psi);
    a = (tan(theta + psi) - tan(theta - psi)) * L_v / 2;
}

bool montecarlo(double prob){
    //random number generation
    random_device rd;
    default_random_engine eng(rd());
    uniform_real_distribution<> Random(0.0, 1.0);
    return (Random(eng)<=prob);
}

void batch_calc(){
    double h, k = 0.0;
    h = L * sin(theta);
    int not_decayed = 0;
    double spacing = 0.1;
    for(double i = h - a; i < h + a; i+=spacing){
        for(double j = k - b; j < k + b; j+=spacing){
            if(pow((i-h) / a, 2) + pow((j-k) / b, 2)<=1.0){
                double t_total = 0.0;
                double x = 0.0;
                double E_temp = E_k;
                double dist = sqrt(pow(i, 2) + pow(j, 2) + pow(L_v, 2));
                double probability = 1e7 * scope_area / (pow(dist,2) * 2 * pi) * exp(-1.0 * t_total / t);
                while(E_temp > 0.0 && montecarlo(probability)){
                    /*
                        How to incorporate energy loss into montecarlo simulation?
                    */
                    energy_adjust();
                    double eta = Gamma * Beta;
                    double W_max = 2.0 * m_e * pow(c, 2) * eta;
                    x += bethe_bloch(W_max, eta, E_temp);
                    t_total += dt * Gamma;
                    probability = exp(-1.0 * t_total / t); //deriving survival probability
                    if(x>L){
                        not_decayed++;
                        break;
                    }
                }
            }
        }
    }
    batch_prob = (double) not_decayed / (400.0 * a * b);
    uncertainty = 1.0 / sqrt((double)not_decayed);
}

//energy loss porton

void energy_adjust(){
    Gamma = E_k / m_0 + 1; //deriving Gamma from kinetic energy
    Beta = sqrt(1-(1/pow(Gamma, 2))); //deriving Beta from Gamma
    t = Gamma * tau;
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

double bethe_bloch(double W_max, double eta, double& E_temp){
    double dx = v * dt;
    double dE_k = -1.0 * coef * rho * (Z/A) * pow(z/Beta, 2) * (log(2 * m_e * pow(Gamma * v, 2) * W_max / pow(I, 2)) - 2 * pow(Beta, 2)
                    -delta_correc(Beta, Gamma) - 2 * shell_correc(Beta, Gamma) / Z) * dx;
    E_temp += dE_k;
    return dx;
}

void write(double x){
    output<<x/pi*180.0<<" "<<batch_prob<<" "<<uncertainty<<" "<<factor * pow(cos(x),2)<<"\n";
}


int main(){
    cout<<"Kinetic enrgy of muon(GeV): ";
    cin>>E_k;
    E_k *= 1000.0; //GeV to MeV
    int n = 25; //number of batches to run
    for(int i = 0; i<n; i++){
        theta = (double)i / (n*2) * (pi - 2 * psi);
        
        geometric_adjust();
        batch_calc();
        write(theta);
    }
}