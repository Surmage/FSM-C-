#pragma once
#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <ctime>
#include "Telegram.h"
#include "TimeManager.h"
#include "States.h"

struct Agent
{
    float fullness;
    float thirst;
    float energy;
    float money;
    float happiness;
    string type;
    string status;
    string name;
    bool busy;
    bool canSocial;
    State* s;
    bool needRepair;
    Telegram* phone;
    TimeManager* clock;
    int timesAskedForHelp;
    float hour;
    tuple<float, Agent*>date;
    Agent() {

    }
    Agent(string name)
    {
        timesAskedForHelp = 0;
        canSocial = true;
        busy = false;
        needRepair = false;
        //randomize start values
        srand(time(NULL)); //reset rng seed
        float startValue1 = 4000 + rand() % 4001; //random between 4000 and 8000
        float startValue2 = 2000;
        float startValue3 = 4000 + rand() % 4001;
        fullness = startValue1;
        thirst = startValue1;
        energy = startValue2;
        money = startValue3;
        happiness = startValue3;
        phone = new Telegram;
        clock = new TimeManager;
        status = "Sleepy";
        s = NULL;
        enterState();
        type = s->type;
        date = std::make_tuple(0.0f, this);
        hour = 0;
    }
//
//    // Update is called once per frame
    void Update()
    {
        s->Execute(this);
        type = s->type;
        //hour = im.getHour();
        if (fullness <= 0 || thirst <= 0)
        {
            if (status != "Dead")
            {
                //Debug.Log("Died with this type: " + type + " and status: " + status);
                delete s;
                status = "Dead";
                s = getState(status);
                s->Enter(this);
            }
        }
        if (fullness < 0)
        {
            fullness = 0;
        }
        if (fullness > 8000)
        {
            fullness = 8000;
        }
        if (thirst < 0)
        {
            thirst = 0;
        }
        if (thirst > 8000)
        {
            thirst = 8000;
        }
        if (energy < 0)
        {
            energy = 0;
        }
        if (energy > 8000)
        {
            energy = 8000;
        }
        if (happiness <= 0)
        {
            happiness = 0;
        }
        if (happiness > 8000)
        {
            happiness = 8000;
        }
        hour = clock->getHour();
        if (hour == 22)
        {
            canSocial = false;
        }
        if (hour == 8)
        {
            canSocial = true;
        }
        if (get<0>(date) == hour) {
            startToSocial();
        }
    }
    void changeHunger(float change)
    {
        if (fullness >= 0 && fullness <= 8000)
        {
            fullness += change;
            if (!busy)
            {
                //If too low
                if (fullness <= 1000 && change < 0)
                {
                    checkShouldEnter();

                }
                //If too high
                else if (amIFine() && change > 0)
                {
                    checkShouldEnter();

                }
            }
        }
    }
    void changeThirst(float change)
    {
        if (thirst >= 0 && thirst <= 8000)
        {
            thirst += change;
            if (!busy)
            {
                //If too low
                if (thirst <= 1000 && change < 0)
                {
                    checkShouldEnter();

                }
                //If too high
                else if (amIFine() && change > 0)
                {
                    checkShouldEnter();

                }
            }
        }
    }
    void changeEnergy(float change)
    {
        if (energy >= 0 && energy <= 8000)
        {
            energy += change;
            if (!busy)
            {
                if (energy <= 0) //pass out
                {
                    //im.updateMessageText(name + " passed out");
                    busy = true;
                    changeHunger(-1500);
                    changeThirst(-1500);
                    changeMoney(-500);
                    busy = false;
                    checkShouldEnter();
                    return;
                }
                //If too low
                if (energy <= 1000 && change < 0)
                {
                    if (s->type == "socializing" && amIFine()) //stay up if socializing and not satisfied yet
                    {
                        checkShouldEnter();
                    }
                    else if (s->type != "socializing") //sleep if not socializing and tired
                    {
                        checkShouldEnter();
                    }
                }
                //If too high
                else if (change > 0 && hour >= 8 && hour <= 9) //Wake up between 8 and 9 if sleeping
                {
                    checkShouldEnter();
                }
            }
        }
    }
    void changeMoney(float change)
    {
        money += change;
        if (!busy)
        {
            if (status != "Social")
            {
                //if too low
                if (money < 1700 && change < 0)
                {
                    checkShouldEnter();
                }
            }
            //if too high
            else if (amIFine() && change > 0)
            {
                checkShouldEnter();
            }

        }

    }
    void changeHappiness(float change)
    {
        happiness += change;
        if (!busy)
        {
            //if too low
            if (happiness <= 2000 && change < 0 && canSocial)
            {
                checkShouldEnter();
            }
            //Change         


            //if too high
            else if (amIFine() && change > 0)
            {
                checkShouldEnter();
            }

        }
    }
    void checkShouldEnter()
    {
        //Check if already in state
        status = isAnythingLow();
        if (!compareStatusType())
        {
            enterState();
        }
    }
    void enterState()
    {
        delete s;
        s = getState(status);
        s->Enter(this);
        type = s->type;
    }

