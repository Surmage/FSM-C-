#pragma once
#include "state.h"

struct Drink : State
{
    virtual void Execute(Agent* agent)
    {
        //Change stat variables
        agent->changeEnergy(energyChangeVal * speed);
        agent->changeThirst(3 * speed);
    }
    virtual void Enter(Agent* agent)
    {
        //Debug.Log(name + " entering Idle state");
        setStartValues("drinking");
    }

    virtual void Exit(Agent* agent)
    {
        //Debug.Log(name + " exiting Gather state");

    }
};
