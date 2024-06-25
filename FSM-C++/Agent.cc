#include "Agent.h"

Agent::Stats::Stats() {
    fullness = 100;
    thirst = 100;
    energy = 100;
    happiness = 100;
    money = 100;
    maxFullness = 100;
    maxThirst = 100;
    maxEnergy = 100;
    maxHappiness = 100;
}

Agent::Agent() {
    stats.fullness = 100;
    stats.thirst = 100;
    stats.energy = 100;
    stats.happiness = 100;
    stats.money = 100;
    speed = 1;
    status = Status::Sleepy;
    setLocation(Location::Home);
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
    counter = 0;
}

Agent::Agent(std::string name) {
    this->name = name;
    timesAskedForHelp = 0;
    canSocial = true;
    busy = false;
    needRepair = false;
    //randomize start values
    float startValue1 = 50.f + rand() % 50; //random between 4000 and 8000
    float startValue2 = 50.f;
    float startValue3 = 50.f + rand() % 50;
    stats.fullness = startValue1;
    stats.thirst = startValue1;
    stats.energy = 1;
    stats.money = startValue3;
    stats.happiness = startValue3;
    status = Status::Sleepy; //start program asleep
    setLocation(Location::Home);
    phone = nullptr;
    clock = nullptr;
    s = NULL;
    enterState();
    type = s->type;
    prevType = type;
    date = std::make_tuple(NULL, this);
    hour = 0;
    speed = 1;
    counter = 0;
}

