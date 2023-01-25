#pragma once
#include "Inclusions.h"
struct Telegram
{
    Agent v[4];
    Telegram() {

    }
    Telegram(vector<Agent>& container) {
        v[0] = container[0];
        v[1] = container[1];
        v[2] = container[2];
        v[3] = container[3];
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
    Agent getAgent(int i) {
        return v[i];
    }
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

};
