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
    int counter;
    int workCounter;
    sf::Vector2f position;
    Status status; //current type, referring to state
    Type type; //current status, referring to mood of the agent, dictates which state they enter
    Type prevType; //previous type before entering current
    //std::string prevStatus; //previous status
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
    bool goBackToWork;

    Agent();
    Agent(std::string name, int id);

    // Update is called in main loop
    void Update(int speed);
    void changeHunger(float change);
    void changeThirst(float change);
    void changeEnergy(float change);
    void changeMoney(float change);
    void changeHappiness(float change);
    void checkShouldEnter();
    bool checkCanEnter(Status &status);
    void enterState();

    void startToSocial();
    State* getState(Status &msg);



    bool amIFine();
    bool inDanger();
    bool canISocial();
    bool isAnythingLow(Status &msg);

    bool compareStatusType();

    void setCanSocial(bool value);
    void setPhone(Telegram* t);
    void setClock(StepManager* h);
    
    int* getMainStatValues();
    char* getState();
    char* getMoneyChar();
    void sendMessage(std::string msg);
};
