#include <iostream>
#include <cstdlib>
#include <string>
#include "waveform.h"
#include "simulation.h"

using namespace std;

void runInterface();
void printInterface(Wave*, RCSimulation, int);
void simInterface(Wave*, RCSimulation, int);

void runInterface()
{
  int waveCount = 0, size = 20;
  bool addBool = true, editBool = false, quitBool = false;
  string choice = "";
  int waveChoice = -1;
  
  Wave* Voltage = new Wave[size];
  RCSimulation Sim;
  
  cout << "Input Parameters:\n";
  Sim.inputRC();
  cout << "\nInput Voltage 1:\n";
  Voltage[0].inputData();
  do
  {
    cout << "Add another voltage source (Y/N)? ";
    cin >> choice;
    cin.clear();
    if(choice=="Y" || choice=="y")
    {
      waveCount++;
      cout << "\nInput Voltage " << waveCount+1 << ":\n";
      Voltage[waveCount].inputData();
    }
    else if(choice == "N" || choice == "n")
    {
      addBool = false;
    }
  } while(addBool); 
  do
  {
    system("CLS");
    printInterface(Voltage, Sim, waveCount); 
    
    choice = "";
    waveChoice = -1;
    editBool = true;
    addBool = true;
    
    cout << "\nChoose operation:";
    cout << "\n(a) Start Simulation\n(b) Edit Input Voltages";
    cout << "\n(c) Edit Resistance\n(d) Edit Capacitance\n(e) Quit\n";
    cout << "\nChoice: ";
    cin >> choice;
    cin.clear();
    if(choice == "A" || choice == "a")
    {
      simInterface(Voltage, Sim, waveCount);
    }
    else if(choice == "B" || choice == "b")
    {
      do
      {
        system("CLS");
        cout << "Editing Input Voltages\n";
        for(int i = 0; i <= waveCount; i++)
        {
          cout << "\nInput Voltage " << i+1 << ":\n";
          Voltage[i].printData();
        } 
        addBool = true;
        cout << endl << "Choose Voltage (Input 0 if done): ";
        cin >> waveChoice;
        cin.clear();
        if(waveChoice == 0)
        {
          editBool = false;
        }
        else if(waveChoice <= waveCount + 1 && waveChoice > 0)
        {
          do
          {
            system("CLS");
            cout << "\nEditing Input Voltage " << waveChoice << endl;
            Voltage[waveChoice-1].printData();
            cout<<"\nEdit which parameter?\n(a) Type\n(b) Amplitude";
            cout<<"\n(c) Frequency\n(d) Phase Angle\n(e) DC Offset";
            cout << "\n(f) None";
            cout<<"\nChoice: ";
            cin >> choice;
            cin.clear();
            if(choice == "a" || choice == "A")
            {
              Voltage[waveChoice-1].editType();
            }
            else if(choice == "b" || choice == "B")
            {
              Voltage[waveChoice-1].editAmp();  
            }
            else if(choice == "c" || choice == "C")
            {
              Voltage[waveChoice-1].editFreq(); 
            }
            else if(choice == "d" || choice == "D")
            {
              Voltage[waveChoice-1].editPhase(); 
            }
            else if(choice == "e" || choice == "E")
            {
              Voltage[waveChoice-1].editDCOff(); 
            }
            else if(choice == "f" || choice == "F")
            {
              addBool = false; 
            }
          } while(addBool);
        } 
      } while(editBool);
    }
    else if(choice == "C" || choice == "c")
    {
      Sim.editR();  
    }
    else if(choice == "D" || choice == "d")
    {
      Sim.editC(); 
    }
    else if(choice == "E" || choice == "e")
    {
      quitBool = true; 
    }
  } while(!quitBool);
  
  cout << "Program exited." << endl;
  
  delete [] Voltage;
}

void printInterface(Wave* Voltage, RCSimulation Sim, int waveCount)
{
  cout << "Simulation Parameters:\n\n";
  Sim.printParam();
  for(int i = 0; i <= waveCount; i++)
  {
    cout << "\nInput Voltage " << i+1 << ":\n";
    Voltage[i].printData(); 
  }
}

void simInterface(Wave* Voltage, RCSimulation Sim, int waveCount)
{
  string save = "";
  double endTime = 0;
  Sim.clearVectors();
  cout << "Simulation end time (in seconds): ";
  cin >> endTime;
  Sim.runge_kutta(Voltage, waveCount, endTime);
  system("CLS");
  Sim.printGraph();
  cout << "Save results to file (Y/N)? ";
  cin >> save;
  if(save == "Y" || save == "y")
  {
    Sim.saveToFile(Voltage, waveCount); 
  }
}

int main()
{
  runInterface();
}
