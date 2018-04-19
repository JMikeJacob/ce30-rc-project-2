#include <iostream>
#include <cstdlib> //system("CLS")
#include <string> 
#include "waveform.h"
#include "simulation.h"

using namespace std;

void runInterface(); //mainframe for interface
void printInterface(Wave*, RCSimulation, int); //parameters
void simInterface(Wave*, RCSimulation, int); //simulation proper

void runInterface()
{
  int waveCount = 0, size = 20;
  bool addBool = true, editBool = false, quitBool = false;
  string choice = "";
  int waveChoice = -1;
  
  Wave* Voltage = new Wave[size]; //array of Voltage wave objects
  RCSimulation Sim; //Sim object containing simulation functions
  
  cout << "Input Parameters:\n";
  Sim.inputRC(); //input R and C values
  cout << "\nInput Voltage 1:\n";
  Voltage[0].inputData(); //input first voltage waveform
  do
  {//loops asking if the user wants to add another voltage
    cout << "Add another voltage source (Y/N)? ";
    cin >> choice;
    cin.clear();
    if(choice=="Y" || choice=="y")
    {
      waveCount++;//increments voltage source count
      cout << "\nInput Voltage " << waveCount+1 << ":\n";
      Voltage[waveCount].inputData(); //input nth voltage wave
    }
    else if(choice == "N" || choice == "n")
    {
      addBool = false; //bool to terminate loop
    }
  } while(addBool); 
  do
  { //main menu
    system("CLS");
    printInterface(Voltage, Sim, waveCount); //prints parameters
    
    choice = "";
    waveChoice = -1;
    editBool = true;
    addBool = true;
    
    cout << "\nChoose operation:";
    cout << "\n(a) Start Simulation\n(b) Add Input Voltage";
    cout << "\n(c) Edit Input Voltages\n(d) Edit Resistance";
    cout << "\n(e) Edit Capacitance\n(f) Quit\n\nChoice: ";
    cin >> choice;
    cin.clear();
    if(choice == "A" || choice == "a") //Start Simulation
    {
      simInterface(Voltage, Sim, waveCount); //simulation proper
    }
    else if(choice == "B" || choice == "b") //adds another voltage
    {
      waveCount++;
      cout << "\nInput Voltage " << waveCount+1 << ":\n";
      Voltage[waveCount].inputData(); 
    }
    else if(choice == "C" || choice == "c") //edits existing voltages
    {
      do //loops until user decides to finish by entering 0
      {
        system("CLS");
        cout << "Editing Input Voltages\n";
        for(int i = 0; i <= waveCount; i++)
        { //prints existing voltage information
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
          do //loops until user decides to finish editing
          {  //the current waveform
            system("CLS");
            cout << "\nEditing Input Voltage " << waveChoice << endl;
            Voltage[waveChoice-1].printData();
            cout<<"\nEdit which parameter?\n(a) Type\n(b) Amplitude";
            cout<<"\n(c) Frequency\n(d) Phase Angle\n(e) DC Offset";
            cout << "\n(f) None";
            cout<<"\nChoice: ";
            cin >> choice;
            cin.clear();
            if(choice == "a" || choice == "A")//edit type
            {
              Voltage[waveChoice-1].editType();
            }
            else if(choice == "b" || choice == "B")//edit amplitude
            {
              Voltage[waveChoice-1].editAmp();  
            }
            else if(choice == "c" || choice == "C")//edit frequency
            {
              Voltage[waveChoice-1].editFreq(); 
            }
            else if(choice == "d" || choice == "D")//edit phase angle
            {
              Voltage[waveChoice-1].editPhase(); 
            }
            else if(choice == "e" || choice == "E")//edit DC offset
            {
              Voltage[waveChoice-1].editDCOff(); 
            }
            else if(choice == "f" || choice == "F")//done editing
            {
              addBool = false; 
            }
          } while(addBool);
        } 
      } while(editBool);
    }
    else if(choice == "D" || choice == "d") //edit resistance
    {
      Sim.editR();  
    }
    else if(choice == "E" || choice == "e") //edit capacitance
    {
      Sim.editC(); 
    }
    else if(choice == "F" || choice == "f") //quit program
    {
      quitBool = true; 
    }
  } while(!quitBool);
  
  cout << "Program exited." << endl;
  
  delete [] Voltage; //deallocates Voltage array
}

void printInterface(Wave* Voltage, RCSimulation Sim, int waveCount)
{//function to print out all simulation parameters
  cout << "Simulation Parameters:\n\n";
  Sim.printParam(); //print R and C
  for(int i = 0; i <= waveCount; i++) //print input voltages
  {
    cout << "\nInput Voltage " << i+1 << ":\n";
    Voltage[i].printData(); 
  }
}

void simInterface(Wave* Voltage, RCSimulation Sim, int waveCount)
{//menu for simulation proper
  string save = "";
  double endTime = 0, initCharge = 0;
  Sim.clearVectors();
  cout << "Simulation end time (in seconds): ";
  cin >> Sim.endTime; //asks for end time of simulation endTime
  cout << "Initial conditions of charge q at t = 0 (default at 0): ";
  cin >> Sim.initCharge; //asks for initial conditions
  Sim.runge_kutta(Voltage, waveCount);
  while(1) //loops until correct choice is made
  {
    cout << "Save results to file (Y/N)? ";
    cin >> save;
    if(save == "Y" || save == "y") //save results to file
    {
      Sim.saveToFile(Voltage, waveCount);
      break; 
    }
    else if(save == "n" || save == "N") //quit sim without saving
    {
      break;
    }
  }
}

int main()
{
  runInterface(); //runs program in console
}
