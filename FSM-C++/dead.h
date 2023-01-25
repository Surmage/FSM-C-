#pragma once
#pragma once
#include "state.h"

struct Dead : State
{
    virtual void Execute(Agent* agent)
    {

    }
    virtual void Enter(Agent* agent)
    {
        //Debug.Log(name + " entering Idle state");
        setStartValues("dead");

    }

    virtual string Exit(Agent* agent)
    {
        //Debug.Log(name + " exiting Gather state");
        return "";

    }
};
