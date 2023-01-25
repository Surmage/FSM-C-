#pragma once
#include "state.h"

struct Mining : State
{
    virtual void Execute(Agent* agent)
    {
        //Change stat variables
        agent->changeEnergy(energyChangeVal * speed);
        agent->changeHunger(-0.2f * speed);
        agent->changeThirst(-0.5f * speed);
        agent->changeMoney(0.3f * speed);
        agent->changeHappiness(-0.2f * speed);
    }
    virtual void Enter(Agent* agent)
    {
        //Debug.Log(name + " entering Idle state");
        setStartValues("mining");
        if (agent->needRepair)
        {
            //Debug.Log(name + " Payed 1500 for new pickaxe before " + agentBehavior.money);
            //"busy" being true prevents state from changing
            agent->busy = true;
            agent->needRepair = false;
            agent->changeMoney(-1500);
            agent->busy = false;
            //Debug.Log(name + " Payed 1500 for new pickaxe after " + agentBehavior.money);
        }
    }

    virtual void Exit(Agent* agent)
    {
        //Debug.Log(name + " exiting Gather state");

    }
};
