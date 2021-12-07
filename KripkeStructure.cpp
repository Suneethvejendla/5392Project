//
// Created by Ganesh Tummala on 1December 2021 .
//

#include "KripkeStructure.h"


KripkeStructure::KripkeStructure(string kripkeStructureDefinition) : KripkeStructure()
{
    list<string> parsedStructure;
    replaceByEmpty(kripkeStructureDefinition, "\r\n");
    splitToList(kripkeStructureDefinition, ";", parsedStructure);

	if (parsedStructure.size() == 0 || parsedStructure.size() != 4)
	{
		cout << "\nInput file does not contain valid segments to form a kripke structure.\n";
		exit(0);
	}

    list<string> stateNames;
    string src_0 = parsedStructure.front();
    replaceByEmpty(src_0, "\r\n");
    splitToList(src_0, ",", stateNames);
    parsedStructure.pop_front();

    list<string> transitions;
    string src_1 = parsedStructure.front();
    replaceByEmpty(src_1, "\r\n");
    splitToList(src_1, ",", transitions);
    parsedStructure.pop_front();

    list<string> stateAtomStructures;
    string src_2 = parsedStructure.front();
    splitToList(src_2, ",", stateAtomStructures);

    for (auto iter_state_names = stateNames.begin(); iter_state_names != stateNames.end(); iter_state_names++)
    {
        State state = State(*iter_state_names);
        if (!checkListContainState(States, state))
        {
            States.push_back(State(*iter_state_names));
        }
		else
		{
			cout << "\nState " << *iter_state_names << "is defined more than once.";
			exit(0);
		}
    }

    //load transitions
    for (string transition : transitions)
    {
        //            list<string> parsedTransition = transition.Split(new char[]{':'}).ToList();
        list<string> parsedTransition;
        splitToList(transition, ":", parsedTransition);

		if (parsedTransition.size() == 0 || parsedTransition.size() != 2)
		{
			cout << "\nTransition is not in the valid format";
			exit(0);
		}

        string transitionName = parsedTransition.front();
        parsedTransition.pop_front();
        list<string> parsedFromToStates;
        string parsedTransition_1 = parsedTransition.front();
        splitToList(parsedTransition_1, "-", parsedFromToStates);

		if (parsedFromToStates.size() == 0 || parsedFromToStates.size() != 2)
		{
			cout << "\nTransition " << transitionName << " is not in[from state] - [to state] format ";
			exit(0);
		}
			

        string fromStateName = parsedFromToStates.front();
        parsedFromToStates.pop_front();
        string toStateName = parsedFromToStates.front();

		list<State>::iterator iter_fromState, iter_toState;
        iter_fromState = FindStateByName(fromStateName);
		iter_toState = FindStateByName(toStateName);

		if (iter_fromState == States.end() || iter_toState == States.end())
		{
			cout << "\nInvalid state is detected in transition " << transitionName;
			exit(0);
		}
			
		
// 		State fromState = *iter_fromState;
// 		State toState = *iter_toState;

        Transition transitionObj = Transition(transitionName, *iter_fromState, *iter_toState);

        if (!checkListContainTransition(Transitions, transitionObj))
            Transitions.push_back(transitionObj);
        else
        {
            cout << "\nTransitions from state " << fromStateName << " to state " << toStateName << " are defined more than once";
			exit(0);
        }
    }

    //load atoms
    for (string stateAtomStructure : stateAtomStructures)
    {
        list<string> parsedStateAtomStructure;
        splitToList(stateAtomStructure, ":", parsedStateAtomStructure);

		if (parsedStateAtomStructure.size() == 0 || parsedStateAtomStructure.size() != 2)
		{
			cout << "\n" << stateAtomStructure << " is not a valid state: atoms definition";
			exit(0);
		}
            

        string stateName;
        string parsedStateAtomStructure_0 = parsedStateAtomStructure.front();
        replaceByEmpty(parsedStateAtomStructure_0, " ");
        stateName = parsedStateAtomStructure_0;
        parsedStateAtomStructure.pop_front();

        string atomNames;
        string parsedStateAtomStructure_1 = parsedStateAtomStructure.front();
        atomNames = trim(parsedStateAtomStructure_1);

        list<string> parsedAtoms;

        for (char atom : atomNames)
            parsedAtoms.push_back(string(1, atom));

        list<string> stateAtoms = list<string>();
        for (string atom : parsedAtoms)
        {
            if (atom == "")
            {
            }
            else if (!checkListContainString(stateAtoms, atom))
                stateAtoms.push_back(atom);
			else
			{
				cout << "\nAtom " << atom << " is defined more than once for state " << stateName;
				exit(0);
			}
				
        }


		list<State>::iterator iter_stateObj = FindStateByName(stateName);

		if (iter_stateObj == States.end())
		{
			cout << "\n" << "State " << stateName << " is not defined";
			exit(0);
		}	
		iter_stateObj->Atom = stateAtoms;

        for (string atom : stateAtoms)
        {
            if (!checkListContainString(Atoms, atom))
                Atoms.push_back(atom);
        }
    }
}

