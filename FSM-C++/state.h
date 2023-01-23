#pragma once
#include <string>
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

    virtual void Enter(string name) = 0;

    virtual void Execute(string name) = 0;

    virtual string Exit(string name) = 0;

    State() {

    }
    State(string type)
    {
        //manager = GameObject.Find("InterfaceManager");
        //im = manager.GetComponent<InterfaceManager>();
        //speed = im.speed;
        this->type = type;
        dateWith = "";
        energyChangeVal = -0.22f;
    }
    void setDate(string next)
    {
        this->dateWith = next;
    }
};
