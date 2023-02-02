#pragma once
#include "Telegram.h"
#include "Agent.h"

Telegram::Telegram() :
	a(0), b(0), c(0), d(0)
{}
Telegram::Telegram(Agent* aa, Agent* bb, Agent* cc, Agent* dd) :
	a(aa), b(bb), c(cc), d(dd)
{}

Agent* Telegram::getAgent(int i) {
	switch (i)
	{
	case 1:
		return a;
	case 2:
		return b;
	case 3:
		return c;
	case 4:
		return d;
	default:
		return a;
	}

}
bool Telegram::askForMoney(Agent* caller)
{
    //Debug.Log(caller.name + " asked for help");
    for (int i = 0; i < 4; i++)
    {
        if (caller != getAgent(i)) //To avoid asking themselves for money
        {
            if (getAgent(i)->money >= 1500 && getAgent(i)->status != "Sleep" && getAgent(i)->status != "Dead")
            {
                //"busy" being true prevents the state from being changed
                getAgent(i)->busy = true;
                caller->busy = true;
                getAgent(i)->changeMoney(-500); //friend gives over money
                caller->changeMoney(500); //caller receives friends money
                caller->changeHappiness(2000); //caller is happy to have been helped
                getAgent(i)->busy = false;
                caller->busy = false;
                return true;
            }
        }
    }
    return false;
}
char* Telegram::dispatchMessage(Agent* sender, Agent* receiver, const char* incMsg)
{
    char msg[50];
    //im.updateMessageText(senderName + " is asking  " + receiverName + " to hangout.");
    /*if (receiver->money >= 2000 && receiver->canISocial() && receiver->busy == false && receiver->status != "Dead")
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

    }*/
    //im.updateMessageText(receiverName + ": " + msg);
    return msg;
}