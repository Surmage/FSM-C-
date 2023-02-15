#pragma once
#include "States.h"
#include "Agent.h"

State::State() 
{
    type = "";
    //3 represents taking 16 hours for stat to fill (Increase by 8000)
    //Multiplying it decreases the time it would take, example: 3 * 2 would take 8 hours, 3 * 8 would take 2 hours
    //Dividing it increases the time it would take, example: 3 / 2 would take 16 hours
    energyChangeVal = -3.0f; 
    statChangeVal = 3.0f;
}

void State::setStartValues(std::string type)
{
    this->type = type;
    energyChangeVal = -3.0f;
    statChangeVal = 3.0f;
}
void Drink::Execute(Agent* agent)
{
    //Change stat variables
    agent->changeEnergy(energyChangeVal, true);
    agent->changeThirst(statChangeVal * 8 * 6, true);
}
void Drink::Enter(Agent* agent)
{
    setStartValues("drinking");
}

void Drink::Exit(Agent* agent)
{

}

void Eat::Execute(Agent* agent)
{
    //Change stat variables
    agent->changeEnergy(energyChangeVal, true);
    agent->changeHunger(statChangeVal * 8 * 2, true);
    agent->busy = true;
    agent->changeThirst(statChangeVal * 8 * 3, true);
    agent->changeHappiness(statChangeVal / 3, true);
    agent->busy = false;
}
void Eat::Enter(Agent* agent)
{
    setStartValues("eating");
    //Busy prevents function calls to change states
    agent->busy = true;
    //Pay for food
    agent->changeMoney(-500, false);
    agent->busy = false;
}

void Eat::Exit(Agent* agent)
{

}

void Gather::Execute(Agent* agent)
{
    //Change stat variables
    agent->changeEnergy(energyChangeVal, true);
    agent->changeHunger(-statChangeVal * 1.5f, true);
    agent->changeThirst(-statChangeVal * 2, true);
    agent->changeMoney(statChangeVal / 8, true);
    agent->changeHappiness(-statChangeVal / 2, true);
}
void Gather::Enter(Agent* agent)
{
    setStartValues("gathering");

}

void Gather::Exit(Agent* agent)
{

}

void Idle::Execute(Agent* agent)
{
    //Change stat variables
    agent->changeEnergy(energyChangeVal, true);
    agent->changeHunger(-statChangeVal * 1.5f, true);
    agent->changeThirst(-statChangeVal * 2, true);
    agent->changeHappiness(-statChangeVal / 2, true);
}
void Idle::Enter(Agent* agent)
{
    setStartValues("idling around");

}

void Idle::Exit(Agent* agent)
{

}

void Mining::Execute(Agent* agent)
{
    //Change stat variables
    agent->changeEnergy(energyChangeVal, true);
    agent->changeHunger(-statChangeVal * 1.5f, true);
    agent->changeThirst(-statChangeVal * 2, true);
    agent->changeMoney(statChangeVal, true);
    agent->changeHappiness(-statChangeVal, true);
}
void Mining::Enter(Agent* agent)
{
    setStartValues("mining");
    if (agent->needRepair)
    {
        //Busy prevents function calls to change states
        agent->busy = true;
        agent->needRepair = false;
        agent->changeMoney(-1500, false);
        agent->busy = false;
        agent->sendMessage(agent->name + " repaired their pickaxe.");
    }
}

void Mining::Exit(Agent* agent)
{
    //Chance for pickaxe to need repairing
    int pickaxeBreakChance = rand() % 21; //5% chance
    if (pickaxeBreakChance == 0)
    {
        agent->needRepair = true;
        agent->sendMessage(agent->name + "'s pickaxe broke.");
    }

}

void Social::Execute(Agent* agent)
{
    //Change stat variables
    agent->changeHappiness(statChangeVal * 8 / 2, true);
    //Busy prevents function calls to change states
    agent->busy = true;
    agent->changeEnergy(energyChangeVal, true);
    agent->changeHunger(statChangeVal * 8 / 2, true);
    agent->changeThirst(statChangeVal * 8, true);
    agent->busy = false;
}
void Social::Enter(Agent* agent)
{
    //Busy prevents function calls to change states
    agent->busy = true;
    agent->changeMoney(-1000, false);
    agent->changeHappiness(1000, false);
    agent->busy = false;
    setStartValues("socializing");
}

void Social::Exit(Agent* agent)
{  
    agent->date = std::make_tuple(NULL, agent);
}

void Sleep::Execute(Agent* agent)
{
    //Change stat variables
    //Busy prevents function calls to change states
    agent->busy = true;
    agent->changeHunger(-statChangeVal / 3, true);
    agent->changeThirst(-statChangeVal / 3, true);
    agent->busy = false;
    agent->changeEnergy(-energyChangeVal * 2, true);
}
void Sleep::Enter(Agent* agent)
{
    
    setStartValues("sleeping");

}

void Sleep::Exit(Agent* agent)
{
    
}

void Dead::Execute(Agent* agent)
{

}
void Dead::Enter(Agent* agent)
{
    
    setStartValues("dead");

}

void Dead::Exit(Agent* agent)
{
    

}