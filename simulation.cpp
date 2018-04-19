#include "simulation.h"

void RCSimulation::editR() //edit resistance value
{
  cout << "Input Resistor value (in Ohms): ";
  cin >> resistance;
  cin.clear();
}

void RCSimulation::editC() //edit capacitance value
{
  cout << "Input Capacitor value (in Farads): ";
  cin >> capacitance;
  cin.clear();
}

void RCSimulation::inputRC() //input R and C values by calling
{                            //both edit functions in one function
  editR(); 
  editC(); 
}

void RCSimulation::printParam() //prints R and C values
{
  cout<< "Resistance (in Ohms): " << resistance<<endl;
  cout<< "Capacitance (in Farads): " << capacitance << endl;
}

double RCSimulation::sign (double x) //sign function
{
    double epsilon = 1e-16; //treats values close to epsilon as 0
    if (x > epsilon) return 1; //positive number returns 1
    if (x < (-1.0)*epsilon) return -1; //negative number returns -1
    else return 0; //number is zero
}

double RCSimulation::highestFreq(Wave* Voltage, int waveCount)
{ //function for determining highest frequency among input voltages
  double highestFreq = 0.0;
  for(int i = 0; i <= waveCount; i++)
  {
    if(Voltage[i].freq > highestFreq)
    { //if a higher value than the held one is detected, it replaces
      highestFreq = Voltage[i].freq;    
    }
  }
  return highestFreq; //return the highest value
}

void RCSimulation::runge_kutta (Wave* Voltage, int waveCount)
{
  double voltage, t, H, K_1, K_2, K_3, K_4, voltage_out, voltage_h2, 
         voltage_h, q, square; 
  double amp, freq, phase, offset, R = resistance, C = capacitance;
  /*Runge-Kutta Method
  
  */
  
  // voltage_h2 is voltage(t + H/2) while voltage_h voltage(t+H)
  //maximum step size is 1/16 the period of the highest-freq wave
  H = (1.0/16.0)*(1/highestFreq(Voltage, waveCount));
  if(endTime/H < 500.0)//number of data points should be at least 500
  {
    H = endTime/500.0; 
  }
  q = initCharge; //initial value
  points = 0; //will count number of points
  //main fourth-order Runge-Kutta algorithm
  //will iterate for each datapoint until endTime
  for (double t = 0; t <= endTime; t = t + H)
  {
    voltage = 0;
    voltage_h2 = 0;
    voltage_h = 0;
    //input voltages at t, t+H/2, and t+h are summed up
    for(int i = 0; i <= waveCount; i++)
    {
      amp = Voltage[i].amp;
      freq = Voltage[i].freq;
      phase = Voltage[i].phase;
      offset = Voltage[i].offset;
      if (Voltage[i].type == "sinusoidal")
      { //equations for sinusoidal waveform
        voltage += offset + amp*sin(2*M_PI*freq*t + phase);
        voltage_h2 += offset + amp*sin(2*M_PI*freq*(t+(H/2)) + phase);
        voltage_h += offset + amp*sin(2*M_PI*freq*(t+H) + phase);
      }
      if (Voltage[i].type == "triangular")
      { //equations for triangular waveforms
        voltage += ((2*amp)/(M_PI))*amp*asin(sin((2*(M_PI)*freq*t + 
                     phase))) + offset;
        voltage_h2 += ((2*amp)/(M_PI))*amp*asin(sin((2*(M_PI)*freq*
                       (t+(H/2)) + phase))) + offset;
        voltage_h +=  ((2*amp)/(M_PI))*amp*asin(sin((2*(M_PI)*freq*
                       (t+H) + phase))) + offset;
      }
      if (Voltage[i].type == "square")
      { //equations for square waveforms
        voltage += offset + amp*(sign(sin(2*(M_PI)*freq*t + phase)));
        voltage_h2 += offset + amp*(sign(sin(2*(M_PI)*freq*(t+(H/2)) +
                      phase)));
        voltage_h += offset + amp*(sign(sin(2*(M_PI)*freq*
                     (t+H) + phase)));
      }
    }   
    //K_1 to K_4 values of Runge-Kutta Method
    K_1 = ((voltage)/R) - (q/(R*C));
    K_2 = ((voltage_h2)/R) - (q + K_1*(H/2.0))/(R*C);
    K_3 = ((voltage_h2)/R) - (q + K_2*(H/2.0)/(R*C));
    K_4 = ((voltage_h)/R) - ((q + K_3*H)/(R*C));
    //approximate solution y_i(t+H)
    q = q + (K_1 + K_2 + K_3 + K_4)*(H/6.0);
    //Ohm's Law to get voltage across resistor R
    voltage_out = R*K_1; // V = I*R
    v_in.push_back(voltage);//inserts input voltage sum to vector
    v_out.push_back(voltage_out);//inserts output voltage to vector
    sec.push_back(t);//inserts time t to vector
    points++; //counts number of datapoints
  }
}

void RCSimulation::saveToFile(Wave* Voltage, int waveCount)
{ //function for saving parameters and results to csv file
  //it saves to csv file as it can easily display the data
  string filename;
  cout << "Filename (without extension): ";
  cin >> filename; //asks for name of save file
  filename += ".csv"; //adds .csv extension
  ofstream ofs;
  ofs.open(filename.c_str()); //creates or opens file
  //insert parameters into file
  ofs << "Simulation Parameters\n";
  ofs << "Resistance," << resistance << endl;
  ofs << "Capacitance, " << capacitance << endl;
  for(int i = 0; i <= waveCount; i++)
  {
    ofs << "\nInput Voltage " << i + 1 << endl;
    ofs << "Type, " << Voltage[i].type << endl;
    ofs << "Amplitude, " << Voltage[i].amp << endl;
    ofs << "Frequency, " << Voltage[i].freq << endl;
    ofs << "Phase Angle, " << Voltage[i].phase << endl;
    ofs << "DC Offset, " << Voltage[i].offset << endl;
    ofs << endl;
  }
  ofs << "\nStart Time,0, End Time," << endTime << endl;
  ofs << "q(t=0)" << initCharge << endl; 
  //insert simulation results (time, v_in, v_out) to file 
  ofs << "\nSimulation Results\n";
  ofs << "t (s),V_in (volts),V_out (volts)" << endl;
  for(int i = 0; i < points; i++)
  { //each iteration is one row, each data having a specific column
     ofs << sec[i] << "," << v_in[i] << "," << v_out[i] << endl;
  }
  ofs.close();
}

void RCSimulation::clearVectors()
{ //function to clear vectors and values for the next simulation
  v_in.clear();
  v_out.clear();
  sec.clear(); 
  points = 0;
  initCharge = 0;
  endTime = 0;
}
