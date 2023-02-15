#pragma once
#include "States.h"
#include "Agent.h"

void Drink::Execute(Agent* agent)
{
    //Change stat variables
    agent->changeEnergy(energyChangeVal, true);
    agent->changeThirst(3 * 8 * 6, true);
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
    agent->changeEnergy(energyChangeVal, true);
    agent->changeHunger(3 * 8 * 2, true);
    agent->busy = true;
    agent->changeThirst(3 * 8 * 3, true);
    agent->changeHappiness(3.0f / 3, true);
    agent->busy = false;
}
void Eat::Enter(Agent* agent)
{
    //Debug.Log(name + " entering Idle state");
    setStartValues("eating");
    //"busy" being true prevents state from changing
    agent->busy = true;
    //Pay for food
    agent->changeMoney(-500, false);
    agent->busy = false;
    agent->timesEaten++;
}

void Eat::Exit(Agent* agent)
{
    //Debug.Log(name + " exiting Gather state");

}

void Gather::Execute(Agent* agent)
{
    //Change stat variables
    agent->changeEnergy(energyChangeVal, true);
    agent->changeHunger(-3.0f * 1.5, true);
    agent->changeThirst(-3.0f * 2, true);
    agent->changeMoney(3.0f / 8, true);
    agent->changeHappiness(-3.0f / 2, true);
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
    agent->changeEnergy(energyChangeVal, true);
    agent->changeHunger(-3.0f * 1.5f, true);
    agent->changeThirst(-3.0f * 2, true);
    agent->changeHappiness(-3.0f / 2, true);
}
void Idle::Enter(Agent* agent)
{
    //Debug.Log(name + " entering Idle state");
    setStartValues("idling around");

}

void Idle::Exit(Agent* agent)
{
    //Debug.Log(name + " exiting Gather state");

}

void Mining::Execute(Agent* agent)
{
    //Change stat variables
    agent->changeEnergy(energyChangeVal, true);
    agent->changeHunger(-3.0f * 1.5, true);
    agent->changeThirst(-3.0f * 2, true);
    agent->changeMoney(3.0f, true);
    agent->changeHappiness(-3.0f, true);
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
        agent->changeMoney(-1500, false);
        agent->busy = false;
        //Debug.Log(name + " Payed 1500 for new pickaxe after " + agentBehavior.money);
    }
}

void Mining::Exit(Agent* agent)
{
    //Chance for pickaxe to need repairing
    srand(time(NULL));
    int pickaxeBreakChance = rand() % 21;
    if (pickaxeBreakChance == 0)
    {
        agent->needRepair = true;
        //Pay for repair if possible
        if (agent->money >= 3000)
        {
            agent->busy = true;
            agent->changeMoney(-1500.0f, false);
            agent->needRepair = false;
            agent->busy = false;
        }
    }

}

void Social::Execute(Agent* agent)
{
    //Change stat variables
    agent->changeHappiness(3.0f * 8 / 2, true);
    agent->busy = true;
    agent->changeEnergy(energyChangeVal, true);
    agent->changeHunger(3.0f * 8 / 2, true);
    agent->changeThirst(3.0f * 8, true);
    agent->busy = false;
}
void Social::Enter(Agent* agent)
{
    //Debug.Log(name + " entering Social state");
    //"busy" being true prevents state from changing
    agent->busy = true;
    agent->changeMoney(-1000, false);
    agent->changeHappiness(1000, false);
    agent->busy = false;
    setStartValues("socializing");
}

void Social::Exit(Agent* agent)
{
    //Debug.Log(name + " exiting Social state");
    agent->date = std::make_tuple(NULL, agent);
}

void Sleep::Execute(Agent* agent)
{
    //Change stat variables
    agent->busy = true;
    agent->changeHunger(-3.0f / 3, true);
    agent->changeThirst(-3.0f / 3, true);
    agent->busy = false;
    agent->changeEnergy(-energyChangeVal * 2, true);
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

void Dead::Execute(Agent* agent)
{

}
void Dead::Enter(Agent* agent)
{
    //Debug.Log(name + " entering Idle state");
    setStartValues("dead");

}

void Dead::Exit(Agent* agent)
{
    //Debug.Log(name + " exiting Gather state");

}