    void startToSocial()
    {
        delete s;
        s = new Social;
        s->Enter(this);
        type = s->type;

    }
    State* getState(string message)
    {
        State* s = NULL;
        //Plan to socialize
        //if (message == "Bored" && this->canSocial == true) //Maybe change implementation to one hour ahead? Meaning, they socialize one hour after being asked rather than at the end of current state
        //{
        //    if (this->money >= 1000) //If not broke
        //    {
        //        if (s->type != "Social") //If not already socializing
        //        {
        //            for (int i = 0; i < 4; i++) //Check through all agents
        //            {
        //                if (this->name != phone->getAgent(i).name) //Check that caller isn't asking themselves to hang out
        //                {
        //                    if (phone->dispatchMessage(0, this, &phone->getAgent(i), "") == "Yes") //If agent says yes
        //                    {
        //                        this->date = make_tuple(clock->getHour() + 2, &phone->getAgent(i));
        //                        phone->getAgent(i).date = make_tuple(clock->getHour() + 2, this); //Plan date
        //                    }
        //                }
        //            }
        //            //Make unable to socialize for 10 seconds (affected by speed variable)
        //            setCanSocial(false);
        //            //Find new state to enter
        //            message = this->isAnythingLow();
        //        }

        //    }
        //    else
        //    {
        //        //Make unable to socialize for 10 seconds (affected by speed variable)
        //        this->setCanSocial(false);
        //        //Find new state to enter
        //        message = this->isAnythingLow();
        //    }
        //}
        //Enter eat state
        if (message == "Hungry")
        {
            s = new Eat;
            return s;

        }
        //Enter sleep state
        if (message == "Sleepy")
        {
            s = new Sleep;
            return s;

        }
        //Enter drink state
        if (message == "Thirsty")
        {
            s = new Drink;
            return s;

        }
        //Enter gather state
        if (message == "Motivated")
        {
            s = new Gather;
            return s;

        }
        //Enter idle state
        if (message == "Fine")
        {
            s = new Idle;
            return s;

        }
        //Enter mining state
        if (message == "Poor")
        {
            s = new Mining;
            return s;

        }
        //Enter dead state
        if (message == "Dead")
        {
            s = new Dead;
            return s;
        }
        return s;
    }

