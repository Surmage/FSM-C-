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
    phone = nullptr;
    clock = nullptr;
    s = NULL;
    enterState();
    type = s->type;
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
    phone = nullptr;
    clock = nullptr;
    s = NULL;
    enterState();
    type = s->type;
    prevType = type;
    date = std::make_tuple(NULL, this);
    hour = 0;
    speed = 1;
}

void Agent::Update(int speed)
    {
        this->speed = speed;

        hour = (int)clock->getHour();
        if (hour == 22 && canSocial) //if it's too late at night
        {
            canSocial = false;
        }
        if (hour == 8 && !canSocial) //if agent has woken up
        {
            canSocial = true;
        }

        //start socializing if the time for the date has arrived
        if (std::get<0>(date) == hour && std::get<1>(date)->name != this->name && canSocial && type != "socializing") { 
            startToSocial();
        }

        type = s->type;
        s->Execute(this); //call stat changing function

        if (fullness <= 0 || thirst <= 0) //agent dies if too thirsty or hungry
        {
            if (status != "Dead")
            {
                delete s;
                status = "Dead";
                s = getState(status);
                s->Enter(this);
            }
        }
        //keeping the stats in check, between 0 and 8000

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
        
    }
    void Agent::changeHunger(float change, bool affectedByTime)
    {
        if (fullness >= 0 && fullness <= 8000)
        {
            if (s->type != "sleeping" || fullness >= 250) {
                
                if(affectedByTime)
                    fullness += change * speed;
                else
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
    }
    void Agent::changeThirst(float change, bool affectedByTime)
    {
        if (thirst >= 0 && thirst <= 8000)
        {
            if (s->type != "sleeping" || thirst >= 250) {
                if (affectedByTime)
                    thirst += change * speed;
                else
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
    }
    void Agent::changeEnergy(float change, bool affectedByTime)
    {
        if (energy >= 0 && energy <= 8000)
        {
            if (affectedByTime)
                energy += change * speed;
            else
                energy += change;

            if (energy <= 0) //pass out
            {
                //busy prevents certain function calls
                busy = true;
                changeHunger(-1500, false);
                changeThirst(-1500, false);
                changeMoney(-1000, false);
                busy = false;
                sendMessage(name + " passed out.");
                checkShouldEnter();
                return;
            }
            if (!busy)
            {               
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
    void Agent::changeMoney(float change, bool affectedByTime)
    {
        if (affectedByTime)
            money += change * speed;
        else
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
    void Agent::changeHappiness(float change, bool affectedByTime)
    {
        if (affectedByTime)
            happiness += change * speed;
        else
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

    void Agent::checkShouldEnter()
    {
        //Check if already in state
        status = isAnythingLow();
        if (!compareStatusType())
        {
            enterState();
        }
    }
    void Agent::enterState()
    {
        if (s != NULL) { //call exit is state exists
            s->Exit(this);
        }
        delete s;
        s = getState(status);
        s->Enter(this);
        type = s->type;
    }

    void Agent::startToSocial()
    {
        s->Exit(this);
        delete s;
        s = new Social;
        s->Enter(this);

    }
    State* Agent::getState(std::string message)
    {
        //Plan to socialize
        if (message == "Bored")
        {
            if (this->canSocial == true && hour <= 19 && std::get<1>(date)->name == this->name)
            {
                if (this->money >= 1000) //If not broke
                {
                    if (type != "Social") //If not already socializing
                    {
                        for (int i = 0; i < 4; i++) //Check through all agents
                        {
                            if (this != phone->getAgent(i)) //Check that caller isn't asking themselves to hang out
                            {
                                std::string msg = phone->dispatchMessage(phone->getAgent(i));
                                if (msg == "Yes") //If agent says yes
                                {
                                    this->date = std::make_tuple((int)clock->getHour() + 2, phone->getAgent(i));
                                    phone->getAgent(i)->date = std::make_tuple((int)clock->getHour() + 2, this); //Plan date
                                }
                            }
                        }
                    }
                }
            }
            //Find new state to enter
            setCanSocial(!canSocial); //flipping canSocial is required to prevent isAnythingLow() from returning "Bored" again
            message = this->isAnythingLow();
            setCanSocial(!canSocial);
        }
        //Enter eat state
        if (message == "Hungry")
        {
            State* s = NULL;
            s = new Eat;
            return s;

        }
        //Enter sleep state
        if (message == "Sleepy")
        {
            State* s = NULL;
            s = new Sleep;
            return s;

        }
        //Enter drink state
        if (message == "Thirsty")
        {
            State* s = NULL;
            s = new Drink;
            return s;

        }
        //Enter gather state
        if (message == "Motivated")
        {
            State* s = NULL;
            s = new Gather;
            return s;

        }
        //Enter idle state
        if (message == "Fine")
        {
            State* s = NULL;
            s = new Idle;
            return s;

        }
        //Enter mining state
        if (message == "Poor")
        {
            State* s = NULL;
            s = new Mining;
            return s;

        }
        //Enter dead state
        if (message == "Dead")
        {
            State* s = NULL;
            s = new Dead;
            return s;
        }
        return s;
    }

    
    bool Agent::amIFine()
    {
        //Check if state main stat is high enough to exit
        if (type == "drinking")
        {
            if (thirst >= 8000)
            {
                return true;
            }
        }
        if (type == "eating")
        {
            if (fullness >= 8000)
            {
                return true;
            }
        }
        if (type == "sleeping")
        {
            if (energy >= 8000)
            {
                return true;
            }
        }
        if (type == "gathering")
        {
            if (money >= 5000)
            {
                return true;
            }
        }
        if (type == "mining")
        {
            if (money >= 10000)
            {
                return true;
            }
        }
        if (type == "socializing")
        {
            if (happiness >= 8000 && std::get<1>(date)->happiness >= 8000)
            {
                return true;
            }
        }
        return false;
    }
    bool Agent::canISocial()
    {
        //Check if state money stat is high enough to socialize
        if (money <= 1700)
        {
            return false;
        }
        else
        {
            if (type == "drinking")
            {
                return true;
            }
            if (type == "eating")
            {
                if (fullness >= 1000)
                {
                    return true;
                }
            }
            if (type == "sleeping")
            {
                return false;
            }
            if (type == "gathering")
            {
                return true;
            }
            if (type == "mining")
            {
                if (money >= 5000)
                {
                    return true;
                }
            }
            if (type == "idling around")
            {
                return true;
            }
            if (type == "socializing")
            {
                return true;
            }
        }
        return false;
    }
    std::string Agent::isAnythingLow()
    {
        //tuples with stats and status
        std::vector<std::tuple<float, std::string>> arrs;
        arrs.push_back(std::tuple<float, std::string>(thirst, "Thirsty"));
        arrs.push_back(std::tuple<float, std::string>(energy, "Sleepy"));
        arrs.push_back(std::tuple<float, std::string>(fullness, "Hungry"));
        arrs.push_back(std::tuple<float, std::string>(money, "Poor"));
        arrs.push_back(std::tuple<float, std::string>(happiness, "Bored"));

        //Remove possibility of entering states if should be impossible

        if (!canSocial || money < 1000 || std::get<1>(date)->name != this->name) //remove entering social as an option (if do have date)
        {
            arrs.pop_back();
        }
        if (needRepair && money < 3000) //remove mining as an option
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
                if (!phone->askForMoney(this)) //remove entering eating as an option
                {
                    arrs.erase(arrs.begin() + 2);
                }
                else
                {
                    timesAskedForHelp++;
                    return "Hungry"; //eating will be the next state
                }
            }
            else
            {
                arrs.erase(arrs.begin() + 2); //didn't receive money, can't afford food
            }
        }
        sort(arrs.begin(), arrs.end()); //sort

        //Return stat that is the lowest
        if (std::get<0>(arrs[0]) <= 1000)
        {
            return std::get<1>(arrs[0]);
        }

        else
        {
            //Check if happiness is greater than 100, if it's 100, they cannot work
            if (happiness >= 100)
            {
                // 20% chance to go mining, 40% chance to go gathering, 40% chance to go idle
                int mood = rand() % 5;
                if (mood == 4)
                {
                    if (status != "Poor")
                    {
                        return "Poor";
                    }
                }
                else if (mood == 2 || mood == 3)
                {
                    //if statements to prevent flipping between idle and gather
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

    bool Agent::compareStatusType()
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

    void Agent::setCanSocial(bool value)
    {
        canSocial = value;
    }
    void Agent::setBusy(bool value) {
        busy = value;
    }
    void Agent::setPhone(Telegram* t) {
        phone = t;
    }
    void Agent::setClock(TimeManager* h) {
        clock = h;
    }
    int* Agent::getMainStatValues() {
        int arr[4] = { (int)fullness, (int)thirst, (int)energy, (int)happiness};
        return arr;
    }
    char* Agent::getState() {
        char buf[100];
        sprintf(buf, "State: %s", type.c_str());
        return buf;
    }
    char* Agent::getMoneyChar() {
        char buf[20];      
        sprintf_s(buf, "Money: %i", (int)money);
        return buf;

    }
    void Agent::sendMessage(std::string msg) {
        phone->updateMessageText(msg);
    }   

