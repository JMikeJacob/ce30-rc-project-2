#ifndef SIMULATION_H
#define SIMULATION_H

#include <cstdlib>
#include <iostream>
#include <fstream>
#define _USE_MATH_DEFINES
#include <math.h> //M_PI
# define M_PI           3.14159265358979323846  /* pi */
#include <vector> 
#include "waveform.h"

using namespace std;

class RCSimulation
{
  private:
    double resistance, capacitance;
    vector<double> v_in, v_out, sec;
    int points;
  public:
    double endTime, initCharge;
    void editR();
    void editC();
    void inputRC();
    void printParam();
    double sign(double);
    double highestFreq(Wave*, int);
    void runge_kutta(Wave*, int);
    void clearVectors();
    void saveToFile(Wave*, int);
    
};

#endif
