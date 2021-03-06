//
// Created by Sai Sandeep on 4 December 2021 .
//

#ifndef SATPROJECT_TRANSITION_H
#define SATPROJECT_TRANSITION_H

//#include "CtlFormula.h"
//#include "KripkeStructure.h"
#include "State.h"

#include <string>

using namespace std;

class Transition
{
public:
    string TransitionName;
    State FromState;
    State ToState;

    Transition() {}

    Transition(State fromState, State toState)
    {
        TransitionName = "";
        FromState = fromState;
        ToState = toState;
    }

    Transition(string transitionName, State fromState, State toState)
    {
        TransitionName = transitionName;
        FromState = fromState;
        ToState = toState;
    }

    bool Equals(const Transition& other) const
    {
        if (FromState.Equals(other.FromState) && ToState.Equals(other.ToState))
            return true;

        return false;
    }

	friend bool operator==(const Transition& lhs, const Transition& rhs)
	{
		return lhs.Equals(rhs);
	}
};

#endif //SATPROJECT_TRANSITION_H
