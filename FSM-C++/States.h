#pragma once
#include "Locations.h"
#include <string>
#include <ctime>

struct Agent;

enum struct Type : char
{
    Sleeping = 'Z',
    Eating = 'E',
    Drinking = 'D',
    Socializing = 'S',
    Lazing = 'L',
    Gathering = 'G',
    Mining = 'M',
    Dead = 'R'

};

struct State
{
    float energyChangeVal;
    float statChangeVal;

    State();

    virtual void Enter(Agent* agent) = 0;
    virtual void Execute(Agent* agent) = 0;
    virtual void Exit(Agent* agent) = 0;
};

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