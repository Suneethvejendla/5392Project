//
// Created by Suneeth Vejendla on 1December 2021 .
//

#ifndef SATPROJECT_KRIPKESTRUCTURE_H
#define SATPROJECT_KRIPKESTRUCTURE_H

#include "State.h"
#include "Transition.h"

#include <list>
#include <string>
#include <algorithm>
#include <iostream>

using namespace std;

class KripkeStructure
{
public:
    list<Transition> Transitions; // not add getter and setter
    list<State> States;           // not add getter and setter
    list<string> Atoms;           // not add getter and setter

    KripkeStructure()
    {
        Transitions = list<Transition>();
        States = list<State>();
        Atoms = list<string>();
    }

    KripkeStructure(string kripkeStructureDefinition);// : KripkeStructure();

    list<State>::iterator FindStateByName(const string stateName);

    string ToString();
    string StatesToString();
    string TransitionsToString();

    //add a replace function for handle string
    void replaceByEmpty(string& src, string before);

    //add a split function for handle string
    void splitToList(const string& src, const string& separator, list<string>& dest);

    string ltrim(const string& s);
    string rtrim(const string& s);
    string trim(const string& s);

    //add function to check contain situation in a list for string
    bool checkListContainString(list<string>& dest, string src);

    //add function to check contain situation in a list for Transition
    bool checkListContainTransition(list<Transition>& dest, Transition src);

    //add function to check contain situation in a list for state
    bool checkListContainState(list<State>& dest, State src);
};

#endif //SATPROJECT_KRIPKESTRUCTURE_H
