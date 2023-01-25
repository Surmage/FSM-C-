#pragma once
#include "state.h"

struct Gather : State
{
    virtual void Execute(Agent* agent)
    {
        //Change stat variables
        agent->changeEnergy(energyChangeVal * speed);
        agent->changeHunger(-0.2f * speed);
        agent->changeThirst(-0.5f * speed);
        agent->changeMoney(0.1f * speed);
        agent->changeHappiness(-0.05f * speed);
    }
    virtual void Enter(Agent* agent)
    {
        //Debug.Log(name + " entering Idle state");
        setStartValues("gathering");

    }

    virtual string Exit(Agent* agent)
    {
        //Debug.Log(name + " exiting Gather state");
        return dateWith;

    }
};
