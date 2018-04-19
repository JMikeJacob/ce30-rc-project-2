#include "waveform.h"

void Wave::editType() //edit waveform type
{
  bool invalid = true;
  cout << "Choose waveform type:\n"; 
  cout << "- sinusoidal\n- square\n- triangular\n";
  do //loops until valid input
  {
    cout << "Choice: ";
    cin >> type;
    cin.clear();
    if(type=="sinusoidal" || type=="square" || type=="triangular")
    {
      invalid = false; //triggers loop to end
    }
    else
    {
      cout << " Invalid input!" << endl;
    }
  } while(invalid);
}

void Wave::editAmp() //edit waveform amplitude
{
  cout << "Input amplitude (in volts): ";
  cin >> amp;
  cin.clear();
}

void Wave::editFreq() //edit waveform frequency
{
  cout << "Input frequency (in Hz): ";
  cin >> freq;
  cin.clear();
}

void Wave::editPhase() //edit phase angle
{
  cout << "Input phase (in radians): ";
  cin >> phase;
  cin.clear();
}

void Wave::editDCOff() //edit DC offset
{
  cout<< "Input DC offset (in volts): ";
  cin>> offset;
  cin.clear();
}

void Wave::editEnable()
{ //turns the source on or off w/o deleting it
  int c = -1;
  do
  {
    cout << "Turn voltage source on/off (0 = off, 1 = on): ";
    cin >> c;
    if(c == 1 || c == 0)
    {
      enable = c;  
    }
    else
    {
      cout << "Invalid input! 0 or 1 only." << endl; 
    }
  } while (c > 1 || c < 0);
}

void Wave::inputData()
{ //creates new voltage wave by calling all edit functions in one go
  editType();
  editAmp();
  editFreq();
  editPhase();
  editDCOff();
  enable = true;
}

void Wave::printData() //prints waveform parameters
{
  if(enable == true)
  {
    cout << "Status: ON" << endl; 
  }
  else if(enable == false)
  {
    cout << "Status: OFF" << endl; 
  } 
  cout<< "Type: "<< type<< endl;
  cout<< "Amplitude: " << amp<< endl;
  cout<< "Frequency: " << freq<< endl;
  cout<< "Phase: "<< phase<< endl;
  cout<< "DC Offset: "<< offset<< endl;
}
