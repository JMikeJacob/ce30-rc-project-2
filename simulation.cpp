#include "simulation.h"

void RCSimulation::editR()
{
  cout << "Input Resistor value (in Ohms): ";
  cin >> resistance;
  cin.clear();
}

void RCSimulation::editC()
{
  cout << "Input Capacitor value (in Farads): ";
  cin >> capacitance;
  cin.clear();
}

void RCSimulation::inputRC()
{
  editR();
  editC(); 
}

void RCSimulation::printParam()
{
  cout<< "Resistance (in Ohms): " << resistance<<endl;
  cout<< "Capacitance (in Farads): " << capacitance << endl;
}
