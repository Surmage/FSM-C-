#pragma once
#include "state.h"

struct Eat : State
{
    virtual void Execute(Agent* agent)
    {
        //Change stat variables
        agent->changeEnergy(energyChangeVal * speed);
        agent->changeHunger(0.5f * speed);
        agent->busy = true;
        agent->changeThirst(1 * speed);
        agent->changeHappiness(0.1f * speed);
        agent->busy = false;
    }
    virtual void Enter(Agent* agent)
    {
        //Debug.Log(name + " entering Idle state");
        setStartValues("eating");
        //"busy" being true prevents state from changing
        agent->busy = true;
        //Pay for food
        agent->changeMoney(-500);
        agent->busy = false;
    }

    virtual string Exit(Agent* agent)
    {
        //Debug.Log(name + " exiting Gather state");
        return dateWith;

    }
};
