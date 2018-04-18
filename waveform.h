#ifndef WAVEFORM_H
#define WAVEFORM_H

#include <iostream>
#include <string>

using namespace std;

class Wave 
{
  public:
    string type;
    double amp, freq, phase, offset;
    
    void editType();
    void editAmp();
    void editFreq();
    void editPhase();
    void editDCOff();
    void inputData();
    void printData();
};


#endif
