#include "Agent.h"
#include <iostream>
#include "gui.h"
#include <thread>

int __stdcall wWinMain(
	HINSTANCE instance,
	HINSTANCE previousInstance,
	PWSTR arguments,
	int commandShow)
{
	// create gui
	gui::CreateHWindow("FSM");
	gui::CreateDevice();
	gui::CreateImGui();
	int x = 0;

	Idle s;	
	std::vector<Agent>v;
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
	Agent d("name4");
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

	while (gui::isRunning)
	{
		a.Update();
		b.Update();
		c.Update();
		d.Update();
		frames ++;
		//std::cout << frames << std::endl;
		float currentTime = frames;
		float deltaTime = currentTime - prevFrame;
		prevFrame = currentTime;
		h.updateTime(deltaTime);

		gui::BeginRender();
		gui::Render(x);
		gui::EndRender();

		std::this_thread::sleep_for(std::chrono::milliseconds(5));
		x++;
	}

	// destroy gui
	gui::DestroyImGui();
	gui::DestroyDevice();
	gui::DestroyHWindow();

	return EXIT_SUCCESS;
}