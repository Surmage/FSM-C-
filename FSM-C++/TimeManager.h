#pragma once
#include <iostream>
struct TimeManager {
    float time;
    char chat[256];
    TimeManager() {
        time = 0;
    }
    void updateTime(float framesPassed) {
        time += framesPassed;
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
    char* getTimeChar() {
        char buf[100];
        sprintf_s(buf, "Day: %i Hour: %i", getDay(), (int)getHour());
        return buf;

    }
    char* getMessageChat() {
        return chat;
    }
    void updateMessageText(std::string msg)
    {
        char buf[100];
        sprintf_s(buf, "%s", msg.c_str());
        //chat += buf;

        //int numLines = messagesText.text.Split('\n').Length;
        ////Remove upper messages
        //if (numLines > 6)
        //{
        //    string[] items = messagesText.text.Split('\n');
        //    messagesText.text = items[1] + "\n" + items[2] + "\n" + items[3] + "\n" + items[4] + "\n" + items[5] + "\n";
        //}
        ////Add messages to message box
        //messagesText.text += msg;
        //messagesText.text += "\n";
    }
};