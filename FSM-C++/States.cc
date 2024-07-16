#include "States.h"
#include "Agent.h"

State::State() 
{
    //3 represents taking 16 hours for stat to fill (Increase by 8000)
    //Multiplying it decreases the time it would take, example: 3 * 2 would take 8 hours, 3 * 8 would take 2 hours
    //Dividing it increases the time it would take, example: 3 / 2 would take 16 hours
    this->energyChangeVal = 0.9375f; //90 energy / 16 hours = 5.625 => 5.625 / 6 = 0.9375
    this->statChangeVal = 5.f;
}

void Drink::Execute(Agent* agent)
{
    //Change stat variables
    agent->changeEnergy(-this->energyChangeVal);
    agent->changeHunger(-this->statChangeVal * 0.5f);
    agent->changeThirst(this->statChangeVal * 20);
    agent->counter++;
}
void Drink::Enter(Agent* agent)
{
    agent->type = Type::Drinking;
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
    agent->changeEnergy(-this->energyChangeVal);
    agent->changeHunger(this->statChangeVal * 10);
    agent->changeThirst(this->statChangeVal * 10);
    agent->changeHappiness(this->statChangeVal * 0.1f);
    agent->counter++;
}
void Eat::Enter(Agent* agent)
{
    agent->type = Type::Eating;
    agent->location = (Location::Restaurant);
    int posFromLoc = static_cast<int>(agent->location);
    agent->position = LocationC::getCoords(posFromLoc, agent->id);
    //Busy prevents function calls to change states
    //Pay for food
    agent->changeMoney(-50);
    agent->counter = 0;
}

void Eat::Exit(Agent* agent)
{

}

void Gather::Execute(Agent* agent)
{
    //Change stat variables
    agent->changeEnergy(-this->energyChangeVal);
    agent->changeHunger(-this->statChangeVal * 0.5f);
    agent->changeThirst(-this->statChangeVal * 2);
    agent->changeMoney(this->statChangeVal);
    agent->changeHappiness(-this->statChangeVal * 0.02f);
    agent->counter++;
}
void Gather::Enter(Agent* agent)
{
    agent->type = Type::Gathering;
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
    agent->changeEnergy(-this->energyChangeVal);
    agent->changeHunger(-this->statChangeVal * 0.5f);
    agent->changeThirst(-this->statChangeVal * 1.5f);
    agent->changeHappiness(-this->statChangeVal * 0.02f);
    agent->changeMoney(-5);
    agent->counter++; 
}
void Idle::Enter(Agent* agent)
{
    agent->type = Type::Lazing;
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
    agent->changeEnergy(-this->energyChangeVal);
    agent->changeHunger(-this->statChangeVal * 0.5f);
    agent->changeThirst(-this->statChangeVal);
    agent->changeMoney(this->statChangeVal * 2);
    agent->changeHappiness(-this->statChangeVal * 0.1f);
    agent->counter++;
}
void Mining::Enter(Agent* agent)
{
    agent->type = Type::Mining;
    agent->location = (Location::Mines);
    int posFromLoc = static_cast<int>(agent->location);
    agent->position = LocationC::getCoords(posFromLoc, agent->id);
    if (agent->needRepair)
    {
        //Busy prevents function calls to change states
        agent->needRepair = false;
        agent->changeMoney(-300);
        agent->sendMessage(agent->name + " repaired their pickaxe.");
    }
    if (agent->goBackToWork) {
        agent->counter = agent->workCounter;
        //std::cout << agent->name << " came back to work" << std::endl;
    }
    else {
        agent->counter = 0;
    }
        
    agent->goBackToWork = false;
}

void Mining::Exit(Agent* agent)
{
    if (agent->counter < 36 && agent->stats.energy > 20) {
        agent->goBackToWork = true;
        agent->workCounter = agent->counter;
        //std::cout << agent->name << " left work but will be back." << std::endl;
    }
    else
        agent->workCounter = 0;
    //Chance for pickaxe to need repairing
    int pickaxeBreakChance = rand() % 11; //10% chance
    if (pickaxeBreakChance == 0 && !agent->goBackToWork)
    {
        agent->needRepair = true;
        agent->sendMessage(agent->name + "'s pickaxe broke.");
    }
}

void Social::Execute(Agent* agent)
{
    //Change stat variables
    agent->changeHappiness(this->statChangeVal);
    //Busy prevents function calls to change states
    agent->changeMoney(-15);
    agent->changeEnergy(-this->energyChangeVal);
    agent->changeHunger(this->statChangeVal * 4);
    agent->changeThirst(this->statChangeVal * 8);
    agent->counter++;
}
void Social::Enter(Agent* agent)
{
    agent->type = Type::Socializing;
    agent->location = (Location::Bar);
    int posFromLoc = static_cast<int>(agent->location);
    agent->position = LocationC::getCoords(posFromLoc, agent->id);
    //Busy prevents function calls to change states
    agent->changeMoney(-50);
    agent->changeHappiness(this->statChangeVal * 2.f);
    
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
    agent->changeHunger(-this->statChangeVal * 0.01f);
    agent->changeThirst(-this->statChangeVal * 0.01f);
    agent->changeEnergy(this->energyChangeVal * 2.f);
    agent->counter++;
}
void Sleep::Enter(Agent* agent)
{   
    agent->type = Type::Sleeping;
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
    
    agent->type = Type::Dead;
    agent->location = (Location::Graveyard);
    int posFromLoc = static_cast<int>(agent->location);
    agent->position = LocationC::getCoords(posFromLoc, agent->id);
    agent->counter = 0;
}

void Dead::Exit(Agent* agent)
{
    

}