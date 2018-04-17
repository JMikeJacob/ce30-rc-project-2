#include <cstdlib>
#include <iostream>
#include <string>
#define _USE_MATH_DEFINES
#include <math.h>
# define M_PI           3.14159265358979323846  /* pi */
#include <vector>

using namespace std;

void runge_kutta (string voltage_type, double amp, double freq, double phase, double offset, double R, double C)
{
    vector<double> v_in, v_out;
    vector<int> time;
    double voltage, t, H, K_1, K_2, K_3, K_4, voltage_out, voltage_h2, voltage_h, q; 
    // voltage_h2 is voltage(t + H/2) while voltage_h voltage(t+H)
    H = 0.000125;
    q = 0;
        
    for (int t = 0; t <= 3; t = t + H) // for 3 seconds only
    {
        if (voltage_type == "sine")
        {
            voltage = offset + amp*sin(2*M_PI*freq*t + phase);
            voltage_h2 = offset + amp*sin(2*M_PI*freq*(t+(H/2)) + phase);
            voltage_h = offset + amp*sin(2*M_PI*freq*(t+H) + phase);
        }
        if (voltage_type == "triangle")
        {
            voltage = ((2*amp)/(M_PI))*amp*asin(sin((2*(M_PI)*freq*t + phase))) + offset;
            voltage_h2 = ((2*amp)/(M_PI))*amp*asin(sin((2*(M_PI)*freq*(t+(H/2)) + phase))) + offset;
            voltage_h =  ((2*amp)/(M_PI))*amp*asin(sin((2*(M_PI)*freq*(t+H) + phase))) + offset;
        }
    //if (voltage_type = "square)
      //  voltage = offset + amp* //what is SIGN fn in C++?
        
        
        K_1 = (voltage)/(R - q)/(R*C);
        K_2 = (voltage_h2)/(R -(q + K_1*(H/2)))/(R*C);
        K_3 = (voltage_h2)/(R - q)/(R*C);
        K_4 = (voltage_h)/(R - (q - K_3*H))/(R*C);
        
        q = q + (K_1 + K_2 + K_3 + K_4)*(H/6);
        voltage_out = R*K_1;
        
        v_in.push_back(voltage);
        v_out.push_back(voltage_out);
        time.push_back(t);
    }
    
}

