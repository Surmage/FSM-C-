#pragma once
#include <string>

struct Agent;

struct State
{
    std::string type;
    float speed;
    float energyChangeVal;
    //GameObject agent;
    //GameObject manager;
    //InterfaceManager im;
    std::string dateWith;

    virtual void Enter(Agent* agent) = 0;

    virtual void Execute(Agent* agent) = 0;

    virtual void Exit(Agent* agent) = 0;

    State() {
        speed = 1;
    }
    void setStartValues(std::string type)
    {
        //manager = GameObject.Find("InterfaceManager");
        //im = manager.GetComponent<InterfaceManager>();
        speed = 1;
        this->type = type;
        dateWith = "";
        energyChangeVal = -0.22f;
    }
    void setDate(std::string next)
    {
        this->dateWith = next;
    }
};
//
struct Dead : State
{
    virtual void Execute(Agent* agent)
    {

    }
    virtual void Enter(Agent* agent)
    {
        //Debug.Log(name + " entering Idle state");
        setStartValues("dead");

    }

    virtual void Exit(Agent* agent)
    {
        //Debug.Log(name + " exiting Gather state");

    }
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