#pragma once
#include "States.h"
#include "Agent.h"

void Drink::Execute(Agent* agent)
{
    //Change stat variables
    agent->changeEnergy(energyChangeVal * speed);
    agent->changeThirst(3 * speed);
}
void Drink::Enter(Agent* agent)
{
    //Debug.Log(name + " entering Idle state");
    setStartValues("drinking");
}

void Drink::Exit(Agent* agent)
{
    //Debug.Log(name + " exiting Gather state");

}

void Eat::Execute(Agent* agent)
{
    //Change stat variables
    agent->changeEnergy(energyChangeVal * speed);
    agent->changeHunger(0.5f * speed);
    agent->busy = true;
    agent->changeThirst(1 * speed);
    agent->changeHappiness(0.1f * speed);
    agent->busy = false;
}
void Eat::Enter(Agent* agent)
{
    //Debug.Log(name + " entering Idle state");
    setStartValues("eating");
    //"busy" being true prevents state from changing
    agent->busy = true;
    //Pay for food
    agent->changeMoney(-500);
    agent->busy = false;
}

void Eat::Exit(Agent* agent)
{
    //Debug.Log(name + " exiting Gather state");

}

void Gather::Execute(Agent* agent)
{
    //Change stat variables
    agent->changeEnergy(energyChangeVal * speed);
    agent->changeHunger(-0.2f * speed);
    agent->changeThirst(-0.5f * speed);
    agent->changeMoney(0.1f * speed);
    agent->changeHappiness(-0.05f * speed);
}
void Gather::Enter(Agent* agent)
{
    //Debug.Log(name + " entering Idle state");
    setStartValues("gathering");

}

void Gather::Exit(Agent* agent)
{
    //Debug.Log(name + " exiting Gather state");

}

void Idle::Execute(Agent* agent)
{
    //Change stat variables
    agent->changeEnergy(energyChangeVal * speed);
    agent->changeHunger(-0.3f * speed);
    agent->changeThirst(-1.0f * speed);
    agent->changeHappiness(-0.1f * speed);
}
void Idle::Enter(Agent* agent)
{
    //Debug.Log(name + " entering Idle state");
    //setStartValues("idling around");

}

void Idle::Exit(Agent* agent)
{
    //Debug.Log(name + " exiting Gather state");

}

void Mining::Execute(Agent* agent)
{
    //Change stat variables
    agent->changeEnergy(energyChangeVal * speed);
    agent->changeHunger(-0.2f * speed);
    agent->changeThirst(-0.5f * speed);
    agent->changeMoney(0.3f * speed);
    agent->changeHappiness(-0.2f * speed);
}
void Mining::Enter(Agent* agent)
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

void Mining::Exit(Agent* agent)
{
    //Debug.Log(name + " exiting Gather state");

}

void Social::Execute(Agent* agent)
{
    //Change stat variables
    agent->changeEnergy(energyChangeVal * speed);
    agent->changeHappiness(0.5f * speed);
    agent->busy = true;
    agent->changeHunger(0.5f * speed);
    agent->changeThirst(0.5f * speed);
    agent->busy = false;
}
void Social::Enter(Agent* agent)
{
    //Debug.Log(name + " entering Social state");
    //"busy" being true prevents state from changing
    agent->busy = true;
    agent->changeMoney(-1000);
    agent->changeHappiness(1000);
    agent->busy = false;
    setStartValues("socializing");
}

void Social::Exit(Agent* agent)
{
    //Debug.Log(name + " exiting Social state");
}

void Sleep::Execute(Agent* agent)
{
    //Change stat variables
    agent->busy = true;
    agent->changeHunger(-0.01f * speed);
    agent->changeThirst(-0.02f * speed);
    agent->busy = false;
    agent->changeEnergy(-energyChangeVal * 2 * speed);
}
void Sleep::Enter(Agent* agent)
{
    //Debug.Log(name + " entering Idle state");
    setStartValues("sleeping");

}

void Sleep::Exit(Agent* agent)
{
    //Debug.Log(name + " exiting Gather state");

}