#include "Agent.h"
#include <iostream>
using namespace std;

int main(int arg, char* args[])
{
	Idle s;	
	vector<Agent>v;
	//create actor 1
	Agent a("name");
	v.push_back(a);
	//create actor 2
	Agent b("name2");
	v.push_back(b);
	//create actor 3
	Agent c("name3");
	v.push_back(c);
	//create actor 4
	Agent d;
	v.push_back(d);
	Telegram t(&a, &b, &c, &d);
	TimeManager h;
	//t.getValue(1);
	//t.getValue(3);

	//Give agents a phone
	//a.setPhone(&t);
	//b.setPhone(&t);
	//c.setPhone(&t);
	//d.setPhone(&t);

	//Give agents a clock
	a.setClock(&h);
	b.setClock(&h);
	c.setClock(&h);
	d.setClock(&h);

	float prevFrame = 0;
	float frames = 0;
	while (true) {
		//ImGui::ShowDemoWindow();
		b.Update();
		cout << b.type << endl;
	/*	b.Update();
		c.Update();
		d.Update();*/
		frames ++;
		//std::cout << frames << std::endl;
		float currentTime = frames;
		float deltaTime = currentTime - prevFrame;
		prevFrame = currentTime;
		h.updateTime(deltaTime);
		//cout << h.getDay() << " " << h.getHour() << endl;
	}
	cout << "hello world";
	return 1;
}