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

    Stats stats;
    int speed; //affects the rate at which the stats are affected

    std::string type; //current type, referring to state
    std::string status; //current status, referring to mood of the agent, dictates which state they enter
    std::string prevType; //previous type before entering current
    std::string prevStatus; //previous status
    std::string name; //name of agent
    bool busy; //busy is used to prevent function calls
    bool canSocial; //canSocial is used to enter and balance the social state
    State* s;
    bool needRepair; //repairing can become necessary from exiting the mining state, (repairing the pickaxe equipment)
    Telegram* phone; //phone to contact other agents
    TimeManager* clock; //clock to check time and day
    int timesAskedForHelp; //agent can receive money from other agents in emergencies
    int hour; //time 
    std::tuple<int, Agent*>date; //stores an hour and agent that this agent will socialize with

    Agent();
    Agent(std::string name);

    // Update is called in main loop
    void Update(int speed);
    void changeHunger(float change, bool affectedByTime);
    void changeThirst(float change, bool affectedByTime);
    void changeEnergy(float change, bool affectedByTime);
    void changeMoney(float change, bool affectedByTime);
    void changeHappiness(float change, bool affectedByTime);
    void checkShouldEnter();
    void enterState();

    void startToSocial();
    State* getState(std::string message);



    bool amIFine();
    bool canISocial();
    std::string isAnythingLow();

    bool compareStatusType();

    void setCanSocial(bool value);
    void setBusy(bool value);
    void setPhone(Telegram* t);
    void setClock(TimeManager* h);
    int* getMainStatValues();
    char* getState();
    char* getMoneyChar();
    void sendMessage(std::string msg);
};
