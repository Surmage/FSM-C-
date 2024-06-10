#pragma once
#include "Agent.h"

Agent::Agent() {
    fullness = 8000;
    thirst = 8000;
    energy = 8000;
    happiness = 8000;
    money = 8000;
    speed = 1;
    status = "Sleepy";
    prevStatus = status;
    //phone = nullptr;
    //clock = nullptr;
    //s = NULL;
    //enterState();
    //type = s->type;
    prevType = type;
    date = std::make_tuple(NULL, this);
    timesAskedForHelp = 0;
    hour = 0;
    canSocial = true;
    busy = false;
    needRepair = false;
}

Agent::Agent(std::string name) {
    this->name = name;
    timesAskedForHelp = 0;
    canSocial = true;
    busy = false;
    needRepair = false;
    //randomize start values
    float startValue1 = 4000.f + rand() % 4001; //random between 4000 and 8000
    float startValue2 = 2000.f;
    float startValue3 = 4000.f + rand() % 4001;
    fullness = startValue1;
    thirst = startValue1;
    energy = startValue2;
    money = startValue3;
    happiness = startValue3;
    status = "Sleepy"; //start program asleep
    prevStatus = status;
    //phone = nullptr;
    //clock = nullptr;
    //s = NULL;
    //enterState();
    //type = s->type;
    prevType = type;
    date = std::make_tuple(NULL, this);
    hour = 0;
    speed = 1;
}

void Agent::Update(int speed)
    {
        //this->speed = speed;

        //hour = (int)clock->getHour();
        //if (hour == 22 && canSocial) //if it's too late at night
        //{
        //    canSocial = false;
        //}
        //if (hour == 8 && !canSocial) //if agent has woken up
        //{
        //    canSocial = true;
        //}

        ////start socializing if the time for the date has arrived
        //if (get<0>(date) == hour && get<1>(date)->name != this->name && canSocial && type != "socializing") { 
        //    startToSocial();
        //}

        //type = s->type;
        //s->Execute(this); //call stat changing function

        //if (fullness <= 0 || thirst <= 0) //agent dies if too thirsty or hungry
        //{
        //    if (status != "Dead")
        //    {
        //        delete s;
        //        status = "Dead";
        //        s = getState(status);
        //        s->Enter(this);
        //    }
        //}
        ////keeping the stats in check, between 0 and 8000

        //if (fullness < 0)
        //{
        //    fullness = 0;
        //}
        //if (fullness > 8000)
        //{
        //    fullness = 8000;
        //}
        //if (thirst < 0)
        //{
        //    thirst = 0;
        //}
        //if (thirst > 8000)
        //{
        //    thirst = 8000;
        //}
        //if (energy < 0)
        //{
        //    energy = 0;
        //}
        //if (energy > 8000)
        //{
        //    energy = 8000;
        //}
        //if (happiness <= 0)
        //{
        //    happiness = 0;
        //}
        //if (happiness > 8000)
        //{
        //    happiness = 8000;
        //}   
        
    }
    void Agent::changeHunger(float change, bool affectedByTime)
    {
        //if (fullness >= 0 && fullness <= 8000)
        //{
        //    if (s->type != "sleeping" || fullness >= 250) {
        //        
        //        if(affectedByTime)
        //            fullness += change * speed;
        //        else
        //            fullness += change;

        //        if (!busy)
        //        {
        //            //If too low
        //            if (fullness <= 1000 && change < 0)
        //            {
        //                checkShouldEnter();

        //            }
        //            //If too high
        //            else if (amIFine() && change > 0)
        //            {
        //                checkShouldEnter();

        //            }
        //        }
        //    }
        //}
    }
    void Agent::changeThirst(float change, bool affectedByTime)
    {
        //if (thirst >= 0 && thirst <= 8000)
        //{
        //    if (s->type != "sleeping" || thirst >= 250) {
        //        if (affectedByTime)
        //            thirst += change * speed;
        //        else
        //            thirst += change;
        //        if (!busy)
        //        {
        //            //If too low
        //            if (thirst <= 1000 && change < 0)
        //            {
        //                checkShouldEnter();

        //            }
        //            //If too high
        //            else if (amIFine() && change > 0)
        //            {
        //                checkShouldEnter();

        //            }
        //        }
        //    }           
        //}
    }
    void Agent::changeEnergy(float change, bool affectedByTime)
    {
        //if (energy >= 0 && energy <= 8000)
        //{
        //    if (affectedByTime)
        //        energy += change * speed;
        //    else
        //        energy += change;

        //    if (energy <= 0) //pass out
        //    {
        //        //busy prevents certain function calls
        //        busy = true;
        //        changeHunger(-1500, false);
        //        changeThirst(-1500, false);
        //        changeMoney(-1000, false);
        //        busy = false;
        //        sendMessage(name + " passed out.");
        //        checkShouldEnter();
        //        return;
        //    }
        //    if (!busy)
        //    {               
        //        //If too low
        //        if (energy <= 1000 && change < 0)
        //        {
        //            if (s->type == "socializing" && amIFine()) //stay up if socializing and not satisfied yet
        //            {
        //                checkShouldEnter();
        //            }
        //            else if (s->type != "socializing") //sleep if not socializing and tired
        //            {
        //                checkShouldEnter();
        //            }
        //        }
        //        //If too high
        //        else if (change > 0 && hour >= 8 && hour <= 9) //Wake up between 8 and 9 if sleeping
        //        {
        //            checkShouldEnter();
        //        }
        //    }
        //}
    }
    void Agent::changeMoney(float change, bool affectedByTime)
    {
        //if (affectedByTime)
        //    money += change * speed;
        //else
        //    money += change;
        //if (!busy)
        //{
        //    if (status != "Social")
        //    {
        //        //if too low
        //        if (money < 1700 && change < 0)
        //        {
        //            checkShouldEnter();
        //        }
        //    }
        //    //if too high
        //    else if (amIFine() && change > 0)
        //    {
        //        checkShouldEnter();
        //    }

        //}

    }
    void Agent::changeHappiness(float change, bool affectedByTime)
    {
        //if (affectedByTime)
        //    happiness += change * speed;
        //else
        //    happiness += change;
        //if (!busy)
        //{
        //    //if too low
        //    if (happiness <= 2000 && change < 0 && canSocial)
        //    {
        //        checkShouldEnter();
        //    }
        //    //Change         


        //    //if too high
        //    else if (amIFine() && change > 0)
        //    {
        //        checkShouldEnter();
        //    }

        //}
    }