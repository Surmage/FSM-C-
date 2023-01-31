#pragma once
#include "Telegram.h"
#include "Agent.h"

Telegram::Telegram() :
	a(0), b(0), c(0), d(0)
{}
Telegram::Telegram(Agent* aa, Agent* bb, Agent* cc, Agent* dd) :
	a(aa), b(bb), c(cc), d(dd)
{}

Agent* Telegram::getAgent(int i) {
	switch (i)
	{
	case 1:
		return a;
	case 2:
		return b;
	case 3:
		return c;
	case 4:
		return d;
	default:
		return a;
	}

}