#include "Telegram.h"
#include "Agent.h"

Telegram::Telegram() :
    a(a), b(b), c(c), d(d), chat("Chat:\n")
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

void Telegram::printAgentStats() {
    std::cout << a.stats.energy << std::endl;
}
bool Telegram::askForMoney(Agent* caller)
{
    //Check through all contacts (agents)
    for (int i = 0; i < 4; i++)
    {
        if (caller->name != getAgent(i)->name) //To avoid asking themselves for money
        {
            if (getAgent(i)->stats.money >= 200 && getAgent(i)->type != Type::Sleeping && getAgent(i)->type != Type::Dead)
            {
                //"busy" being true prevents the state from being changed
                getAgent(i)->changeMoney(-100); //friend hands over money
                caller->changeMoney(100); //caller receives friends money
                caller->changeHappiness(50); //caller is happy to have been helped
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
    if (receiver->stats.money >= 100 && receiver->canISocial() && receiver->type != Type::Dead)
    {
        msg = "Yes";      
    }
    //If friend doesn't have the money
    else if (receiver->stats.money <= 100)
    {
        msg = "I'm too poor";
    }
    //If friend can't for another reason
    else
    {
        msg = "Can't because I am " + static_cast<char>(receiver->type);

    }
    return msg;
}
std::string Telegram::getMessageChat() {
    return chat;
}
void Telegram::updateMessageText(std::string msg)
{
    //Combine message with previous chat messages
    chat += "\n" + msg;
    int count = 0; //Count for new lines

    std::string buf; //Buffer 
    for (int i = 0;  i < chat.length(); i++) {
        if (chat[i] == '\n') { //Add to count for each new line
            count++;
        }
        if (count >= 3) {
            //Write rest of char array into buf
            buf += chat[i];
        }
    }
    // Greater than 7 (8) is used below because the chat is intended to have 6 saved messages at a time
    // And there are 2 new lines after the initial "Chat:" (2 + 6 = 8) 
    if (count > 7) { 
        //Chat array is set to buf
        chat = buf;
    }
}