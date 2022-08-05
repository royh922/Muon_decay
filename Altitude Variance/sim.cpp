#include <iostream>
#include <cmath>
#include <fstream>
#include <random>
#include <set>
#include <utility>
using namespace std;

//scale down
random_device rd;
default_random_engine eng(rd());
uniform_int_distribution<int> Random(-500, 500);

double uni_dis(){
    //uniform number generation
    return Random(eng);
}

int main(){
    
    ofstream output("output.dat");

    double density = 8.47e-3; //number density of dry air in 1e18 mm^-3
    double dz = 1.0; //step distance in mm
    double z = 0.0; //penetration depth in m
    double radius = 155e-12; //dry air cross section radius in m;
    // bool ray [1000][1000] = {false};
    double max_num = density * dz * 1e6; //area = 1e-6 mm * 1e-6 mm
    
    set<pair<int, int>> points;
    vector<pair<int, int>> rays;

    int N = 1000000;
    while(N--) rays.push_back({uni_dis(), uni_dis()});

    while(z < 15000){
        
        //populate target points
        for(int i = 0; i<max_num; i++) points.insert(make_pair(uni_dis(), uni_dis()));


        int cnt = 0; //target hit count
        
        for(vector<pair<int, int>>::iterator it = rays.begin(); it != rays.end();){
            if(points.find(rays[it - rays.begin()]) != points.end()){
                cnt++;
                rays.erase(it);
            }
            else it++;
        }

        /* for(int i = -500; i<500; i++){
            for(int j = -500; j<500; j++){
                if(ray[i + 500][j + 500]) continue;
                const bool check = points.find({i, j}) != points.end();
                if(check){
                    ray[i +500][j + 500] = true;
                    cnt++;
                }
            }
        } */
        points.clear();
        if(cnt == 0) break;
        output<<z<<" "<<cnt<<"\n";
        z += dz / 1000.0;
    }

    output.close();    

    return 0;
}