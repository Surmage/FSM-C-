#pragma once
#include "Idle.h"
struct Telegram
{
    /*GameObject interfaceM;
    InterfaceManager im;
    [SerializeField] public List<GameObject> states = new List<GameObject>();
    [SerializeField] public List<GameObject> friends = new List<GameObject>();*/
    vector<Agent>v;
    float speed;
    Telegram(std::vector<Agent>& container) {
        v = container;
    }
    void Start()
    {
        interfaceM = GameObject.Find("InterfaceManager");
        im = interfaceM.GetComponent<InterfaceManager>();
        speed = im.speed;
    }
    string dispatchMessage(float delay, string senderName, string receiverName, string incMsg)
    {
        GameObject receiver = GameObject.Find(receiverName);

        var recAct = receiver.GetComponent<AgentBehavior>();
        string msg = "";
        im.updateMessageText(senderName + " is asking  " + receiverName + " to hangout.");
        if (recAct.money >= 2000 && recAct.canISocial() && recAct.busy == false && recAct.status != "Dead")
        {
            msg = "Yes";
        }
        else if (recAct.money <= 2000)
        {
            msg = "I'm too poor";
        }
        else
        {
            msg = "Can't because I am " + recAct.type;

        }
        im.updateMessageText(receiverName + ": " + msg);
        return msg;
    }
    State changeState(string message, State s, Agent* caller)
    {
        //If a socializing date has been planned
        if (s.Exit(caller) != "")
        {
            string friend = s.dateWith;

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
            s = states[4].GetComponent<Social>();
            return s;

        }
        //Plan to socialize
        if (message == "Bored" && caller->canSocial == true) //Maybe change implementation to one hour ahead? Meaning, they socialize one hour after being asked rather than at the end of current state
        {
            if (caller->money >= 1000) //If not broke
            {
                if (s.type != "Social") //If not already socializing
                {
                    for (int i = 0; i < 4; i++) //Check through all agents
                    {
                        if (caller->name != v[i].name) //Check that caller isn't asking themselves to hang out
                        {
                            if (dispatchMessage(0, caller->name, v[i].name, "") == "Yes") //If agent says yes
                            {
                                v[i].s.setDate(caller); //Plan date
                            }
                        }
                    }
                    //Make unable to socialize for 10 seconds (affected by speed variable)
                    StartCoroutine(caller.setCanSocial(10));
                    //Find new state to enter
                    message = caller->isAnythingLow();
                }

            }
            else
            {
                //Make unable to socialize for 10 seconds (affected by speed variable)
                StartCoroutine(caller.setCanSocial(10));
                //Find new state to enter
                message = caller->isAnythingLow();
            }
        }
        //Enter eat state
        if (message == "Hungry")
        {
            s = states[0].GetComponent<Eat>();
            return s;

        }
        //Enter sleep state
        if (message == "Sleepy")
        {
            s = states[1].GetComponent<Sleep>();
            return s;

        }
        //Enter drink state
        if (message == "Thirsty")
        {
            s = states[2].GetComponent<Drink>();
            return s;

        }
        //Enter gather state
        if (message == "Motivated")
        {
            s = states[3].GetComponent<Gather>();
            return s;

        }
        //Enter idle state
        if (message == "Fine")
        {
            s = states[5].GetComponent<Idle>();
            return s;

        }
        //Enter mining state
        if (message == "Poor")
        {
            s = states[6].GetComponent<Mining>();
            return s;

        }
        //Enter dead state
        if (message == "Dead")
        {
            s = states[7].GetComponent<Dead>();
            return s;
        }
        return s;
    }
    State changeState(int i, State s, Agent caller)
    {
        //Change state based of index i
        if (s != null)
        {
            s.Exit(caller.name);
        }
        if (i == 0)
        {
            s = states[0].GetComponent<Eat>();
        }
        if (i == 1)
        {
            s = states[1].GetComponent<Sleep>();
        }
        if (i == 2)
        {
            s = states[2].GetComponent<Drink>();
        }
        if (i == 3)
        {
            s = states[3].GetComponent<Gather>();
        }
        if (i == 4)
        {
            s = states[4].GetComponent<Social>();
        }
        if (i == 5)
        {
            s = states[5].GetComponent<Dead>();
        }

        return s;
    }
    bool askForMoney(Agent caller)
    {
        //Debug.Log(caller.name + " asked for help");
        for (int i = 0; i < 4; i++)
        {
            if (caller.name != v[i].name) //To avoid asking themselves for money
            {
                Agent friend = v[i];
                if (friend.money >= 1500 && friend.status != "Sleep" && friend.status != "Dead")
                {
                    //"busy" being true prevents the state from being changed
                    friend.busy = true;
                    caller.busy = true;
                    friend.changeMoney(-500);
                    caller.changeMoney(500);
                    caller.changeHappiness(2000);
                    friend.busy = false;
                    caller.busy = false;
                    return true;
                }
            }
        }
        return false;
    }
    float getSpeed()
    {
        return speed;
    }
};