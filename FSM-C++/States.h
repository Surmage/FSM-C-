#pragma once
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
    Dead = 'D'

};

enum struct Location : int
{
    Mines = 0,
    Home = 1,
    Work = 2,
    Restaurant = 3,
    Bar = 4,
    Field = 5
};

struct State
{
    Type type;
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