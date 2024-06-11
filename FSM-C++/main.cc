#include <iostream>
#include "Agent.h"
#include "imgui.h"
#include "imgui-SFML.h"
#include <SFML/Graphics.hpp>

//int __stdcall wWinMain(
//	HINSTANCE instance,
//	HINSTANCE previousInstance,
//	PWSTR arguments,
//	int commandShow)
//{
//	// create gui
//	gui::CreateHWindow("FSM");
//	gui::CreateDevice();
//	gui::CreateImGui();
//
//	std::vector<Agent>v;
//	//create actor 1
//	char txtAgent1[] = "Agent1";
//	Agent a(txtAgent1);
//	//create actor 2
//	char txtAgent2[] = "Agent2";
//	Agent b(txtAgent2);
//	//create actor 3
//	char txtAgent3[] = "Agent3";
//	Agent c(txtAgent3);
//	//create actor 4
//	char txtAgent4[] = "Agent4";
//	Agent d(txtAgent4);
//	
//	Telegram t(a, b, c, d);
//	TimeManager h;
//
//	//Give agents a phone
//	a.setPhone(&t);
//	b.setPhone(&t);
//	c.setPhone(&t);
//	d.setPhone(&t);
//
//	//Give agents a clock
//	a.setClock(&h);
//	b.setClock(&h);
//	c.setClock(&h);
//	d.setClock(&h);
//
//	float prevFrame = 0;
//	float frames = 0;
//	int i = 0;
//	bool isPaused = false;
//	int speed = 1;
//
//	srand((unsigned)time(NULL));
//
//	high_resolution_clock::duration totalTime(0);
//	using clock = std::chrono::steady_clock;
//	clock::duration elapsed = {};
//	auto start = high_resolution_clock::now();
//
//	while (gui::isRunning)
//	{
//		elapsed = std::chrono::steady_clock::now() - start;
//		if (!isPaused) {
//			//Update agents
//			a.Update(speed);
//			b.Update(speed);
//			c.Update(speed);
//			d.Update(speed);
//			//Roughly 1 hour per 2 seconds from testing
//			float currentTime = (float)std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count() / 600.0f; 
//			float deltaTime = currentTime - prevFrame;
//			prevFrame = currentTime;
//			h.updateTime(deltaTime  * speed);
//		}
//		else {
//			//pause
//			prevFrame = (float)std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count() / 600.0f;
//		}
//
//		gui::BeginRender();
//		gui::Render();
//
//		v.clear();
//		v.resize(0);
//		v.push_back(a);
//		v.push_back(b);
//		v.push_back(c);
//		v.push_back(d);
//		i = gui::SetupGUI(v[i].getMainStatValues(), v[i].getState(), v[i].getMoneyChar(), h.getTimeChar(), t.getMessageChat(), i);
//		isPaused = gui::PauseButtonF(isPaused);
//		speed = gui::SpeedSlider(speed);
//		
//		gui::EndGUI();
//		gui::EndRender();
//
//		std::this_thread::sleep_for(std::chrono::milliseconds(5));
//	}
//
//	// destroy gui
//	gui::DestroyImGui();
//	gui::DestroyDevice();
//	gui::DestroyHWindow();
//
//	return EXIT_SUCCESS;
//}

int main() {
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

	
	Telegram t(a, b, c, d);
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

	sf::RenderWindow window(sf::VideoMode(640, 480), "FSM");
	window.setFramerateLimit(60);
	ImGui::SFML::Init(window);
	sf::CircleShape shape(100.f);
	//sf::RectangleShape rect(100.f, 100.f);
	shape.setFillColor(sf::Color::White);
	//rect.setFillColor(sf::Color::Green);
	sf::Font font;
	if (!font.loadFromFile("tahoma.ttf"))
	{
		// error...
	}
	sf::Text text;
	text.setString("Hello");
	text.setFont(font);
	text.setCharacterSize(24);
	text.setFillColor(sf::Color::Black);
	text.setPosition(50,10);



	sf::Clock deltaClock;

	float prevFrame = 0;
	float frames = 0;
	int i = 0;
	bool isPaused = false;
	int speed = 1;
	sf::Time start;
	sf::Time elapsed;
	start = deltaClock.getElapsedTime();
	
	srand((unsigned)time(NULL));

	while (window.isOpen()) {
		elapsed = deltaClock.getElapsedTime() - start;
		if (!isPaused) {
			//Update agents
			a.Update(speed);
			b.Update(speed);
			c.Update(speed);
			d.Update(speed);
			std::cout << a.status << " " << a.energy << " Hour: " << a.hour << std::endl;
			
			//Roughly 1 hour per 2 seconds from testing
			float currentTime = (float)elapsed.asMicroseconds() / 600.0f; 
			float deltaTime = currentTime - prevFrame;
			prevFrame = currentTime;
			//std::cout << currentTime << std::endl;
			h.updateTime(deltaTime  * speed);
		}
		else {
			//pause
			prevFrame = (float)elapsed.asMicroseconds() / 600.0f;
		}
		sf::Event event;
		while (window.pollEvent(event)) {
			ImGui::SFML::ProcessEvent(window, event);

			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		ImGui::SFML::Update(window, deltaClock.getElapsedTime());

		//ImGui::ShowDemoWindow();

		ImGui::Begin("Hello, world!");
		ImGui::Button("Look at this pretty button");
		ImGui::SliderInt("speed", &speed, 0, 10);
		ImGui::End();
		text.setString(a.type + "\n" + 
			"Energy: " + std::to_string(a.energy) + "\n" +
			"Money: " + std::to_string(a.money) + "\n" +
			"Fullness: " + std::to_string(a.fullness) + "\n" +
			"Thirst: " + std::to_string(a.thirst));

		window.clear();
		window.draw(shape);
		window.draw(text);
		ImGui::SFML::Render(window);
		window.display();
	}

	ImGui::SFML::Shutdown();

	return 0;
}