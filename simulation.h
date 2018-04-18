#ifndef SIMULATION_H
#define SIMULATION_H

#include <iostream>

using namespace std;

class RCSimulation
{
  private:
    double resistance, capacitance;
  public:
    void editR();
    void editC();
    void inputRC();
    void printParam();
    
};

#endif
