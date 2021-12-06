//
// Created by Suneeth Vejendla on 1December 2021 .
//


#ifndef SATPROJECT_CTLFORMULA_H
#define SATPROJECT_CTLFORMULA_H

#include "KripkeStructure.h"
#include "State.h"
#include "Transition.h"

#include <string>
#include <list>
#include <map>
#include <algorithm>

using namespace std;

enum TypeSAT
{
    UnKnown,
    AllTrue,
    AllFalse,
    Atomic,
    Not,
    And,
    Or,
    Implies,    //SAT (¬φ1 ∨ φ2)
    AX,         //SAT (¬EX¬φ1)
    EX,         //SAT_EX
    AU,         //A[φ1 U φ2] = SAT(¬(E[¬φ2 U (¬φ1 ∧¬φ2)] ∨ EG¬φ2))
    EU,         //SAT_EU
    EF,         //SAT (E( U φ1))
    EG,         //SAT(¬AF¬φ1)
    AF,         //SAT_AF
    AG          //SAT (¬EF¬φ1)
};

class CtlFormula
{
public:
    KripkeStructure _kripke;
    State _state;
    string _expression;
    // modify
    map<string, string> _convertionString;

    //constrctor
    CtlFormula(string expression, State state, KripkeStructure& kripke);
    void ConvertAsSysForm(string& expression);
    bool IsValid();

private:
    TypeSAT GetTypeSAT(string expression, string& leftExpression, string& rightExpression);
    // Determine states that satisfy given expression
    list<State> SAT(string expression);
    //Handling EX
    list<State> SAT_EX(string expression);

    // Handling EU
    list<State> SAT_EU(string leftExpression, string rightExpression);
    // Handling AF
    list<State> SAT_AF(string expression);
    // PreE
    list<State> PreE(list<State>& y);

    // PreA
    list<State> PreA(list<State>& y);

    // Determine whether the list contain same set of states
    bool arelistStatesSame(list<State>& list1, list<State>& list2);

    // Determine whether this is an atom
    bool isAtomic(string expression);

    // Determine whether given expression contains binary operation for the next checking
    bool isBinaryOp(string expression, string sym, string& leftExpression, string& rightExpression);

    // Removing extra brackets
    string removeExtraBrackets(string expression);

    //add function to check contain situation in a list for state
    bool checkListContainState(list<State>& dest, State src);

    //add remove an element function to list<State>
    void removeFromList(list<State>& dest, State src);

    //add function to check contain situation in a list for Transition
    bool checkListContainTransition(list<Transition>& dest, Transition src);

    //add function to check contain situation in a list for string
    bool checkListContainString(list<string>& dest, string src);

	// remove all space in expression
	void removeAllSpace(string& expression);
};

#endif //SATPROJECT_CTLFORMULA_H
