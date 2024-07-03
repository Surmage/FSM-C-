#include "States.h"
#include "Agent.h"

State::State() 
{
    type = Type::Sleeping;
    //3 represents taking 16 hours for stat to fill (Increase by 8000)
    //Multiplying it decreases the time it would take, example: 3 * 2 would take 8 hours, 3 * 8 would take 2 hours
    //Dividing it increases the time it would take, example: 3 / 2 would take 16 hours
    energyChangeVal = 0.9375f; //90 energy / 16 hours = 5.625 => 5.625 / 6 = 0.9375
    statChangeVal = 5.f;
}

void Drink::Execute(Agent* agent)
{
    //Change stat variables
    agent->changeEnergy(-energyChangeVal);
    agent->changeHunger(-statChangeVal * 0.5f);
    agent->changeThirst(statChangeVal * 20);
    agent->counter++;
}
void Drink::Enter(Agent* agent)
{
    this->type = Type::Drinking;
    int posFromLoc = static_cast<int>(agent->location);
    agent->position = LocationC::getCoords(posFromLoc, agent->id);
    agent->counter = 0;
}

void Drink::Exit(Agent* agent)
{

}

void Eat::Execute(Agent* agent)
{
    //Change stat variables
    agent->changeEnergy(-energyChangeVal);
    agent->changeHunger(statChangeVal * 10);
    agent->busy = true;
    agent->changeThirst(statChangeVal * 10);
    agent->changeHappiness(statChangeVal * 0.2f);
    agent->busy = false;
    agent->counter++;
}
void Eat::Enter(Agent* agent)
{
    this->type = Type::Eating;
    agent->location = (Location::Restaurant);
    int posFromLoc = static_cast<int>(agent->location);
    agent->position = LocationC::getCoords(posFromLoc, agent->id);
    //Busy prevents function calls to change states
    agent->busy = true;
    //Pay for food
    agent->changeMoney(-25);
    agent->busy = false;
    agent->counter = 0;
}

void Eat::Exit(Agent* agent)
{

}

void Gather::Execute(Agent* agent)
{
    //Change stat variables
    agent->changeEnergy(-energyChangeVal);
    agent->changeHunger(-statChangeVal * 0.5f);
    agent->changeThirst(-statChangeVal * 2);
    agent->changeMoney(statChangeVal);
    agent->changeHappiness(-statChangeVal * 0.02f);
    agent->counter++;
}
void Gather::Enter(Agent* agent)
{
    this->type = Type::Gathering;
    agent->location = (Location::Field);
    int posFromLoc = static_cast<int>(agent->location);
    agent->position = LocationC::getCoords(posFromLoc, agent->id);
    agent->counter = 0;

}

void Gather::Exit(Agent* agent)
{

}

void Idle::Execute(Agent* agent)
{
    //Change stat variables
    agent->changeEnergy(-energyChangeVal);
    agent->changeHunger(-statChangeVal * 0.5f);
    agent->changeThirst(-statChangeVal * 1.5f);
    agent->changeHappiness(-statChangeVal * 0.05f);
    agent->counter++;
}
void Idle::Enter(Agent* agent)
{
    this->type = Type::Lazing;
    agent->location = (Location::Home);
    int posFromLoc = static_cast<int>(agent->location);
    agent->position = LocationC::getCoords(posFromLoc, agent->id);
    agent->counter = 0;

}

void Idle::Exit(Agent* agent)
{

}

void Mining::Execute(Agent* agent)
{
    //Change stat variables
    agent->changeEnergy(-energyChangeVal);
    agent->changeHunger(-statChangeVal * 0.5f);
    agent->changeThirst(-statChangeVal);
    agent->changeMoney(statChangeVal * 4);
    agent->changeHappiness(-statChangeVal * 0.2f);
    agent->counter++;
}
void Mining::Enter(Agent* agent)
{
    this->type = Type::Mining;
    agent->location = (Location::Mines);
    int posFromLoc = static_cast<int>(agent->location);
    agent->position = LocationC::getCoords(posFromLoc, agent->id);
    if (agent->needRepair)
    {
        //Busy prevents function calls to change states
        agent->busy = true;
        agent->needRepair = false;
        agent->changeMoney(-100);
        agent->busy = false;
        agent->sendMessage(agent->name + " repaired their pickaxe.");
    }
    if (agent->goBackToWork) {
        agent->counter = agent->workCounter;
        std::cout << agent->name << " came back to work" << std::endl;
    }
    else {
        agent->counter = 0;
    }
        
    agent->goBackToWork = false;
}

void Mining::Exit(Agent* agent)
{
    //Chance for pickaxe to need repairing
    int pickaxeBreakChance = rand() % 11; //10% chance
    if (pickaxeBreakChance == 0 && !agent->goBackToWork)
    {
        agent->needRepair = true;
        std::cout << agent->name << " pickaxe broke" << std::endl;
        agent->sendMessage(agent->name + "'s pickaxe broke.");
    }
    if (agent->counter < 36) {
        agent->goBackToWork = true;
        agent->workCounter = agent->counter;
        std::cout << agent->name << " left work but will be back." << std::endl;
    }
    else
        agent->workCounter = 0;
       
}

void Social::Execute(Agent* agent)
{
    //Change stat variables
    agent->changeHappiness(statChangeVal * 2);
    //Busy prevents function calls to change states
    agent->busy = true;
    agent->changeMoney(-10);
    agent->changeEnergy(-energyChangeVal);
    agent->changeHunger(statChangeVal * 4);
    agent->changeThirst(statChangeVal * 8);
    agent->busy = false;
    agent->counter++;
}
void Social::Enter(Agent* agent)
{
    this->type = Type::Socializing;
    agent->location = (Location::Bar);
    int posFromLoc = static_cast<int>(agent->location);
    agent->position = LocationC::getCoords(posFromLoc, agent->id);
    //Busy prevents function calls to change states
    agent->busy = true;
    agent->changeMoney(-50);
    agent->changeHappiness(statChangeVal * 3.f);
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
    agent->changeHunger(-statChangeVal * 0.01f);
    agent->changeThirst(-statChangeVal * 0.01f);
    agent->busy = false;
    agent->changeEnergy(energyChangeVal * 2.f);
    agent->counter++;
}
void Sleep::Enter(Agent* agent)
{
    
    this->type = Type::Sleeping;
    agent->location = (Location::Home);
    int posFromLoc = static_cast<int>(agent->location);
    agent->position = LocationC::getCoords(posFromLoc, agent->id);
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