list<State>::iterator KripkeStructure::FindStateByName(const string stateName)
{
    for (auto it = States.begin(); it != States.end(); it++)
    {
		if (it->StateName == stateName)
			return it;
    }
	return States.end();
}

string KripkeStructure::ToString()
{
    string sb;

    sb.append("STATES\r\n");
    sb.append("-----------\r\n");
    sb.append(StatesToString());
    sb.append("\r\n");
    sb.append("\r\n");
    sb.append("\r\n");
    sb.append("TRANSITIONS\r\n");
    sb.append("-------------------\r\n");
    sb.append(TransitionsToString());
    sb.append("\r\n");

    return sb;
}

string KripkeStructure::StatesToString()
{
    string sb = ""; // = new StringBuilder();

    for (State state : States)
    {
        string atomNames;
        for (auto iter_atoms = state.Atom.begin(); iter_atoms != state.Atom.end(); iter_atoms++)
        {
            atomNames.append(*iter_atoms);
        }
        sb += (state.StateName + "(" + atomNames + ")");
    }

    return sb;
}

string KripkeStructure::TransitionsToString()
{
    string sb="";

    for (Transition transition : Transitions)
    {
        sb += (transition.TransitionName + "(" + transition.FromState.StateName + " -> " + transition.ToState.StateName + ")");
    }

    return sb;
}

void KripkeStructure::replaceByEmpty(string& src, string before)
{
    while (src.find(before) != string::npos)
    {
        src.erase(src.find(before), 2);
    }
}

void KripkeStructure::splitToList(const string& src, const string& separator, list<string>& dest)
{
    string str = src;
    string substring;
    string::size_type start = 0, index;
    dest.clear();
    index = str.find_first_of(separator, start);
    do
    {
        if (index != string::npos)
        {
            substring = str.substr(start, index - start);
            dest.push_back(substring);
            start = index + separator.size();
            index = str.find(separator, start);
            if (start == string::npos)
                break;
        }
    } while (index != string::npos);

    //the last part
    substring = str.substr(start);
    dest.push_back(substring);
}

//add trim functions for trim string
string KripkeStructure::ltrim(const string& s)
{
    size_t start = s.find_first_not_of(" \n\r\t\f\v");
    return (start == string::npos) ? "" : s.substr(start);
}

string KripkeStructure::rtrim(const string& s)
{
    size_t end = s.find_last_not_of(" \n\r\t\f\v");
    return (end == string::npos) ? "" : s.substr(0, end + 1);
}

string KripkeStructure::trim(const string& s)
{
    return rtrim(ltrim(s));
}

bool KripkeStructure::checkListContainString(list<string>& dest, string src)
{
	return std::find(dest.begin(), dest.end(), src) != dest.end() ? true : false;
}

bool KripkeStructure::checkListContainTransition(list<Transition>& dest, Transition src)
{
	return std::find(dest.begin(), dest.end(), src) != dest.end() ? true : false;
}

bool KripkeStructure::checkListContainState(list<State>& dest, State src)
{
	return std::find(dest.begin(), dest.end(), src) != dest.end() ? true : false;
}
