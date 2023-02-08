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

	//create actor 1
	char txtAgent1[] = "Agent1";
	Agent a(txtAgent1);
	//create actor 2
	char txtAgent2[] = "Agent2";
	Agent b(txtAgent2);
	//create actor 3
	char txtAgent3[] = "Agent3";
	Agent c(txtAgent3);
	//create actor 4
	char txtAgent4[] = "Agent4";
	Agent d(txtAgent4);
	Telegram t(&a, &b, &c, &d);
	TimeManager h;
	//t.getValue(1);
	//t.getValue(3);

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
		h.updateTime(deltaTime + (frames/60));

		gui::BeginRender();
		gui::Render(a.getMainStatValues(), a.getType(), h.getTimeChar());
		gui::EndRender();

		std::this_thread::sleep_for(std::chrono::milliseconds(5));
	}

	// destroy gui
	gui::DestroyImGui();
	gui::DestroyDevice();
	gui::DestroyHWindow();

	return EXIT_SUCCESS;
}