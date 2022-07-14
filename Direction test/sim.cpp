#include<iostream>
#include<cmath>
#include<fstream>
using namespace std;

#define R 100
#define spacing 1
#define pi (atan(1)*4)

int main(){
    double hits[91] = {0.0};
    string filename;
    cout<<"Name of output file: ";
    cin>>filename;
    ofstream output(filename);
    for(int i = -R; i < R; i += spacing){
        for(int j = -R; j < R; j += spacing){
            for(int k = 0; k < R; k += spacing){
                double dist = sqrt((pow(i, 2) + pow(j, 2) + pow(k, 2))); 
                if(dist < R){
                    double weight = 1 / pow(dist, 2.0);
                    int degree = acos((double)k * 10.0 / (dist * 10.0)) / pi * 180.0;
                    if(degree < 0 || degree > 90) continue;
                    hits[degree] += weight;
                }
            }
        }
    }
    for(int i = 0; i<91; i++) output<<hits[i]<<"\n";

    output.close();
    return 0;
}