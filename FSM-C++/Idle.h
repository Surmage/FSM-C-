#pragma once
#include "state.h"

struct Idle : State
{
    virtual void Execute(string name)
    {
        //Change stat variables
        //speed = im.speed;
     /*   agent = GameObject.Find(name);
        var agentBehavior = agent.GetComponent<AgentBehavior>();
        agentBehavior.changeEnergy(energyChangeVal * speed);
        agentBehavior.changeHunger(-0.3f * speed);
        agentBehavior.changeThirst(-1f * speed);
        agentBehavior.changeHappiness(-0.1f * speed);*/
    }
    virtual void Enter(string name)
    {
        //Debug.Log(name + " entering Idle state");
        //setStartValues("idling around");

    }

    virtual string Exit(string name)
    {
        //Debug.Log(name + " exiting Gather state");
        return dateWith;

    }
};
