#pragma once
struct TimeManager {
    float time;
    TimeManager() {
        time = 0;
    }
    void updateTime(float framesPassed) {
        time = framesPassed;
    }
    int getDay()
    {
        //24 hours in a day, 60 minutes per, 60 seconds per, 
        //86 400 seconds in a day
        float day = time / 86400.0f;
        int roundedDay = (int)day;
        return roundedDay;
    }
    float getHour()
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
};