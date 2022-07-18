#include<iostream>
#include<cmath>
#include<fstream>
using namespace std;

#define R 2000
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
                    double dot_product = (double)k * 10.0 / (dist * 10.0);
                    int degree = round(acos(dot_product) / pi * 180.0);
                    if(degree < 0 || degree > 90) continue;
                    double weight = 1 / pow(dist, 2.0) * dot_product / sin((double)degree / 180.0 * pi);
                    hits[degree] += weight;
                }
            }
        }
    }
    // for(int i = 1; i<91; i++) hits[i] /= sin((double) i / 180.0 * pi);
    for(int i = 0; i<91; i++) output<<hits[i]<<"\n";

    output.close();
    return 0;
}