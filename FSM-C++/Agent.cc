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
    this->stats.fullness = 100;
    this->stats.thirst = 100;
    this->stats.energy = 100;
    this->stats.happiness = 100;
    this->stats.money = 100;
    this->status = Status::Sleepy;
    this->location = (Location::Home);
    int posFromLoc = static_cast<int>(this->location);
    this->position = LocationC::getCoords(posFromLoc, id);
    this->phone = nullptr;
    this->clock = nullptr;
    this->s = NULL;
    this->enterState();
    this->type = Type::Sleeping;
    this->date = std::make_tuple(NULL, this);
    this->timesAskedForHelp = 0;
    this->hour = 0;
    this->canSocial = true;
    this->needRepair = false;
    this->counter = 0;
    this->workCounter = 0;
    this->goBackToWork = false;
}

Agent::Agent(std::string name, int id) {
    this->name = name;
    this->id = id;
    this->timesAskedForHelp = 0;
    this->canSocial = true;
    this->needRepair = false;
    //randomize start values
    float startValue1 = 50.f + rand() % 50; //random between 50 and 100
    float startValue2 = 50.f + rand() % 50;
    this->stats.fullness = startValue1;
    this->stats.thirst = startValue1;
    this->stats.energy = 1;
    this->stats.money = startValue2;
    this->stats.happiness = startValue2;
    this->status = Status::Sleepy; //start program asleep
    this->location = (Location::Home);
    int posFromLoc = static_cast<int>(this->location);
    this->position = LocationC::getCoords(posFromLoc, id);
    this->phone = nullptr;
    this->clock = nullptr;
    this->s = NULL;
    this->enterState();
    this->type = Type::Sleeping;
    this->date = std::make_tuple(NULL, this);
    this->hour = 0;
    this->counter = 0;
    this->workCounter = 0;
    this->goBackToWork = false;
}

void Agent::Update(int cHour)
{
    if (this->type == Type::Dead)
        return;

    if (this->stats.fullness <= 0 || this->stats.thirst <= 0) //agent dies if too thirsty or hungry
    {
        if (status != Status::Dead)
        {
            this->sendMessage(name + " died.");
            delete s;
            this->status = Status::Dead;
            this->s = getState(status);
            this->s->Enter(this);
            return;
        }
    }

    else if (stats.energy <= 0) //pass out
    {
        //busy prevents certain function calls
        this->changeHunger(-15);
        this->changeThirst(-15);
        this->changeMoney(-50);
        this->sendMessage(name + " passed out.");
    }

    this->hour = cHour;
    if (this->hour >= 19) //if it's too late at night
    {
        canSocial = false;
        this->goBackToWork = false;
    }
    else if (this->hour == 6 && !this->canSocial) //if agent has woken up
    {
        this->canSocial = true;
    }
   
    //keeping the stats in check, between 0 and 8000

    if (this->stats.fullness < 0)
    {
        this->stats.fullness = 0;
    }
    if (this->stats.fullness > this->stats.maxFullness)
    {
        this->stats.fullness = this->stats.maxFullness;
    }
    if (this->stats.thirst < 0)
    {
        this->stats.thirst = 0;
    }
    if (this->stats.thirst > this->stats.maxThirst)
    {
        this->stats.thirst = this->stats.maxThirst;
    }
    if (this->stats.energy < 0)
    {
        this->stats.energy = 0;
    }
    if (this->stats.energy > this->stats.maxEnergy)
    {
        this->stats.energy = this->stats.maxEnergy;
    }
    if (this->stats.happiness <= 0)
    {
        this->stats.happiness = 0;
    }
    if (this->stats.happiness > this->stats.maxHappiness)
    {
        this->stats.happiness = this->stats.maxHappiness;
    } 

    this->s->Execute(this); //call stat changing function
    if (this->goBackToWork && this->checkCanEnter())
    {
        this->status = Status::Poor;
        this->enterState();
        return;
    }

    //start socializing if the time for the date has arrived
    if (std::get<0>(this->date) == this->hour && 
        std::get<1>(this->date)->name != this->name &&
        this->type != Type::Socializing)
    {
        this->startToSocial();
        return;
    }
    if (this->amIFine() || this->inDanger()) {
        this->checkShouldEnter();
    }     
}
    void Agent::changeHunger(float change)
    {
        if (this->stats.fullness >= 0 && this->stats.fullness <= this->stats.maxFullness)
        {            
            this->stats.fullness += change;
        }
    }
    void Agent::changeThirst(float change)
    {
        if (this->stats.thirst >= 0 && this->stats.thirst <= this->stats.maxThirst)
        {            
            this->stats.thirst += change;
        }
    }
    void Agent::changeEnergy(float change)
    {
        if (this->stats.energy >= 0 && this->stats.energy <= this->stats.maxEnergy)
        
            this->stats.energy += change;
        
    }
    void Agent::changeMoney(float change)
    {
        //No limits, debt exists
        this->stats.money += change;
    }
    void Agent::changeHappiness(float change)
    {
        this->stats.happiness += change;
    }

    void Agent::checkShouldEnter()
    {        
        this->isAnythingLow(status);
        if (!this->compareStatusType()) //Check if already in state
        {
            if(this->checkCanEnter()) //Check if switching state is appropriate
                this->enterState();
        }
    }

    bool Agent::checkCanEnter() {
        //Check if state counter and stats are sufficient for pivoting

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
            if (hour == 6) //wake up at 6
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
            if (counter >= 12 || stats.thirst <= 10 || stats.fullness <= 10 || stats.energy <= 5)
            {
                return true;
            }
        }
        else if (type == Type::Mining)
        {
            if (counter >= 36 || stats.thirst <= 10 || stats.fullness <= 10 || stats.energy <= 5)
            {
                return true;
            }
        }
        else if (type == Type::Socializing)
        {
            if (stats.happiness >= stats.maxHappiness * 0.9f || 
                std::get<1>(date)->stats.happiness >= stats.maxHappiness * 0.9f)
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
            if (std::get<1>(date)->name != this->name) { //if a date is planned
                State* s = NULL;
                s = new Idle;
                return s;
            }
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
                        canSocial = false;
                    }
                }
            }
            //Find new state to enter
            this->isAnythingLow(msg);
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
            if(hour == 6)
                return true;
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
            stats.money <= 50) return true;
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
                if (stats.money >= 250 && counter >= 25)
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

        if (!canSocial || stats.money < 150 || std::get<1>(date)->name != this->name) //remove entering social as an option (if do have date)
        {
            arrs.pop_back();
        }
        if ((needRepair && stats.money < 400) || hour >= 15) //remove mining as an option
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
                if ((mood == 4 && !needRepair) || (mood == 4 && needRepair && stats.money >= 400))
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

    void Agent::setPhone(Telegram* t) {
        phone = t;
    }
    void Agent::setClock(StepManager* h) {
        clock = h;
    }
   
    void Agent::sendMessage(std::string msg) {
        phone->updateMessageText(msg);
    }   

