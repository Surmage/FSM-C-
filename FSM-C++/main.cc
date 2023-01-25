#include "Agent.h"
#include <iostream>
using namespace std;

int main(int arg, char* args[])
{
	Idle s;	
	vector<Agent>v;
	//create actor 1
	Agent a;
	v.push_back(a);
	//create actor 2
	Agent b;
	v.push_back(b);
	//create actor 3
	Agent c;
	v.push_back(c);
	//create actor 4
	Agent d;
	v.push_back(d);
	Telegram t(v);
	TimeManager h;

	//Give agents a phone
	a.setPhone(&t);
	b.setPhone(&t);
	c.setPhone(&t);
	d.setPhone(&t);

	//Give agents a clock
	a.setClock(&h);
	b.setClock(&h);
	c.setClock(&h);
	d.setClock(&h);

	while (true) {
		h.updateTime(1);
		a.Update();
		b.Update();
		c.Update();
		d.Update();
	}
	return 1;
}