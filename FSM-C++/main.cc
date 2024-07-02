#include <iostream>
#include "Agent.h"
#include <SFML/Graphics.hpp>

const int videoX = 1280;
const int videoY = 720;

int main() {
	//create actor 1
	char txtAgent1[] = "Agent1";
	Agent a(txtAgent1, 0);
	//create actor 2
	char txtAgent2[] = "Agent2";
	Agent b(txtAgent2, 1);
	//create actor 3
	char txtAgent3[] = "Agent3";
	Agent c(txtAgent3, 2);
	//create actor 4
	char txtAgent4[] = "Agent4";
	Agent d(txtAgent4, 3);

	
	Telegram t(a, b, c, d);
	StepManager sm;

	//Give agents a phone
	a.setPhone(&t);
	b.setPhone(&t);
	c.setPhone(&t);
	d.setPhone(&t);

	//Give agents a clock
	a.setClock(&sm);
	b.setClock(&sm);
	c.setClock(&sm);
	d.setClock(&sm);

	sf::RenderWindow window(sf::VideoMode(videoX, videoY), "FSM");
	window.setFramerateLimit(60);
	ImGui::SFML::Init(window);

	std::vector<sf::RectangleShape>agentShapes;
	for (int i = 0; i < 4; i++) {
		sf::RectangleShape shape(sf::Vector2f(50.f, 50.f));
		shape.setFillColor(sf::Color::Red);
		shape.setPosition(sf::Vector2f(100, 100));
		agentShapes.push_back(shape);
	}
	
	std::vector<sf::CircleShape>shapes;
	std::vector<sf::Vector2f>locations;
	for (int i = 0; i < 6; i++) {
		sf::Vector2f loc = LocationC::getCoords(i, 0);
		locations.push_back(loc);

		sf::CircleShape shape(100.f);
		shape.setFillColor(sf::Color::White);
		shape.setPosition(loc);
		shapes.push_back(shape);
	}

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
	text.setFillColor(sf::Color::Green);
	text.setPosition(50,10);

	sf::Text timeText;
	timeText.setString("Hello");
	timeText.setFont(font);
	timeText.setCharacterSize(24);
	timeText.setFillColor(sf::Color::White);
	timeText.setPosition(300, 10);

	sf::Text chat;
	chat.setString("");
	chat.setFont(font);
	chat.setCharacterSize(24);
	chat.setFillColor(sf::Color::Green);
	chat.setPosition(400, 400);



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

	sm.step = 8;
	int step = 0;
	

	while (window.isOpen()) {
		std::vector<Agent>agents;
		elapsed = deltaClock.getElapsedTime() - start;
		if (!isPaused) {
			//Update agents
			a.Update(sm.getHour());
			b.Update(sm.getHour());
			c.Update(sm.getHour());
			d.Update(sm.getHour());	
			sm.step = step;
			step++;
			
		}
		agents.push_back(a); agents.push_back(b); agents.push_back(c); agents.push_back(d);
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
		ImGui::Checkbox("Pause", &isPaused);
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
			ImGui::BeginChild("Agent A", ImVec2(0, 0), true,
				ImGuiWindowFlags_HorizontalScrollbar | ImGuiWindowFlags_AlwaysVerticalScrollbar);
			ImGui::SliderFloat("Energy", &a.stats.energy, 0, 100);
			ImGui::SliderFloat("Fullness", &a.stats.fullness, 0, 100);
			ImGui::SliderFloat("Happiness", &a.stats.happiness, 0, 100);
			ImGui::SliderFloat("Thirst", &a.stats.thirst, 0, 100);
			ImGui::SliderFloat("Money", &a.stats.money, 0, 100);
			ImGui::EndChild();
		}

		
			
		ImGui::End();

		//std::cout << isPaused << std::endl;
		
		text.setString((std::string(1, (static_cast<char>(a.type)))) + "\n" +
			"Energy: " + std::to_string(a.stats.energy) + "\n" +
			"Money: " + std::to_string(a.stats.money) + "\n" +
			"Fullness: " + std::to_string(a.stats.fullness) + "\n" +
			"Thirst: " + std::to_string(a.stats.thirst) + "\n" + 
			"Happiness: " + std::to_string(a.stats.happiness) + "\n" + 
			"Counter: " + std::to_string(a.counter));

		timeText.setString("Day: " + std::to_string(sm.getDay()) + 
			" Hour: " + std::to_string(sm.getHour()) +
			" Minute: " + std::to_string(sm.getMinute()));

		chat.setString(t.getMessageChat());
		
		window.clear();
		for (int i = 0; i < shapes.size(); i++) {
			window.draw(shapes[i]);
		}
		for (int i = 0; i < agentShapes.size(); i++) {
			agentShapes[i].setPosition(sf::Vector2f(agents[i].position.x, agents[i].position.y));
			window.draw(agentShapes[i]);
		}
		window.draw(text);
		window.draw(timeText);
		window.draw(chat);
		ImGui::SFML::Render(window);
		sf::sleep(sf::milliseconds(500 / speed));
		window.display();		
	}

	ImGui::SFML::Shutdown();

	return 0;
}