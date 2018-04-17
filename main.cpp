#include <iostream>
#include <array>
#include <cstdlib>
#include <string>

using namespace std;

class InputVoltage{
public:
    string type;
    double amp, freq, phase, offset;
    int counts=0;
    bool invalidvoltChecker=false;

    double inputData()
    {
        cout<< "\n|INPUT VOLTAGE|"<< endl;
        do{
            cout<< "Input waveform type (Choices are sinusoidal, square, or triangular): ";
            cin>> type;
            cin.clear();
            if((type == "sinusoidal") || (type == "square") || (type == "triangular") || (type == "Sinusoidal") || (type == "Square") || (type == "Triangular"))
            {
                invalidvoltChecker=false;
            }
            else
            {
                cout<< "Invalid input!"<< endl;
                invalidvoltChecker=true;
            }
        }while(invalidvoltChecker==true);
        cout<< "Input amplitude: ";
        cin>> amp;
        cin.clear();
        cout<< "Input frequency: ";
        cin>> freq;
        cin.clear();
        cout<< "Input phase: ";
        cin>> phase;
        cin.clear();
        cout<< "Input DC offset: ";
        cin>> offset;
        cin.clear();
    }
    double editType()
    {
         do{
            cout<< "Input waveform type (Choices are sinusoidal, square, or triangular): ";
            cin>> type;
            cin.clear();
            if((type == "sinusoidal") || (type == "square") || (type == "triangular") || (type == "Sinusoidal") || (type == "Square") || (type == "Triangular"))
            {
                invalidvoltChecker=false;
            }
            else
            {
                cout<< "Invalid input!";
                invalidvoltChecker=true;
            }
        }while(invalidvoltChecker==true);
    }
    double editAmp()
    {
        cout<< "Input amplitude: ";
        cin>> amp;
        cin.clear();
    }
    double editFreq()
    {
        cout<< "Input frequency: ";
        cin>> freq;
        cin.clear();
    }
    double editPhase()
    {
        cout<< "Input phase: ";
        cin>> phase;
        cin.clear();
    }
    double editDCOff()
    {
        cout<< "Input DC offset: ";
        cin>> offset;
        cin.clear();
    }
    void printData()
    {
        cout<< "Type: "<< type<< endl;
        cout<< "Amplitude: " << amp<< endl;
        cout<< "Frequency: " << freq<< endl;
        cout<< "Phase: "<< phase<< endl;
        cout<< "DC Offset: "<< offset<< endl;
        return;
    }

};

