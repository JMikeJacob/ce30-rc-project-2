#include "waveform.h"

void Wave::editType()
{
  bool invalid = true;
  cout << "Choose waveform type:\n"; 
  cout << "- sinusoid\n- square\n- triangular\n";
  do
  {
    cout << "Choice: ";
    cin >> type;
    cin.clear();
    //if(type[0] >= 'A' && type[0] <= 'Z')
    //{
      //type[0] -= 'a'; 
    //}
    if(type=="sinusoidal" || type=="square" || type=="triangular")
    {
      invalid = false;
    }
    else
    {
      cout << " Invalid input!" << endl;
    }
  } while(invalid);
}

void Wave::editAmp()
{
  cout << "Input amplitude: ";
  cin >> amp;
  cin.clear();
}

void Wave::editFreq()
{
  cout << "Input frequency: ";
  cin >> freq;
  cin.clear();
}

void Wave::editPhase()
{
  cout << "Input phase: ";
  cin >> phase;
  cin.clear();
}

void Wave::editDCOff()
{
  cout<< "Input DC offset: ";
  cin>> offset;
  cin.clear();
}

void Wave::inputData()
{
  editType();
  editAmp();
  editFreq();
  editPhase();
  editDCOff();
}

void Wave::printData()
{
  cout<< "Type: "<< type<< endl;
  cout<< "Amplitude: " << amp<< endl;
  cout<< "Frequency: " << freq<< endl;
  cout<< "Phase: "<< phase<< endl;
  cout<< "DC Offset: "<< offset<< endl;
  return;
}
