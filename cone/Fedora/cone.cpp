#include <iostream>
#include <cmath>
#include <fstream>
#include <random>
using namespace std;

//defining constants
#define C 299792.458 //unit: m/s
#define tau 2.1969811e-6 //unit: s
#define m_0 105.6583755 //unit: MeV/c^2
#define pi (atan(1)*4)

ofstream output("cone.txt");
ofstream test("test.dat");

/*
    Variable definitions:
    L_v = Vertical distance
    Tau = resting muon lifetime
    t = moving muon lifetime using relativity
    v = velocity of muon
    Time = time travelling given distance L
    Beta = v/c
    Lamda = decay constant = 1/t
*/
double L_v = 15.0;
double L, t, v, E_k, Time, Beta, Gamma, Lambda;
double probability, sim_prob, uncertainty;
double factor;
double scope_area = 1.824146925e-8;

/*
    Cone geometry:
    psi = 1/2 open angle
    a = major axis
    b = minor axis
    theta = angle to zenith
*/

double psi = ((double)9.7/180) * pi;
double a, b, theta;

void init_calc(){
    Gamma = E_k * 1e3 / m_0 + 1; //deriving Gamma from kinetic energy
    t = Gamma * tau; //adjusting lifetime using Gamma
    Lambda = 1 / t;
    Beta = sqrt(1-(1/pow(Gamma, 2))); //deriving Beta from Gamma
    v = C * Beta;    
}

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
    return (Random(eng)<=probability);
}

void write(double x){
    output<<x/pi*180.0<<" "<<sim_prob<<" "<<uncertainty<<" "<<factor * pow(cos(x),2)<<"\n";
}

void batch_calc(){
    double h, k = 0.0;
    h = L * sin(theta);
    int not_decayed = 0;
    double spacing = 0.1;
    for(double i = h - a; i < h + a; i+=spacing){
        for(double j = k - b; j < k + b; j+=spacing){
            test<<i<<" "<<j<<"||";
            if(pow((i-h) / a, 2) + pow((j-k) / b, 2)<=1.0){ //check if in ellipse
                double dist = sqrt(pow(i, 2) + pow(j, 2) + pow(L_v, 2)); 
                Time = dist / v;
                probability = 1e7 * scope_area / (pow(dist,2) * 2 * pi) * exp(-1.0 * Lambda * Time); //deriving survival probability
                // cout<<probability<<"\n";
                for(int n = 0; n<1; n++) if(montecarlo(probability))not_decayed++;
            }
        }
    }
    test<<"\n";
    sim_prob = (double) not_decayed / (40.0 * a * b);
    uncertainty = 1.0 / sqrt((double)not_decayed);
}

int main(){
    //requesting inputs and printing outputs
    cout<<"Initial muon kinetic energy in GeV: ";
    cin>>E_k;
    init_calc();
    geometric_adjust();
    batch_calc();
    factor = sim_prob;
    // write(0.0);
    int n = 25; //number of batches to run
    n++;
    for(int i = 1; i<n - 1; i++){
        theta = (double)i / (n*2) * (pi - psi);
        geometric_adjust();
        test<<i<<" "<<theta/pi * 180.0<<" "<<a<<" "<<b<<"\n";
        batch_calc();
        // write(theta);
    }
    
    return 0;
}

