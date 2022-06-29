#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
using namespace std;

double x_0, y_0;
double R, x, y, vx, vy, t, tf, dt;
double theta, omega;
double t0 = 0.0;
#define PI 3.14159265358979323846;
void output(){
    t = t0;
    ofstream output("data.dat");
    while(t<=tf){
        output<<t<<"\t"<<x<<"\t"<<y<<"\t"<<vx<<"\t"<<vy<<"\n";
        theta = omega*(t-t0);
        x = x_0 + R * cos(theta);
        y = y_0 + R * sin(theta);
        vx = -omega * R * sin(theta);
        vy = omega * R * cos(theta);
        t+=dt;
    }
}

int main(){
    cout<<"This program plots a circle given appropriate variables\n";
    do{
        cout<<"Enter a value for Omega: ";
        cin>>omega;
        if(omega<=0) cout<<"Invalid omega value! Must be greater than 0!\n";
    }while(omega<=0);
    do{
        cout<<"Enter a value for R: ";
        cin>>R;
        if(omega<=0) cout<<"Invalid R value! Must be greater than 0!\n";
    }while(R<=0);
    cout<<"Enter the center of the circle (x0, y0): ";
    cin>>x_0>>y_0;
    cout<<"Enter t0, tf, and dt: ";
    cin>>t0>>tf>>dt;
    printf("Omega: %lf, R: %lf, (x0, y0): (%lf, %lf), (t0, tf, dt): (%lf, %lf, %lf)\n", omega, R, x_0, y_0, t0, tf ,dt);
    output();
    return 0;
}