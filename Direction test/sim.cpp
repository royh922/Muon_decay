#include<iostream>
#include<cmath>
#include<fstream>
using namespace std;

#define R 10.0
#define spacing 0.001

int main(){
    for(double i = -R; i < R; i += spacing){
        for(double j = -R; j < R; j += spacing){
            for(double k = R; k < 0; k -= spacing){
                if((pow(i, 2) + pow(j, 2) + pow(k, 2)) < 100.0){
                    
                }
            }
        }
    }
    return 0;
}