#pragma once
#include <iostream>
#include <string>
#include "Idle.h"
#include <vector>
#include <tuple>
using namespace std;
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
    int timesAskedForHelp;
    /*GameObject messageDispatcher;
    Telegram telegram;
    GameObject interfaceManager;
    InterfaceManager im;
    GameObject state;*/
    float hour;
    // Start is called before the first frame update
    Agent() {

    }
    Agent(string name)
    {
        timesAskedForHelp = 0;
        canSocial = true;
        busy = false;
        status = "";
        needRepair = false;
        //randomize start values
        float startValue1 = Random.Range(4000, 8000);
        float startValue2 = 2000;
        float startValue3 = Random.Range(4000, 8000);
        fullness = startValue1;
        thirst = startValue1;
        energy = startValue2;
        money = startValue3;
        happiness = startValue3;
        /*messageDispatcher = GameObject.Find("MessageDispatcher");
        telegram = messageDispatcher.GetComponent<Telegram>();
        interfaceManager = GameObject.Find("InterfaceManager");
        im = interfaceManager.GetComponent<InterfaceManager>();*/
        s = NULL;
        //s = telegram.changeState(1, s, this);
        this->name = name;
        s->Enter(name);
        type = s->type;
        //hour = im.getHour();
    }

    // Update is called once per frame
    void Update()
    {
        s->Execute(name);
        type = s->type;
        //hour = im.getHour();
        if (fullness <= 0 || thirst <= 0)
        {
            if (status != "Dead")
            {
                //Debug.Log("Died with this type: " + type + " and status: " + status);
                status = "Dead";
                //s = telegram.changeState(status, s, this);
                s->Enter(name);
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
        if (hour == 0)
        {
            canSocial = false;
        }
        if (hour == 8)
        {
            canSocial = true;
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
        //s = telegram.GetComponent<Telegram>().changeState(status, s, this);
        s->Enter(name);
        type = s->type;
    }
    void enterSocial()
    {
        //s = telegram.GetComponent<Telegram>().changeState(4, s, this);
        s->Enter(name);
        type = s->type;
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
            if (happiness >= 8000)
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
        arrs =
        {
            (thirst, "Thirsty"), (energy, "Sleepy"), (fullness, "Hungry"), (money, "Poor"), (happiness, "Bored")
        };

        //Remove possibility of entering states if should be impossible

        if (!canSocial || money < 1000) //remove entering social as an option
        {
            arrs.RemoveAt(4);
        }
        if (needRepair && money < 1700) //remove mining as an option
        {
            arrs.RemoveAt(3);
        }
        else if (energy <= 1000 || happiness <= 1000) //remove mining as an option too
        {
            arrs.RemoveAt(3);
        }
        if (arrs[2].Item1 <= 1000 && money < 200) //check if hungry and poor
        {
            if (timesAskedForHelp <= 4) //can only receive money for food 4 times before friends stop
            {
                if (!telegram.askForMoney(this)) //remove entering eating as an option
                {
                    arrs.RemoveAt(2);
                }
                else
                {
                    timesAskedForHelp++;
                    return "Hungry"; //eating will be the next state
                }
            }
            else
            {
                arrs.RemoveAt(2); //didn't receive money, can't afford food
            }
        }
        arrs.Sort();

        //Return stat that is the lowest
        if (arrs[0].Item1 <= 1000)
        {
            return arrs[0].Item2;
        }

        else
        {
            //Enter Idle or Gathering 
            if (happiness >= 0)
            {
                float mood = Random.Range(0, 3);
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

    private bool compareStatusType()
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

    public IEnumerator setCanSocial(float waitTime)
    {
        //Set canSocial variable with a timer 
        if (canSocial)
        {
            canSocial = false;

            WaitForSeconds wait = new WaitForSeconds(waitTime / telegram.getSpeed()); //Cooldown on canSocial
            yield return wait;
            canSocial = true;
        }
    }

};
