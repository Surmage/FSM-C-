#pragma once
#include "state.h"
struct Social : State
{
    virtual void Execute(Agent* agent)
    {
        //Change stat variables
        agent->changeEnergy(energyChangeVal * speed);
        agent->changeHappiness(0.5f * speed);
        agent->busy = true;
        agent->changeHunger(0.5f * speed);
        agent->changeThirst(0.5f * speed);
        agent->busy = false;
    }
    virtual void Enter(Agent* agent)
    {
        //Debug.Log(name + " entering Social state");
        //"busy" being true prevents state from changing
        agent->busy = true;
        agent->changeMoney(-1000);
        agent->changeHappiness(1000);
        agent->busy = false;
        setStartValues("socializing");
    }

    virtual string Exit(Agent* agent)
    {
        //Debug.Log(name + " exiting Social state");
        return dateWith;
    }
};