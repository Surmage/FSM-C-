#pragma once
#include <iostream>

struct Agent;

struct Telegram
{
    Agent& a;
    Agent& b;
    Agent& c;
    Agent& d;

    std::string chat;

    Telegram();
    Telegram(Agent &aa, Agent &bb, Agent &cc, Agent &dd);
   

    Agent* getAgent(int i);
   
    bool askForMoney(Agent* caller);
    std::string dispatchMessage(Agent* receiver);
    std::string getMessageChat();
    void updateMessageText(std::string msg);
};
