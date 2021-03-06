// 
//Created by Vandana on 5 December 2021 .
//

#include "CtlFormula.h"
#include "KripkeStructure.h"
#include "State.h"
#include "Transition.h"

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

//Need to update
string GetMessage(bool IsValid, string expression, string stateID)
{
    string message;
	message = "Property " + expression + " " + (IsValid ? "holds " : "does not hold ") + "in state " + stateID;
    return message;
}

int main()
{
    //get model file
    cout << "Enter file name (kripke model): " << endl;
    ifstream _kripke_file;
    string input_kripke_file_name, input_kripke_model;
    cin >> input_kripke_file_name;
    string kripke_content;
    _kripke_file.open(input_kripke_file_name);

	if (_kripke_file.is_open())
    {
        while (!_kripke_file.eof())
        {
            _kripke_file >> kripke_content;
            input_kripke_model += kripke_content;
        }
    }
    else
    {
        cout << "File can't open ";
		return 0;
    }
    _kripke_file.close();

    //get state
    string input_state;
    cout << "Enter state: " << endl;
    cin >> input_state;

    //get CTL formular
    string input_ctl_formula;
    cout << "Enter CTL formula: " << endl;
    // cin >> input_ctl_formula;
	cin.ignore();
	getline(cin, input_ctl_formula);

    //for testing part
    cout << "\nFile (Kripke model): " << input_kripke_model << endl;
    cout << "State: " << input_state << endl;
    cout << "CTL formula: " << input_ctl_formula << endl;

    //parse input kripke model to Objest KripkeStructure
	KripkeStructure _kripke(input_kripke_model);

	// if the given state is not in structure
	if (std::find(_kripke.States.begin(), _kripke.States.end(), input_state) == _kripke.States.end())
	{
		std::cout << "the given state is not in structure ! " << std::endl;
		return 0;
	}

    string kripke_model = _kripke.ToString();

    State checkedState = State(input_state);
    CtlFormula ctlFormula = CtlFormula(input_ctl_formula, checkedState, _kripke);
    bool IsValid = ctlFormula.IsValid();
    string message = GetMessage(IsValid, input_ctl_formula, input_state);
    cout << "Result is: " << message << endl;

    return 0;
}