void Agent::Update(int cHour)
    {
        this->speed = 1;

        this->hour = cHour;
        if (hour == 22 && canSocial) //if it's too late at night
        {
            canSocial = false;
        }
        if (hour == 8 && !canSocial) //if agent has woken up
        {
            canSocial = true;
        }

        type = s->type;
        s->Execute(this); //call stat changing function
        if (stats.energy <= 0) //pass out
        {
            //busy prevents certain function calls
            busy = true;
            changeHunger(-15, false);
            changeThirst(-15, false);
            changeMoney(-50, false);
            busy = false;
            sendMessage(name + " passed out.");
        }
        if (stats.fullness <= 0 || stats.thirst <= 0) //agent dies if too thirsty or hungry
        {
            if (status != Status::Dead)
            {
                sendMessage(name + " died.");
                //std::cout << type << std::endl;
                delete s;
                status = Status::Dead;
                s = getState(status);
                s->Enter(this);
                return;
            }
        }
       

        
        //keeping the stats in check, between 0 and 8000

        if (stats.fullness < 0)
        {
            stats.fullness = 0;
        }
        if (stats.fullness > stats.maxFullness)
        {
            stats.fullness = stats.maxFullness;
        }
        if (stats.thirst < 0)
        {
            stats.thirst = 0;
        }
        if (stats.thirst > stats.maxThirst)
        {
            stats.thirst = stats.maxThirst;
        }
        if (stats.energy < 0)
        {
            stats.energy = 0;
        }
        if (stats.energy > stats.maxEnergy)
        {
            stats.energy = stats.maxEnergy;
        }
        if (stats.happiness <= 0)
        {
            stats.happiness = 0;
        }
        if (stats.happiness > stats.maxHappiness)
        {
            stats.happiness = stats.maxHappiness;
        } 
        //start socializing if the time for the date has arrived
        if (std::get<0>(date) == hour && std::get<1>(date)->name != this->name && canSocial && type != Type::Socializing) {
            startToSocial();
            return;
        }
        if (amIFine() || inDanger()) {
            checkShouldEnter();
        }
            
        
    }
    void Agent::changeHunger(float change, bool affectedByTime)
    {
        if (stats.fullness >= 0 && stats.fullness <= stats.maxFullness)
        {
            {
                
                if(affectedByTime)
                    stats.fullness += change * speed;
                else
                    stats.fullness += change;       
            }
        }
    }
    void Agent::changeThirst(float change, bool affectedByTime)
    {
        if (stats.thirst >= 0 && stats.thirst <= stats.maxThirst)
        {
            {
                if (affectedByTime)
                    stats.thirst += change * speed;
                else
                    stats.thirst += change;
            }           
        }
    }
    void Agent::changeEnergy(float change, bool affectedByTime)
    {
        if (stats.energy >= 0 && stats.energy <= stats.maxEnergy)
        {
            if (affectedByTime)
                stats.energy += change * speed;
            else
                stats.energy += change;
       
        }
    }
    void Agent::changeMoney(float change, bool affectedByTime)
    {
        if (affectedByTime)
            stats.money += change * speed;
        else
            stats.money += change;      

    }
    void Agent::changeHappiness(float change, bool affectedByTime)
    {
        if (affectedByTime)
            stats.happiness += change * speed;
        else
            stats.happiness += change;
        
    }

    void Agent::checkShouldEnter()
    {
        
        isAnythingLow(status);
        if (!compareStatusType()) //Check if already in state
        {
            if(checkCanEnter(status)) //Check if switching state is appropriate
                enterState();
        }
    }

    bool Agent::checkCanEnter(Status& status) {
        
        //Check if state main stat is high enough to exit
        if (type == Type::Drinking)
        {
            return true;
            
        }
        else if (type == Type::Eating)
        {
            if (counter >= 2)
                return true;
        }
        else if (type == Type::Sleeping)
        {
            if (counter >= 40)
            {
                return true;
            }
        }
        else if (type == Type::Lazing)
        {
            if (counter >= 3 || stats.thirst <= 10 || stats.fullness <= 10)
            {
                return true;
            }
        }
        else if (type == Type::Gathering)
        {
            if (counter >= 6 || stats.thirst <= 10 || stats.fullness <= 10)
            {
                return true;
            }
        }
        else if (type == Type::Mining)
        {
            if (counter >= 12 || stats.thirst <= 10 || stats.fullness <= 10)
            {
                return true;
            }
        }
        else if (type == Type::Socializing)
        {
            if (stats.happiness >= stats.maxHappiness * 0.9f || std::get<1>(date)->stats.happiness >= stats.maxHappiness * 0.9f)
            {
                return true;
            }
        }
        return false;
    }

    void Agent::enterState()
    {
        if (s != NULL) { //call exit if state exists
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
    State* Agent::getState(Status &msg)
    {
        //Plan to socialize
        if (msg == Status::Bored)
        {
            if (this->canSocial == true && hour <= 19 && std::get<1>(date)->name == this->name)
            {
                if (this->stats.money >= 100) //If not broke
                {
                    if (type != Type::Socializing) //If not already socializing
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
            this->isAnythingLow(msg);
            setCanSocial(!canSocial);
        }
        //Enter eat state
        if (msg == Status::Hungry)
        {
            State* s = NULL;
            s = new Eat;
            return s;

        }
        //Enter sleep state
        if (msg == Status::Sleepy)
        {
            State* s = NULL;
            s = new Sleep;
            return s;

        }
        //Enter drink state
        if (msg == Status::Thirsty)
        {
            State* s = NULL;
            s = new Drink;
            return s;

        }
        //Enter gather state
        if (msg == Status::Motivated)
        {
            State* s = NULL;
            s = new Gather;
            return s;

        }
        //Enter idle state
        if (msg == Status::Fine)
        {
            State* s = NULL;
            s = new Idle;
            return s;

        }
        //Enter mining state
        if (msg == Status::Poor)
        {
            State* s = NULL;
            s = new Mining;
            return s;

        }
        //Enter dead state
        if (msg == Status::Dead)
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
        if (type == Type::Drinking)
        {
            if (stats.thirst >= stats.maxThirst * 0.9f)
            {
                return true;
            }
        }
        if (type == Type::Eating)
        {
            if (stats.fullness >= stats.maxFullness * 0.9f)
            {
                return true;
            }
        }
        if (type == Type::Sleeping)
        {
            if (stats.energy >= stats.maxFullness * 0.9f)
            {
                return true;
            }
        }
        if (type == Type::Gathering)
        {
            if (stats.money >= 500)
            {
                return true;
            }
        }
        if (type == Type::Mining)
        {
            if (stats.money >= 500)
            {
                return true;
            }
        }
        if (type == Type::Socializing)
        {
            if (stats.happiness >= stats.maxHappiness * 0.9f || std::get<1>(date)->stats.happiness >= stats.maxHappiness * 0.9f)
            {
                return true;
            }
        }
        return false;
    }

    bool Agent::inDanger() {
        if (stats.energy <= stats.maxEnergy * 0.1f ||
            stats.fullness <= stats.maxFullness * 0.1f ||
            stats.thirst <= stats.maxThirst * 0.1f ||
            stats.happiness <= stats.maxHappiness * 0.1f ||
            stats.money <= 25) return true;
        else
            return false;
    }

    bool Agent::canISocial()
    {
        //Check if state money stat is high enough to socialize
        if (stats.money <= 100)
        {
            return false;
        }
        else
        {
            if (type == Type::Drinking)
            {
                return true;
            }
            if (type == Type::Eating)
            {
                if (stats.fullness >= stats.maxFullness * 0.1f)
                {
                    return true;
                }
            }
            if (type == Type::Sleeping)
            {
                return false;
            }
            if (type == Type::Gathering)
            {
                return true;
            }
            if (type == Type::Mining)
            {
                if (stats.money >= 250)
                {
                    return true;
                }
            }
            if (type == Type::Lazing)
            {
                return true;
            }
            if (type == Type::Socializing)
            {
                return false;
            }
        }
        return false;
    }
    bool Agent::isAnythingLow(Status &msg)
    {
        //tuples with stats and status
        std::vector<std::tuple<float, Status>> arrs;
        arrs.push_back(std::tuple<float, Status>(stats.thirst, Status::Thirsty));
        arrs.push_back(std::tuple<float, Status>(stats.energy, Status::Sleepy));
        arrs.push_back(std::tuple<float, Status>(stats.fullness, Status::Hungry));
        arrs.push_back(std::tuple<float, Status>(stats.money, Status::Poor));
        arrs.push_back(std::tuple<float, Status>(stats.happiness, Status::Bored));

        //Remove possibility of entering states if should be impossible

        if (!canSocial || stats.money < 100 || std::get<1>(date)->name != this->name) //remove entering social as an option (if do have date)
        {
            arrs.pop_back();
        }
        if (needRepair && stats.money < 100) //remove mining as an option
        {
            arrs.erase(arrs.begin() + 3);
        }
        else if (stats.energy <= stats.maxEnergy * 0.2f || stats.happiness <= stats.maxHappiness * 0.1f) //remove mining as an option too
        {
            arrs.erase(arrs.begin() + 3);
        }
        if (stats.fullness <= stats.maxFullness * 0.1f && stats.money < 15) //check if hungry and poor
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
                    msg == Status::Hungry;
                    return true; //eating will be the next state
                }
            }
            else
            {
                arrs.erase(arrs.begin() + 2); //didn't receive money, can't afford food
            }
        }
        sort(arrs.begin(), arrs.end()); //sort

        //Return stat that is the lowest
        if (std::get<0>(arrs[0]) <= 10)
        {
            msg = std::get<1>(arrs[0]);
            return true;
        }

        else
        {
            //Check if happiness is greater than 100, if it's 100, they cannot work
            if (stats.happiness >= stats.maxHappiness * 0.1f)
            {
                // 20% chance to go mining, 40% chance to go gathering, 40% chance to go idle
                int mood = rand() % 5;
                if (mood == 4)
                {
                    if (status != Status::Poor)
                    {
                        msg = Status::Poor;
                        return true;
                    }
                }
                else if (mood == 2 || mood == 3)
                {
                    //if statements to prevent flipping between idle and gather
                    if (status != Status::Fine)
                    {
                        msg = Status::Motivated;
                        return true;
                    }
                    else
                    {
                        msg = Status::Fine;
                        return true;
                    }
                }
                else
                {
                    if (status != Status::Motivated)
                    {
                        msg = Status::Fine;
                        return true;
                    }
                    else
                    {
                        msg = Status::Motivated;
                        return true;
                    }
                }

            }
            else
            {
                if (status != Status::Motivated)
                {
                    msg = Status::Fine;
                    return true;
                }
                else
                {
                    msg = Status::Motivated;
                    return true;
                }
            }
        }
        return false;
    }

    bool Agent::compareStatusType()
    {
        //Checks if type fits with status, for example: is the agent eating because they are hungry? Is the agent sleeping because they are sleepy?
        if (status == Status::Hungry)
        {
            if (type == Type::Eating)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        if (status == Status::Sleepy)
        {
            if (type == Type::Sleeping)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        if (status == Status::Thirsty)
        {
            if (type == Type::Drinking)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        if (status == Status::Motivated)
        {
            if (type == Type::Gathering)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        if (status == Status::Bored)
        {
            if (type == Type::Socializing)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        if (status == Status::Fine)
        {
            if (type == Type::Lazing)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        if (status == Status::Poor)
        {
            if (type == Type::Mining)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        if (status == Status::Dead)
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
    void Agent::setClock(StepManager* h) {
        clock = h;
    }
    void Agent::setLocation(Location l) {
        int coord = static_cast<int>(l);
        sf::Vector2i pos(coord, coord);
        this->location = std::tuple(l, pos);
    }
    int* Agent::getMainStatValues() {
        int arr[4] = { (int)stats.fullness, (int)stats.thirst, (int)stats.energy, (int)stats.happiness};
        return arr;
    }
    char* Agent::getState() {
        char buf[100];
        //sprintf(buf, "State: %s", type.c_str());
        return buf;
    }
    char* Agent::getMoneyChar() {
        char buf[20];      
        sprintf_s(buf, "Money: %i", (int)stats.money);
        return buf;

    }
    void Agent::sendMessage(std::string msg) {
        phone->updateMessageText(msg);
    }   