    bool amIFine()
    {
        //Check if state main stat is high enough to exit
        if (s->type == "drinking")
        {
            if (thirst >= 8000)
            {
                return true;
            }
        }
        if (s->type == "eating")
        {
            if (fullness >= 8000)
            {
                return true;
            }
        }
        if (s->type == "sleeping")
        {
            if (energy >= 8000)
            {
                return true;
            }
        }
        if (s->type == "gathering")
        {
            if (money >= 5000)
            {
                return true;
            }
        }
        if (s->type == "mining")
        {
            if (money >= 10000)
            {
                return true;
            }
        }
        if (s->type == "socializing")
        {
            if (happiness >= 8000 && get<1>(date)->happiness >= 8000)
            {
                return true;
            }
        }
        return false;
    }
    bool canISocial()
    {
        //Check if state money stat is high enough to socialize
        if (money <= 1700)
        {
            return false;
        }
        else
        {
            if (s->type == "drinking")
            {
                return true;
            }
            if (s->type == "eating")
            {
                if (fullness >= 1000)
                {
                    return true;
                }
            }
            if (s->type == "sleeping")
            {
                return false;
            }
            if (s->type == "gathering")
            {
                return true;
            }
            if (s->type == "mining")
            {
                if (money >= 5000)
                {
                    return true;
                }
            }
            if (s->type == "idling around")
            {
                return true;
            }
            if (s->type == "socializing")
            {
                return true;
            }
        }
        return false;
    }
    string isAnythingLow()
    {
        vector<tuple<float, string>> arrs;
        arrs.push_back(tuple<float, string>(thirst, "Thirsty"));
        arrs.push_back(tuple<float, string>(energy, "Sleepy"));
        arrs.push_back(tuple<float, string>(fullness, "Hungry"));
        arrs.push_back(tuple<float, string>(money, "Poor"));
        arrs.push_back(tuple<float, string>(happiness, "Bored"));

        //Remove possibility of entering states if should be impossible

        if (!canSocial || money < 1000) //remove entering social as an option
        {
            arrs.pop_back();
        }
        if (needRepair && money < 1700) //remove mining as an option
        {
            arrs.erase(arrs.begin() + 3);
        }
        else if (energy <= 1000 || happiness <= 1000) //remove mining as an option too
        {
            arrs.erase(arrs.begin() + 3);
        }
        if (fullness <= 1000 && money < 200) //check if hungry and poor
        {
            if (timesAskedForHelp <= 4) //can only receive money for food 4 times before friends stop
            {
                //if (!phone->askForMoney(this)) //remove entering eating as an option
                //{
                //    arrs.erase(arrs.begin() + 2);
                //}
                //else
                //{
                //    timesAskedForHelp++;
                //    return "Hungry"; //eating will be the next state
                //}
            }
            else
            {
                arrs.erase(arrs.begin() + 2); //didn't receive money, can't afford food
            }
        }
        sort(arrs.begin(), arrs.end()); //sort

        //Return stat that is the lowest
        if (get<0>(arrs[0]) <= 1000)
        {
            return get<1>(arrs[0]);
        }

        else
        {
            //Enter Idle or Gathering 
            if (happiness >= 0)
            {
                srand(time(NULL)); //reset rng seed
                float mood = rand() % 3;
                if (mood == 2)
                {
                    if (status != "Fine")
                    {
                        return "Motivated";
                    }
                    else
                    {
                        return "Fine";
                    }
                }
                else
                {
                    if (status != "Motivated")
                    {
                        return "Fine";
                    }
                    else
                    {
                        return "Motivated";
                    }
                }

            }
            else
            {
                if (status != "Motivated")
                {
                    return "Fine";
                }
                else
                {
                    return "Motivated";
                }
            }
        }
        return status;
    }

    bool compareStatusType()
    {
        //Checks if type fits with status, for example: is the agent eating because they are hungry? Is the agent sleeping because they are sleepy?
        if (status == "Hungry")
        {
            if (type == "eating")
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        if (status == "Sleepy")
        {
            if (type == "sleeping")
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        if (status == "Thirsty")
        {
            if (type == "drinking")
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        if (status == "Motivated")
        {
            if (type == "gathering")
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        if (status == "Bored")
        {
            if (type == "socializing")
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        if (status == "Fine")
        {
            if (type == "idling around")
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        if (status == "Poor")
        {
            if (type == "mining")
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        if (status == "Dead")
        {
            return false;
        }
        return false;
    }

    void setCanSocial(bool value)
    {
        canSocial = value;
    }
    void setPhone(Telegram* t) {
        phone = t;
    }
    void setClock(TimeManager* h) {
        clock = h;
    }
};
