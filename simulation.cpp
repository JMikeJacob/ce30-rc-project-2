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

double RCSimulation::sign (double x)
{
    double epsilon = 1e-16;
    if (x > epsilon) return 1;
    if (x < (-1)*epsilon) return -1;
    else return 0;
}

void RCSimulation::runge_kutta (Wave* Voltage, int waveCount, double endTime)
{
  double voltage, t, H, K_1, K_2, K_3, K_4, voltage_out, voltage_h2, voltage_h, q, square; 
  double amp, freq, phase, offset, R = resistance, C = capacitance;
  // voltage_h2 is voltage(t + H/2) while voltage_h voltage(t+H)
  H = 0.0000625;
  q = 0;
  points = 0;
  for (double t = 0; t <= endTime; t = t + H)
  {
    voltage = 0;
    voltage_h2 = 0;
    voltage_h = 0;
    for(int i = 0; i <= waveCount; i++)
    {
      amp = Voltage[i].amp;
      freq = Voltage[i].freq;
      phase = Voltage[i].phase;
      offset = Voltage[i].offset;
      if (Voltage[i].type == "sinusoidal")
      {
        voltage += offset + amp*sin(2*M_PI*freq*t + phase);
        voltage_h2 += offset + amp*sin(2*M_PI*freq*(t+(H/2)) + phase);
        voltage_h += offset + amp*sin(2*M_PI*freq*(t+H) + phase);
      }
      if (Voltage[i].type == "triangular")
      {
        voltage += ((2*amp)/(M_PI))*amp*asin(sin((2*(M_PI)*freq*t + phase))) + offset;
        voltage_h2 += ((2*amp)/(M_PI))*amp*asin(sin((2*(M_PI)*freq*(t+(H/2)) + phase))) + offset;
        voltage_h +=  ((2*amp)/(M_PI))*amp*asin(sin((2*(M_PI)*freq*(t+H) + phase))) + offset;
      }
      if (Voltage[i].type == "square")
      {
        voltage += offset + amp*(sign(sin(2*(M_PI)*freq*t + phase)));
        voltage_h2 += offset + amp*(sign(sin(2*(M_PI)*freq*(t*(H/2)) + phase)));
        voltage_h += offset + amp*(sign(sin(2*(M_PI)*freq*(t+H) + phase))); //what is SIGN fn in C++?
      }
    }   
        
    K_1 = ((voltage)/R) - (q/(R*C));
    K_2 = ((voltage_h2)/R) - (q + K_1*(H/2))/(R*C);
    K_3 = (voltage_h2)/R - q/(R*C);
    K_4 = (voltage_h)/R - (q + K_3*H)/(R*C);
    
    q = q + (K_1 + K_2 + K_3 + K_4)*(H/6);
    voltage_out = R*K_1;
    cout << "t: " << t << " v_in: " << voltage << " v_out: " << voltage_out << endl;
    v_in.push_back(voltage);
    v_out.push_back(voltage_out);
    sec.push_back(t);
    points++;
  }
}

void RCSimulation::printGraph()
{
  cout << "Simulation Results:\n\n";
  cout << setprecision(9);
  cout << "     t      |    V_in    |     V_out     |" << endl; 
  for(int i = 0; i < points; i++)
  {
    /*
    if(log10(sec[i])>= 8 || log10(sec[i] <= 0.00001) ||
       log10(v_in[i])>= 8 || log10(v_in[i] <= 0.00001) ||
       log10(v_out[i])>= 8 || log10(v_out[i] <= 0.00001))
    {
      cout << scientific; 
    } 
    else
    {
      cout << fixed; 
    }*/
    cout << sec[i] << "|" << v_in[i] << "|" << v_out[i] << endl;
  }
  cout << std::resetiosflags;
}

void RCSimulation::saveToFile(Wave* Voltage, int waveCount)
{
  string filename;
  cout << "Filename: ";
  cin >> filename;
  
  ofstream ofs;
  ofs.open(filename.c_str());
  ofs << "Simulation Parameters:\n";
  ofs << "Resistance: " << resistance << endl;
  ofs << "Capacitance: " << capacitance << endl;
  for(int i = 0; i <= waveCount; i++)
  {
    ofs << "\nInput Voltage " << i + 1 << endl;
    ofs << "Type: " << Voltage[i].type;
    ofs << "Amplitude: " << Voltage[i].amp;
    ofs << "Frequency: " << Voltage[i].freq;
    ofs << "Phase Angle: " << Voltage[i].phase;
    ofs << "DC Offset: " << Voltage[i].offset;
    ofs << endl;
  }
  ofs << "\nSimulation Results:\n";
  for(int i = 0; i < points; i++)
  {
     
     ofs << sec[i] << "," << v_in[i] << "," << v_out[i] << endl;
  }
  ofs.close();
  ofs.close();
}

void RCSimulation::clearVectors()
{
  v_in.clear();
  v_out.clear();
  sec.clear(); 
  points = 0;
}
