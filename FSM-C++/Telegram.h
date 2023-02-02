#pragma once

struct Agent;

struct Telegram
{
    Agent* a;
    Agent* b;
    Agent* c;
    Agent* d;

    Telegram();
    Telegram(Agent *aa, Agent *bb, Agent *cc, Agent *dd);
   

    Agent* getAgent(int i);
   
    bool askForMoney(Agent* caller);
    char* dispatchMessage(Agent* sender, Agent* receiver, const char* incMsg);

};
