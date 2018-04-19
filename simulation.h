#ifndef SIMULATION_H
#define SIMULATION_H

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#define _USE_MATH_DEFINES
#include <math.h>
# define M_PI           3.14159265358979323846  /* pi */
#include <vector>
#include <iomanip>
#include <limits>
#include "waveform.h"

using namespace std;

class RCSimulation
{
  private:
    double resistance, capacitance;
    vector<double> v_in, v_out, sec;
    int points;
  public:
    void editR();
    void editC();
    void inputRC();
    void printParam();
    double sign(double);
    double highestFreq(Wave*, int);
    void runge_kutta(Wave*, int, double);
    void printGraph();
    void clearVectors();
    void saveToFile(Wave*, int);
    
};

#endif
