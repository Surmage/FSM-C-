#pragma once
#include "state.h"

struct Sleep : State
{
    virtual void Execute(Agent* agent)
    {
        //Change stat variables
        agent->busy = true;
        agent->changeHunger(-0.01f * speed);
        agent->changeThirst(-0.02f * speed);
        agent->busy = false;
        agent->changeEnergy(-energyChangeVal * 2 * speed);
    }
    virtual void Enter(Agent* agent)
    {
        //Debug.Log(name + " entering Idle state");
        setStartValues("sleeping");

    }

    virtual void Exit(Agent* agent)
    {
        //Debug.Log(name + " exiting Gather state");

    }
};
