#pragma once
#include <string>
#include "Agent.h"
using namespace std;

struct State
{
    string type;
    float speed;
    float energyChangeVal;
    //GameObject agent;
    //GameObject manager;
    //InterfaceManager im;
    string dateWith;

    virtual void Enter(Agent* agent) = 0;

    virtual void Execute(Agent* agent) = 0;

    virtual void Exit(Agent* agent) = 0;

    State() {

    }
    void setStartValues(string type)
    {
        //manager = GameObject.Find("InterfaceManager");
        //im = manager.GetComponent<InterfaceManager>();
        speed = 1;
        this->type = type;
        dateWith = "";
        energyChangeVal = -0.22f;
    }
    void setDate(string next)
    {
        this->dateWith = next;
    }
};
