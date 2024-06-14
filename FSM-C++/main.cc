#include <iostream>
#include "Agent.h"
#include "imgui.h"
#include "imgui-SFML.h"
#include <SFML/Graphics.hpp>

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

	sf::Text timeText;
	timeText.setString("Hello");
	timeText.setFont(font);
	timeText.setCharacterSize(24);
	timeText.setFillColor(sf::Color::White);
	timeText.setPosition(300, 10);



	sf::Clock deltaClock;

	float prevStep = 0;
	float frames = 0;
	int i = 0;
	bool isPaused = true;
	int speed = 1;
	sf::Time start;
	sf::Time elapsed;
	start = deltaClock.getElapsedTime();
	
	srand((unsigned)time(NULL));

	StepManager sm;
	sm.step = 8;
	int step = 0;
	
	

	while (window.isOpen()) {
		elapsed = deltaClock.getElapsedTime() - start;
		if (!isPaused) {
			//Update agents
			a.Update(sm.getHour());
			b.Update(sm.getHour());
			c.Update(sm.getHour());
			d.Update(sm.getHour());
			//std::cout << a.status << " " << a.energy << " Hour: " << a.hour << std::endl;
			
			//Roughly 1 hour per 2 seconds from testing
			//float currentTime = (float)elapsed.asMicroseconds() / 600.0f; 
			//float deltaTime = currentTime - prevFrame;
			//prevFrame = currentTime;
			//std::cout << currentTime << std::endl;
			//h.updateTime(deltaTime  * speed);			
			sm.step = step;
			step++;
			
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
		if(ImGui::Button("Pause")) {
			isPaused = !isPaused;
		}
		ImGui::SliderInt("speed", &speed, 0, 10);
		if (isPaused) {
			if (ImGui::InputInt("Step", &step, 1, 1)) {
				std::cout << "Pressed" << std::endl;
				a.Update(sm.getHour());
				b.Update(sm.getHour());
				c.Update(sm.getHour());
				d.Update(sm.getHour());
				prevStep = step--;
				sm.step = step;
			}

		}
			
		ImGui::End();

		//std::cout << isPaused << std::endl;
		
		text.setString(a.type + "\n" + 
			"Energy: " + std::to_string(a.stats.energy) + "\n" +
			"Money: " + std::to_string(a.stats.money) + "\n" +
			"Fullness: " + std::to_string(a.stats.fullness) + "\n" +
			"Thirst: " + std::to_string(a.stats.thirst));

		timeText.setString("Day: " + std::to_string(sm.getDay()) + 
			" Hour: " + std::to_string(sm.getHour()) +
			" Minute: " + std::to_string(sm.getMinute()));

		window.clear();
		window.draw(shape);
		window.draw(text);
		window.draw(timeText);
		ImGui::SFML::Render(window);
		sf::sleep(sf::milliseconds(500 / speed));
		window.display();
		
	}

	ImGui::SFML::Shutdown();

	return 0;
}