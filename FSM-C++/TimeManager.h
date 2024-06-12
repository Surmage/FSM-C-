#pragma once
#include <iostream>

struct TimeManager {
    float time;
    TimeManager();
    void updateTime(float framesPassed);
    int getDay();
    float getHour();
    char* getTimeChar();
    
};

struct StepManager {
    float step;
    StepManager();
    void updateStep(int &increment);
    int getDay();
    int getHour();
    int getMinute();
};