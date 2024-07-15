#pragma once
#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include "Telegram.h"
#include "TimeManager.h"
#include "States.h"
#include <sstream>


struct Agent
{
    struct Stats {
        float fullness; //increased by eating, decreased through other states
        float maxFullness;
        float thirst; //increased by eating, drinking and socializing, decreased through other states
        float maxThirst;
        float energy; //increased by sleeping, decreased through other states
        float maxEnergy;
        float happiness; //increased by eating and socializing, decreased through other states
        float maxHappiness;
        float money; //increased by working (gathering and mining), decreased through eating, socializing and repairing

        Stats();
    };

    

    enum struct Status : char
    {
        Sleepy = 'S',
        Hungry = 'H',
        Thirsty = 'T',
        Bored = 'B',
        Fine = 'F',
        Motivated = 'M',
        Poor = 'P',
        Dead = 'D'
    };
    

    Stats stats;
    Location location;
    int counter; //keeps track of cycles in a state, gets incremented by 1 per game loop until reset
    int workCounter; //cycles specially for mining state, to ensure the required work hours are met
    sf::Vector2f position;
    Status status; 
    Type type; //current type, referring to state
    int id;
    std::string name; //name of agent
    bool canSocial; //canSocial is used to enter and balance the social state
    State* s;
    bool needRepair; //repairing can become necessary from exiting the mining state, (repairing the pickaxe equipment)
    Telegram* phone; //phone to contact other agents
    StepManager* clock; //clock to check time and day
    int timesAskedForHelp; //agent can receive money from other agents in emergencies
    int hour; //time 
    std::tuple<int, Agent*>date; //stores an hour and agent that this agent will socialize with
    bool goBackToWork; //goes back to work after taking a drinking or eating break

    Agent();
    Agent(std::string name, int id);

    void Update(int speed);  // Update is called in main loop

    //Methods for changing a stat
    void changeHunger(float change);
    void changeThirst(float change);
    void changeEnergy(float change);
    void changeMoney(float change);
    void changeHappiness(float change);

    //Methods for handling agent switching states
    void checkShouldEnter();
    bool checkCanEnter(); //Checks if leaving their current state is appropriate
    void enterState(); //Handle state exit and enter
    void startToSocial(); //Skip previous stages and enter social state

    State* getState(Status &msg); //gets and changes appropriate state based on agent status

    bool amIFine(); //Checks if the agent has gained security from their current state
    bool inDanger(); //Checks if agent is in danger due to a low stat value
    bool canISocial(); //Checks if agent has the resources to socialize (money, fullness etc)
    bool isAnythingLow(Status &msg); //Retrieves the next appropriate state

    bool compareStatusType(); //Compares status and type to see if agent is in the correct state

    void setCanSocial(bool value);
    void setPhone(Telegram* t);
    void setClock(StepManager* h);  
    void sendMessage(std::string msg);
};
