#include <iostream>
#include <cmath>
#include <fstream>
#include <random>
using namespace std;

//defining constants
#define C 299792458.0 //unit: m/s
#define tau 2.1969811e-6 //unit: s
#define m_0 105.6583755 //unit: MeV/c^2

ofstream output("simple_histogram_root.txt");

/*
    Variable definitions:
    L = distance travelled
    Tau = resting muon lifetime
    t = moving muon lifetime using relativity
    v = velocity of muon
    Time = time travelling given distance L
    Beta = v/c
    Lamda = decay constant = 1/t
*/
double L, t, v, E_k, Time, Beta, Gamma, Lambda;
double probability, sim_prob;

void calc(){
    Gamma = E_k * 1e3 / m_0 + 1; //deriving Gamma from kinetic energy
    t = Gamma * tau; //adjusting lifetime using Gamma
    Lambda = 1 / t;
    Beta = sqrt(1-(1/pow(Gamma, 2))); //deriving Beta from Gamma
    v = C * Beta;
    Time = L * 1e3 /v;
    probability = exp(-1.0 * Lambda * Time); //deriving survival probability
}

void montecarlo(int N){
    //random number generation
    random_device rd;
    default_random_engine eng(rd());
    uniform_real_distribution<> Random(0.0, 1.0);

    int not_decayed = 0;
    for(int i = 0; i<N; i++){
        double temp = Random(eng);
        if(temp<=probability) not_decayed++;
    }
    sim_prob = (double)not_decayed/N;
    output<<sim_prob<<"\n";
}

int main(){
    //requesting inputs and printing outputs
    cout<<"Initial muon kinetic energy in GeV: ";
    cin>>E_k;
    cout<<"Vertical length (KM): ";
    cin>>L;
    cout<<"Number of muons to simulate: ";
    int N;
    cin>>N;
    calc();
    printf("Gamma = %lf, Travel time = %lf, Lambda = %lf, Adjusted tau = %lf\n", Gamma, Time, Lambda, t);
    cout<<"Theoretical probability is: "<<probability<<"\n\n";
    for(int i = 0; i<1000; i++) montecarlo(N);
    return 0;
}

