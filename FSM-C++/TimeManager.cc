#include "TimeManager.h"

TimeManager::TimeManager() {
    time = 0;
}
void TimeManager::updateTime(float framesPassed) {
    time += framesPassed;
}
int TimeManager::getDay()
{
    //24 hours in a day, 60 minutes per, 60 seconds per, 
    //86 400 seconds in a day
    float day = time / 86400.0f;
    int roundedDay = (int)day;
    return roundedDay;
}
float TimeManager::getHour()
{
    //60 seconds per minute, 60 minutes in an hour, makes 3600 seconds is an hour
    float hour = time / 3600;
    int day = getDay();
    if (day >= 1)
    {
        hour = hour - 24 * getDay();
    }
    return hour;
}
char* TimeManager::getTimeChar() {
    char buf[100];
    sprintf_s(buf, "Day: %i Hour: %i", getDay(), (int)getHour());
    return buf;

}

StepManager::StepManager() {
    step = 0;
}
void StepManager::updateStep(int& increment) {
    if(increment > 0)
        step += increment;
}
int StepManager::getDay() {
    //1 step = 10 minutes => 1 day = 6 * 24 = 144 steps
    float day = step / 144;
    int roundedDay = (int)day;
    return roundedDay;
}
int StepManager::getHour() {
    float hour = step / 6;
    int day = getDay();
    if (day >= 1)
    {
        hour = hour - 24 * day;
    }
    return hour;
}

int StepManager::getMinute() {
    int roundedHour = getHour();
    float hour = step / 6 - 24 * getDay();
    float min = hour - roundedHour;
    min = 60 * min;
    return (min > 0.0) ? (min + 0.5) : (min - 0.5); //rounded up/down
}