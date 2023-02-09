#pragma once
#include "Telegram.h"
#include "Agent.h"

Telegram::Telegram() :
    a(a), b(b), c(c), d(d)
{}
Telegram::Telegram(Agent& aa, Agent& bb, Agent& cc, Agent& dd) :
	a(aa), b(bb), c(cc), d(dd), chat("Chat:")
{}

Agent* Telegram::getAgent(int i) {
	switch (i)
	{
	case 1:
		return &a;
	case 2:
		return &b;
	case 3:
		return &c;
	case 4:
		return &d;
	default:
		return &a;
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
                getAgent(i)->changeMoney(-500, false); //friend gives over money
                caller->changeMoney(500, false); //caller receives friends money
                caller->changeHappiness(2000, false); //caller is happy to have been helped
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
    char msg[100];
    //im.updateMessageText(senderName + " is asking  " + receiverName + " to hangout.");
    if (receiver->money >= 2000 && receiver->canISocial() && receiver->busy == false && receiver->status != "Dead")
    {
        sprintf(msg, "Yes");      
    }
    else if (receiver->money <= 2000)
    {
        sprintf(msg, "I'm too poor");
    }
    else
    {
        sprintf(msg, "Can't because I am%s", receiver->type.c_str());

    }
    
    //im.updateMessageText(receiverName + ": " + msg);
    return msg;
}
char* Telegram::getMessageChat() {
    return chat;
}
void Telegram::updateMessageText(std::string msg)
{
    sprintf(chat, "%s", msg.c_str());
    //chat += buf;

    //int numLines = messagesText.text.Split('\n').Length;
    ////Remove upper messages
    //if (numLines > 6)
    //{
    //    string[] items = messagesText.text.Split('\n');
    //    messagesText.text = items[1] + "\n" + items[2] + "\n" + items[3] + "\n" + items[4] + "\n" + items[5] + "\n";
    //}
}