class RCSimulation{
public:
    double resistance, capacitance;
    double inputRC()
    {
        cout<<"Input Resistor value (in Ohms): ";
        cin>> resistance;
        cin.clear();
        cout<<"Input Capacitor value (in Farads): ";
        cin>> capacitance;
        cin.clear();
    }
    double editR()
    {
        cout<<"Input Resistor value (in Ohms): ";
        cin>> resistance;
        cin.clear();
    }
    double editC()
    {
        cout<<"Input Capacitor value (in Farads): ";
        cin>> capacitance;
        cin.clear();
    }
    void printRC()
    {
        cout<< "Resistance (in Ohms): " << resistance<<endl;
        cout<< "Capacitance (in Farads): " << capacitance << endl;
    }



};
int main()
{
    int counts=0, sizer=20, waveformCount=0;
    bool addBool, editBool, whichEdit, whichWave;
    string addWave, editData, editChoice, voltEdit;
    InputVoltage wave[sizer];
    RCSimulation rcValue;
    rcValue.inputRC();
    wave[0].inputData();
    system("CLS");
    cout<< "Here are your data inputs!"<< endl;
    rcValue.printRC();
    cout<< "\n|INPUT VOLTAGE|"<< endl;
    wave[0].printData();
    do
    {
        cout<< "\nDo you want to add another waveform?"<<endl << "a. Yes" << "\nb. No" <<endl;
        cout<<"Answer: ";
        cin>>addWave;
        cin.clear();
        if(addWave=="no" || addWave=="No" || addWave=="b" || addWave=="B" || addWave=="b." || addWave=="B.")
        {
            system("CLS");
            cout<< "Thank you! Here is your final input\n"<< endl;
            rcValue.printRC();
            for(int i=0; i<=counts; i++)
            {
                cout<< endl;
                cout<< "Input waveform "<< i+1 << ": "<<endl;
                wave[i].printData();
            }
            addBool=false;
        }
        else if(addWave=="yes" || addWave=="Yes" || addWave=="a" || addWave=="A" || addWave=="a." || addWave=="A.")
        {
            counts++;
            wave[counts].inputData();
            system("CLS");
            cout<< "Here are your data inputs!\n"<< endl;
            rcValue.printRC();
            for(int i=0; i<=counts; i++)
            {
                cout<< endl;
                cout<< "Input waveform "<< i+1 << ": "<<endl;
                wave[i].printData();
            }
            addBool=true;
        }
        else
        {
            cout<<"Invalid input! Choose between yes and no only"<<endl;
            system("PAUSE");
            system("CLS");
        }
    }while(addBool==true);

    do
    {
        cout<< "\nDo you want to edit your data?"<<endl << "a. Yes" << "\nb. No" <<endl;
        cout<<"Answer: ";
        cin>>editData;
        cin.clear();
        if(editData=="no" || editData=="No" || editData=="b" || editData=="B" || editData=="b." || editData=="B.")
        {
            editBool=false;
            cout<< "\nThank you for using this program!"<< endl;
            return 0;
        }
        if(editData=="yes" || editData=="Yes" || editData=="a" || editData=="A" || editData=="A." || editData=="a.")
        {
           editBool=true;
           do{
            cout<<"\nWhich part would you like to edit?"<<endl<<"a. Voltage\nb. Resistance\nc. Capacitance\nd. None"<< endl;
            cout<<"Answer: ";
            cin>> editChoice;
            cin.clear();
            if (editChoice=="Voltage" || editChoice=="voltage" || editChoice=="a" || editChoice=="A")
            {
                whichEdit==true;
                do{
                    cout<<"\nWhich waveform?" <<endl<<"Choices: " <<endl;
                    for(int k=0; k<=counts; k++)
                    {
                        cout<< "- Input waveform "<< k+1<< endl;
                    }
                    cout<<"Answer: ";
                    cin>> waveformCount;
                    cin.clear();
                    if(waveformCount<= counts+1)
                    {
                        whichWave=true;
                    }
                    else
                    {
                        cout<< "Invalid input!"<< endl;
                        whichWave=false;
                    }
                }while(whichWave==false);
                cout<<"\nWhich parameter/s?" <<endl<< "Choices: " <<endl;
                cout<<"A. Type"<<endl;
                cout<<"B. Amplitude"<<endl;
                cout<<"C. Frequency"<<endl;
                cout<<"D. Phase"<<endl;
                cout<<"E. DC Offset" << endl;
                do{
                    cout<< "Answer (input 0 if done): ";
                    cin>> voltEdit;
                    cin.clear();
                        if(voltEdit=="A" || voltEdit=="a")
                        {
                            wave[waveformCount-1].editType();
                        }
                        else if(voltEdit=="B" || voltEdit=="b")
                        {
                            wave[waveformCount-1].editAmp();
                        }
                        else if(voltEdit=="C" || voltEdit=="c")
                        {
                            wave[waveformCount-1].editFreq();
                        }
                        else if(voltEdit=="D" || voltEdit=="d")
                        {
                            wave[waveformCount-1].editPhase();
                        }
                        else if (voltEdit=="E" || voltEdit=="e")
                        {
                            wave[waveformCount-1].editDCOff();
                        }
                        else if(voltEdit=="0")
                        {

                        }
                        else
                        {
                            cout<<"Invalid input! Input letters A, B, C, D, or E only"<<endl;
                        }
                }while(voltEdit!="0");

                system("CLS");
                cout<< "Thank you! Here is your final input\n"<< endl;
                rcValue.printRC();
                for(int i=0; i<=counts; i++)
                {
                    cout<< endl;
                    cout<< "Input waveform "<< i+1 << ": "<<endl;
                    wave[i].printData();
                }
            }
            else if (editChoice=="Resistance" || editChoice=="resistance" || editChoice=="b" || editChoice=="B")
            {
                whichEdit==true;
                rcValue.editR();
                system("CLS");
                cout<< "Thank you! Here is your final input\n"<< endl;
                rcValue.printRC();
                for(int i=0; i<=counts; i++)
                {
                    cout<< endl;
                    cout<< "Input waveform "<< i+1 << ": "<<endl;
                    wave[i].printData();
                }
            }
            else if (editChoice=="Capacitance" || editChoice=="capacitance" || editChoice=="c" || editChoice=="C")
            {
                whichEdit==true;
                rcValue.editC();
                system("CLS");
                cout<< "Thank you! Here is your final input\n"<< endl;
                rcValue.printRC();
                for(int i=0; i<=counts; i++)
                {
                    cout<< endl;
                    cout<< "Input waveform "<< i+1 << ": "<<endl;
                    wave[i].printData();
                }
            }
            else if(editChoice=="None" || editChoice=="none" || editChoice=="d" || editChoice=="D")
            {
                whichEdit=true;
                system("CLS");
                cout<< "Thank you! Here is your final input\n"<< endl;
                rcValue.printRC();
                for(int i=0; i<=counts; i++)
                {
                    cout<< endl;
                    cout<< "Input waveform "<< i+1 << ": "<<endl;
                    wave[i].printData();
                }
            }
            else
            {
                whichEdit=false;
                cout<<"\nInvalid input!"<<endl;
            }
           }while(whichEdit==false);
        }
        else
        {
            whichEdit=true;
            cout<<"\nInvalid input!"<<endl;
        }

    }while(editBool==true);
    return 0;
}
