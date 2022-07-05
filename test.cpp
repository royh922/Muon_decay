#include <iostream>
#include <cmath>
#include <fstream>
#include <random>
using namespace std;

#define pi atan(1)*4

void ad(int& g){
    g++;
}

int main()
{
    int g = 123;
    af(&g);
    cout<<g<<"\n";
    ad(g);
    cout<<g<<"\n";
    return 0;
}
