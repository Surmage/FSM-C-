#pragma once
#include <string>
#include <ctime>

struct Agent;

struct State
{
    std::string type;
    float energyChangeVal;
    //GameObject agent;
    //GameObject manager;
    //InterfaceManager im;

    virtual void Enter(Agent* agent) = 0;

    virtual void Execute(Agent* agent) = 0;

    virtual void Exit(Agent* agent) = 0;

    State() {
    }
    void setStartValues(std::string type)
    {
        //manager = GameObject.Find("InterfaceManager");
        //im = manager.GetComponent<InterfaceManager>();
        this->type = type;
        energyChangeVal = -3.0f;
    }
};
//
struct Dead : State
{
    virtual void Execute(Agent* agent);
    virtual void Enter(Agent* agent);

    virtual void Exit(Agent* agent);
};
struct Drink : State
{
    virtual void Execute(Agent* agent);
    virtual void Enter(Agent* agent);

    virtual void Exit(Agent* agent);
};
struct Eat : State
{
    virtual void Execute(Agent* agent);
    virtual void Enter(Agent* agent);

    virtual void Exit(Agent* agent);
};
struct Gather : State
{
    virtual void Execute(Agent* agent);
    virtual void Enter(Agent* agent);

    virtual void Exit(Agent* agent);
};
struct Idle : State
{
    virtual void Execute(Agent* agent);
    virtual void Enter(Agent* agent);

    virtual void Exit(Agent* agent);
};
struct Mining : State
{
    virtual void Execute(Agent* agent);
    virtual void Enter(Agent* agent);

    virtual void Exit(Agent* agent);
};
struct Social : State
{
    virtual void Execute(Agent* agent);
    virtual void Enter(Agent* agent);

    virtual void Exit(Agent* agent);
};
struct Sleep : State
{
    virtual void Execute(Agent* agent);
    virtual void Enter(Agent* agent);

    virtual void Exit(Agent* agent);
};