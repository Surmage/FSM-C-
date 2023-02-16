#pragma once
#include "Telegram.h"
#include "Agent.h"

Telegram::Telegram() :
    a(a), b(b), c(c), d(d), chat("\n")
{}
Telegram::Telegram(Agent& aa, Agent& bb, Agent& cc, Agent& dd) :
	a(aa), b(bb), c(cc), d(dd), chat("Chat:\n")
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
    //Check through all contacts (agents)
    for (int i = 0; i < 4; i++)
    {
        if (caller->name != getAgent(i)->name) //To avoid asking themselves for money
        {
            if (getAgent(i)->money >= 1500 && getAgent(i)->status != "Sleep" && getAgent(i)->status != "Dead")
            {
                //"busy" being true prevents the state from being changed
                getAgent(i)->busy = true;
                caller->busy = true;
                getAgent(i)->changeMoney(-500, false); //friend hands over money
                caller->changeMoney(500, false); //caller receives friends money
                caller->changeHappiness(2000, false); //caller is happy to have been helped
                getAgent(i)->busy = false;
                caller->busy = false;
                updateMessageText(caller->name + " received money from " + getAgent(i)->name);
                return true;
            }
        }
    }
    return false;
}
std::string Telegram::dispatchMessage(Agent* receiver)
{
    std::string msg;
    //If friend can social
    if (receiver->money >= 2000 && receiver->canISocial() && receiver->busy == false && receiver->status != "Dead")
    {
        msg = "Yes";      
    }
    //If friend doesn't have the money
    else if (receiver->money <= 2000)
    {
        msg = "I'm too poor";
    }
    //If friend can't for another reason
    else
    {
        msg = "Can't because I am" + receiver->type;

    }
    return msg;
}
char* Telegram::getMessageChat() {
    return chat;
}
void Telegram::updateMessageText(std::string msg)
{
    //Combine message with previous chat messages
    sprintf(chat, "%s\n%s", chat, msg.c_str()); 
    int count = 0; //Count for new lines

    char* str = chat;
    int size = strlen(str);
    char buf[200]; //Buffer used to 
    int j = 0;
    for (int i = 0;  i < size; i++) {
        str++;
        if (*str == '\n') { //Add to count for each new line
            count++;
        }
        if (count >= 3) {
            //Write rest of char array into buf
            buf[j] = *str;
            j++;
        }
    }
    // Greater than 7 (8) is used below because the chat is intended to have 6 saved messages at a time
    // And there are 2 new lines after the initial "Chat:" (2 + 6 = 8) 
    if (count > 7) { 
        //Chat array is set to buf
        sprintf(chat, "Chat:\n %s", buf);
    }
}