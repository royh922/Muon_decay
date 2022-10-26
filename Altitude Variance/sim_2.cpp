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
    const double p_air_section = 500e-31; //collision cross section in mb (10^-31 m^2);
    const double radius = sqrt(p_air_section / pi);
    const double radius_squared = pow(radius, 2.0);
    cout<<radius_squared<<"\n";
    const double E = 1000;
    const double bound = 1e-13;

    // cout<<flux<<" "<<bound<<"\n";

    //air desnity equation: 1.225* pow((288.16-0.0065*h)/288.16, 4.2561) h in meters

    set<pair<double, pair<double, double>>> points; //target points in z, x, y (easier sort for z)

    int rays = 1;
    while(rays--){
        double height = 15000.0;
        while(height > 5000.0){
            // cout<<height<<"\n";
            double density = 1.225e-3 * pow((288.16-0.0065*height)/288.16, 4.2561) * 0.02504 / 1.2041e-3 * 1e27;
            int N = round(density * bound * bound * 15000.0);
            while(N--) points.insert({uni_dis(height - 500.0, height), {uni_dis(bound * -1.0, bound), uni_dis(bound * -1.0, bound)}});
            height -= 100.0;
        }
        for(auto itr = points.rbegin(); itr != points.rend(); itr++){
            auto point = *itr;
            /* if(pow(point.second.first, 2.0) + pow(point.second.second, 2.0) <= radius_squared){
                output<<point.first<<"\n";
                break;
            }    */
            output<<point.first<<" "<<point.second.first<<" "<<point.second.second<<"\n";     
        }

        points.clear();
    }

    output.close();

    return 0;
}