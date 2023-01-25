#pragma once
#include "Inclusions.h"
struct Telegram
{
    vector<Agent>v;
    float speed;
    Telegram(std::vector<Agent>& container) {
        v = container;
    }
   
    bool askForMoney(Agent* caller)
    {
        //Debug.Log(caller.name + " asked for help");
        for (int i = 0; i < 4; i++)
        {
            if (caller->name != v[i].name) //To avoid asking themselves for money
            {
                if (v[i].money >= 1500 && v[i].status != "Sleep" && v[i].status != "Dead")
                {
                    //"busy" being true prevents the state from being changed
                    v[i].busy = true;
                    caller->busy = true;
                    v[i].changeMoney(-500); //friend gives over money
                    caller->changeMoney(500); //caller receives friends money
                    caller->changeHappiness(2000); //caller is happy to have been helped
                    v[i].busy = false;
                    caller->busy = false;
                    return true;
                }
            }
        }
        return false;
    }
};
string dispatchMessage(float delay, Agent* sender, Agent* receiver, string incMsg)
{
    string msg = "";
    //im.updateMessageText(senderName + " is asking  " + receiverName + " to hangout.");
    if (receiver->money >= 2000 && receiver->canISocial() && receiver->busy == false && receiver->status != "Dead")
    {
        msg = "Yes";
    }
    else if (receiver->money <= 2000)
    {
        msg = "I'm too poor";
    }
    else
    {
        msg = "Can't because I am " + receiver->type;

    }
    //im.updateMessageText(receiverName + ": " + msg);
    return msg;
}
State *startToSocial(string message, State* s, Agent* caller)
{
    //If a socializing date has been planned
    if (s->Exit(caller) != "")
    {
        string friend = s->dateWith;

        //Find the friend
        for (int i = 0; i < 4; i++)
        {
            if (friend == friends[i].name)
            {
                //Friend enter social
                friends[i].GetComponent<AgentBehavior>().status = "Bored";
                friends[i].GetComponent<AgentBehavior>().enterSocial();
            }
        }
        //Caller enter social
        caller->status = "Bored";
        s = new Social;
        return s;

    }

    return s;
}