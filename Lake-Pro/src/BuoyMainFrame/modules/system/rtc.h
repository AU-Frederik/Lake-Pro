#pragma once
#include "../setup/modules.h"

bool century = false;
bool h12Flag;
bool pmFlag;
bool twentyFourHourClock = false; // True = 12h, false = 24h

void setRTCData() {
    myRTC.setClockMode(twentyFourHourClock);  // false to set to 24h
    myRTC.setYear(24);
    myRTC.setMonth(OCTOBER);
    myRTC.setDate(23);
    myRTC.setDoW(WEDNESDAY);
    myRTC.setHour(17);
    myRTC.setMinute(30);
    myRTC.setSecond(0);
}