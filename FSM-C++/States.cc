#include "States.h"
#include "Agent.h"

State::State() 
{
    type = "";
    //3 represents taking 16 hours for stat to fill (Increase by 8000)
    //Multiplying it decreases the time it would take, example: 3 * 2 would take 8 hours, 3 * 8 would take 2 hours
    //Dividing it increases the time it would take, example: 3 / 2 would take 16 hours
    energyChangeVal = -2.f; 
    statChangeVal = 5.f;
}

void State::setStartValues(std::string type)
{
    this->type = type;
    energyChangeVal = -2.f;
    statChangeVal = 5.f;
}
void Drink::Execute(Agent* agent)
{
    //Change stat variables
    agent->changeEnergy(energyChangeVal, true);
    agent->changeThirst(statChangeVal * 20, true);
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
    agent->changeHunger(statChangeVal * 5, true);
    agent->busy = true;
    agent->changeThirst(statChangeVal * 10, true);
    agent->changeHappiness(statChangeVal * 0.2f, true);
    agent->busy = false;
}
void Eat::Enter(Agent* agent)
{
    setStartValues("eating");
    //Busy prevents function calls to change states
    agent->busy = true;
    //Pay for food
    agent->changeMoney(-10, false);
    agent->busy = false;
}

void Eat::Exit(Agent* agent)
{

}

void Gather::Execute(Agent* agent)
{
    //Change stat variables
    agent->changeEnergy(energyChangeVal, true);
    agent->changeHunger(-statChangeVal, true);
    agent->changeThirst(-statChangeVal * 2, true);
    agent->changeMoney(statChangeVal, true);
    agent->changeHappiness(-statChangeVal * 0.8f, true);
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
    agent->changeHunger(-statChangeVal, true);
    agent->changeThirst(-statChangeVal * 1.5f, true);
    agent->changeHappiness(-statChangeVal * 0.5f, true);
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
    agent->changeHunger(-statChangeVal * 0.5f, true);
    agent->changeThirst(-statChangeVal, true);
    agent->changeMoney(statChangeVal * 4, true);
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
        agent->changeMoney(-15, false);
        agent->busy = false;
        //agent->sendMessage(agent->name + " repaired their pickaxe.");
    }
}

void Mining::Exit(Agent* agent)
{
    //Chance for pickaxe to need repairing
    int pickaxeBreakChance = rand() % 21; //5% chance
    if (pickaxeBreakChance == 0)
    {
        agent->needRepair = true;
        //agent->sendMessage(agent->name + "'s pickaxe broke.");
    }

}

void Social::Execute(Agent* agent)
{
    //Change stat variables
    agent->changeHappiness(statChangeVal * 4, true);
    //Busy prevents function calls to change states
    agent->busy = true;
    agent->changeEnergy(energyChangeVal, true);
    agent->changeHunger(statChangeVal * 4, true);
    agent->changeThirst(statChangeVal * 8, true);
    agent->busy = false;
}
void Social::Enter(Agent* agent)
{
    //Busy prevents function calls to change states
    agent->busy = true;
    agent->changeMoney(-10, false);
    agent->changeHappiness(statChangeVal * 5.f, false);
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
    agent->changeHunger(-statChangeVal * 0.01f, true);
    agent->changeThirst(-statChangeVal * 0.01f, true);
    agent->busy = false;
    agent->changeEnergy(-energyChangeVal, true);
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