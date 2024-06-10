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