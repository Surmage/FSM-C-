#pragma once
#include "state.h"

struct Idle : State
{
    virtual void Execute(Agent* agent)
    {
        //Change stat variables
        agent->changeEnergy(energyChangeVal * speed);
        agent->changeHunger(-0.3f * speed);
        agent->changeThirst(-1.0f * speed);
        agent->changeHappiness(-0.1f * speed);
    }
    virtual void Enter(Agent* agent)
    {
        //Debug.Log(name + " entering Idle state");
        //setStartValues("idling around");

    }

    virtual void Exit(Agent* agent)
    {
        //Debug.Log(name + " exiting Gather state");

    }
};
