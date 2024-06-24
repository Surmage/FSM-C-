#include "States.h"
#include "Agent.h"

State::State() 
{
    type = Type::Sleeping;
    //3 represents taking 16 hours for stat to fill (Increase by 8000)
    //Multiplying it decreases the time it would take, example: 3 * 2 would take 8 hours, 3 * 8 would take 2 hours
    //Dividing it increases the time it would take, example: 3 / 2 would take 16 hours
    energyChangeVal = -2.f; 
    statChangeVal = 5.f;
}

void Drink::Execute(Agent* agent)
{
    //Change stat variables
    agent->changeEnergy(energyChangeVal * 0.5f, true);
    agent->changeHunger(-statChangeVal * 0.5f, true);
    agent->changeThirst(statChangeVal * 20, true);
    agent->counter++;
}
void Drink::Enter(Agent* agent)
{
    this->type = Type::Drinking;
    agent->counter = 0;
}

void Drink::Exit(Agent* agent)
{

}

void Eat::Execute(Agent* agent)
{
    //Change stat variables
    agent->changeEnergy(energyChangeVal * 0.5f, true);
    agent->changeHunger(statChangeVal * 10, true);
    agent->busy = true;
    agent->changeThirst(statChangeVal * 10, true);
    agent->changeHappiness(statChangeVal * 0.2f, true);
    agent->busy = false;
    agent->counter++;
}
void Eat::Enter(Agent* agent)
{
    this->type = Type::Eating;
    //Busy prevents function calls to change states
    agent->busy = true;
    //Pay for food
    agent->changeMoney(-25, false);
    agent->busy = false;
    agent->counter = 0;
}

void Eat::Exit(Agent* agent)
{

}

void Gather::Execute(Agent* agent)
{
    //Change stat variables
    agent->changeEnergy(energyChangeVal * 0.5f, true);
    agent->changeHunger(-statChangeVal * 0.5f, true);
    agent->changeThirst(-statChangeVal * 2, true);
    agent->changeMoney(statChangeVal, true);
    agent->changeHappiness(-statChangeVal * 0.02f, true);
    agent->counter++;
}
void Gather::Enter(Agent* agent)
{
    this->type = Type::Gathering;
    agent->counter = 0;

}

void Gather::Exit(Agent* agent)
{

}

void Idle::Execute(Agent* agent)
{
    //Change stat variables
    agent->changeEnergy(energyChangeVal * 0.5f, true);
    agent->changeHunger(-statChangeVal * 0.5f, true);
    agent->changeThirst(-statChangeVal * 1.5f, true);
    agent->changeHappiness(-statChangeVal * 0.05f, true);
    agent->counter++;
}
void Idle::Enter(Agent* agent)
{
    this->type = Type::Lazing;
    agent->counter = 0;

}

void Idle::Exit(Agent* agent)
{

}

void Mining::Execute(Agent* agent)
{
    //Change stat variables
    agent->changeEnergy(energyChangeVal * 0.5f, true);
    agent->changeHunger(-statChangeVal * 0.5f, true);
    agent->changeThirst(-statChangeVal, true);
    agent->changeMoney(statChangeVal * 4, true);
    agent->changeHappiness(-statChangeVal * 0.2f, true);
    agent->counter++;
}
void Mining::Enter(Agent* agent)
{
    this->type = Type::Mining;
    if (agent->needRepair)
    {
        //Busy prevents function calls to change states
        agent->busy = true;
        agent->needRepair = false;
        agent->changeMoney(-100, false);
        agent->busy = false;
        agent->sendMessage(agent->name + " repaired their pickaxe.");
    }
    agent->counter = 0;
}

void Mining::Exit(Agent* agent)
{
    //Chance for pickaxe to need repairing
    int pickaxeBreakChance = rand() % 11; //10% chance
    if (pickaxeBreakChance == 0)
    {
        agent->needRepair = true;
        std::cout << agent->name << " pickaxe broke" << std::endl;
        agent->sendMessage(agent->name + "'s pickaxe broke.");
    }

}

void Social::Execute(Agent* agent)
{
    //Change stat variables
    agent->changeHappiness(statChangeVal * 2, true);
    //Busy prevents function calls to change states
    agent->busy = true;
    agent->changeMoney(-10, false);
    agent->changeEnergy(energyChangeVal * 0.5f, true);
    agent->changeHunger(statChangeVal * 4, true);
    agent->changeThirst(statChangeVal * 8, true);
    agent->busy = false;
    agent->counter++;
}
void Social::Enter(Agent* agent)
{
    this->type = Type::Socializing;
    //Busy prevents function calls to change states
    agent->busy = true;
    agent->changeMoney(-50, false);
    agent->changeHappiness(statChangeVal * 3.f, false);
    agent->busy = false;
    agent->counter = 0;
    std::cout << agent->name << " enterered social" << std::endl;
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
    agent->counter++;
}
void Sleep::Enter(Agent* agent)
{
    
    this->type = Type::Sleeping;
    agent->counter = 0;

}

void Sleep::Exit(Agent* agent)
{
    
}

void Dead::Execute(Agent* agent)
{
    agent->counter++;
}
void Dead::Enter(Agent* agent)
{
    
    this->type = Type::Dead;
    agent->counter = 0;
}

void Dead::Exit(Agent* agent)
{
    

}