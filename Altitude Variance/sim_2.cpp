#include <iostream>
#include <cmath>
#include <fstream>
#include <random>
#include <set>
#include <utility>
using namespace std;

const double pi = 4 * atan(1);

random_device rd;
default_random_engine eng(rd());

double uni_dis(const double min, const double max){
    //uniform number generation
    uniform_real_distribution<double> Random(min, max);
    return Random(eng);
}

int main(){
    ofstream output("test.dat");
    const double radius_squared = pow(3.15e-5, 2.0); //collision cross section radius in mm;
    set<pair<double, pair<double, double>>> points; //target points in z, x, y (easier sort for z)
    
    int rays = 100000;
    while(rays--){
        int N = 1000;
        while(N--) points.insert({uni_dis(0, 1.0), {uni_dis(-0.0005, 0.0005), uni_dis(-0.0005, 0.0005)}});

        for(auto itr : points){
            if(pow(itr.second.first, 2.0) + pow(itr.second.second, 2.0) <= radius_squared){
                output<<itr.first<<"\n";
                break;
            }        
        }

        points.clear();
    }

    output.close();

    return 0;
}